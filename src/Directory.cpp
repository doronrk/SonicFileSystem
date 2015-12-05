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
    displayName = p.filename().string();
    filesCached = false;
    sphereRadius = sphereRad;
    orbitRadius = orbitRad;
    selectedSound = nullptr;
    orbit = new Orbit(orbitRadius, angularVelocity, 100000, 1, 0, 0.0);
    center = ofVec3f(0, 0, 0);
    int r = round(ofRandom(0, 255));
    int g = round(ofRandom(0, 255));
    int b = 255 - r - g;
    color = ofColor(r, g, b);
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
    vector<Directory*> subDirs;
    for(map<std::string,Directory*>::iterator it = subDirMap.begin(); it != subDirMap.end(); ++it) {
        subDirs.push_back(it->second);
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

std::string Directory::getDisplayname()
{
    return displayName;
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
                subDirMap.insert(std::pair<std::string, Directory*>(p.filename().string(), dir));
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
                Sound* s = new Sound(myf, p, orbitRadius, angularVelocity, p.filename().string());
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
    std::vector<Directory*> subDirs = getSubDirs();
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


void Directory::draw(ofVec3f center, int depth, bool dispNamesOn)
{
    if (depth > maxDepth)
    {
        return;
    }
    ofPushStyle();
    {
        ofSetColor(color);
        sounds = getSounds();
        std::vector<Directory*> subDirs = getSubDirs();

        // draw the sphere repesenting the directory
        ofVec3f position = orbit->getHeadPosition();
        position = position + center;
        ofSpherePrimitive sphere = ofSpherePrimitive();
        sphere.setPosition(position);
        sphere.setRadius(sphereRadius);
        sphere.draw(OF_MESH_WIREFRAME);
        
        for (int i = 0; i < sounds.size(); ++i)
        {
            sounds[i]->draw(position, depth, dispNamesOn);
        }
        for (int i = 0; i < subDirs.size(); ++i)
        {
            subDirs[i]->draw(position, depth + 1, dispNamesOn);
        }
        
        if (depth < 2 && dispNamesOn)
        {
            ofPushMatrix();
            {
                ofTranslate(position);
                ofDrawBitmapString(displayName, 0, sphereRadius + 3);
            }
            ofPopMatrix();
        }
        
    }
    ofPopStyle();
}


