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

Directory::Directory(boost::filesystem::path p)
{
    path = p;
    filesCached = false;
    radius = 50;
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
    std::cerr << "updateFiles called" << std::endl;
    directory_iterator end_itr;
    int i = 0;
    for ( directory_iterator itr( path ); itr != end_itr; ++itr )
    {
        boost::filesystem::path p = itr->path();
        boost::filesystem::file_status stat = itr->status();
        if (is_directory(stat))
        {
            Directory* dir = new Directory(p);
            if (dir->isValid())
            {
                subDirs.push_back(dir);
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
                float orbitRadius = radius + (radius/2.0) * (i + 1);
                Sound* s = new Sound(myf, p, position, orbitRadius);
                sounds.push_back(s);
            }
        }
        i = i + 1;
    }
    filesCached = true;
}

void Directory::setPosition(ofVec3f pos)
{
    position = pos;
}

void Directory::update(float secondsElapsed)
{
    sounds = getSounds();
    for (int i = 0; i < sounds.size(); ++i)
    {
        sounds[i]->update(secondsElapsed);
    }
}


void Directory::draw()
{
    // draw the sphere repesenting the directory
    ofSpherePrimitive sphere = ofSpherePrimitive();
    sphere.setPosition(position);
    sphere.setRadius(radius);
    sphere.draw(OF_MESH_WIREFRAME);
        
    sounds = getSounds();
    for (int i = 0; i < sounds.size(); ++i)
    {
        sounds[i]->draw();
    }
//    sounds[0]->draw();

}


