//
//  Directory.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//
#include <iostream>
#include "Directory.h"

using namespace boost::filesystem;

Directory::Directory(boost::filesystem::path p, float sphereRad, float orbitRad,
                     float angularVelocity)
{
    path = p;
    filesCached = false;
    sphereRadius = sphereRad;
    orbitRadius = orbitRad;
    selectedSound = nullptr;
    orbit = new Orbit(orbitRadius, angularVelocity, 100000, 1, 0, 0.0);
    center = ofVec3f(0, 0, 0);
}

bool Directory::isValid()
{
    if (boost::filesystem::exists(path))
    {
        return boost::filesystem::is_directory(path);
    }
    return false;
}

std::vector<Directory*> Directory::getSubDirs()
{
    if (isValid() && ! filesCached)
    {
        updateFiles();
    }
    return subDirs;
}

std::vector<Sound*> Directory::getSounds()
{
    if (isValid() && ! filesCached)
    {
        updateFiles();
    }
    return sounds;
}


void Directory::updateFiles()
{
    directory_iterator end_itr;
    int i = 0;
    for ( directory_iterator itr( path ); itr != end_itr; ++itr )
    {
        boost::filesystem::path p = itr->path();
        boost::filesystem::file_status stat = itr->status();
        float orbitRadius = sphereRadius + (sphereRadius/5.0) * (i + 1);
        float angularVelocity;
        if (orbitRadius > sphereRadius)
        {
            float ratio = orbitRadius / sphereRadius;
            angularVelocity = (1.0/(ratio*ratio));
        } else
        {
            angularVelocity = 0.0;
        }
        if (is_directory(stat))
        {
            Directory* dir = new Directory(p, sphereRadius/3.0, orbitRadius, angularVelocity);
            if (dir->isValid())
            {
                subDirs.push_back(dir);
                i = i + 1;
            } else
            {
                delete dir;
            }
        }
        else if (is_regular_file(stat))
        {
            SndfileHandle myf = SndfileHandle(p.string());
            int error = myf.error();
            if (error == 0)
            {
                Sound* s = new Sound(myf, p, orbitRadius, angularVelocity);
                sounds.push_back(s);
                i = i + 1;
            }
        }
    }
    filesCached = true;
}

void Directory::update(float secondsElapsed, int depth)
{
    if (depth > maxDepth)
    {
        return;
    }
    sounds = getSounds();
    subDirs = getSubDirs();
    orbit->update(secondsElapsed);
    for (int i = 0; i < sounds.size(); ++i)
    {
        sounds[i]->update(secondsElapsed);
    }
    for (int i = 0; i < subDirs.size(); ++i)
    {
        subDirs[i]->update(secondsElapsed, depth + 1);
    }
}


void Directory::draw(ofVec3f center, int depth)
{
    if (depth > maxDepth)
    {
        return;
    }
    sounds = getSounds();
    subDirs = getSubDirs();

    // draw the sphere repesenting the directory
    ofVec3f position = orbit->getHeadPosition();
    position = position + center;
    ofSpherePrimitive sphere = ofSpherePrimitive();
    sphere.setPosition(position);
    sphere.setRadius(sphereRadius);
    sphere.draw(OF_MESH_WIREFRAME);
    
    
    for (int i = 0; i < sounds.size(); ++i)
    {
        sounds[i]->draw(position);
    }
    for (int i = 0; i < subDirs.size(); ++i)
    {
        subDirs[i]->draw(position, depth + 1);
    }
    
    
    if (selectedSound != nullptr)
    {
        selectedSound->drawOrbit();
    }
}


