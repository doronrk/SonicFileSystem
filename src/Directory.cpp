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
                Sound* s = new Sound(myf, p, position, radius);
                sounds.push_back(s);
            }
        }
    }
    filesCached = true;
}

void Directory::setPosition(ofVec3f pos)
{
    position = pos;
}

void Directory::draw()
{
    // draw the sphere repesenting the directory
    ofSpherePrimitive sphere = ofSpherePrimitive();
    sphere.setPosition(position);
    sphere.setRadius(radius);
    sphere.draw(OF_MESH_WIREFRAME);
        
    sounds = getSounds();
    sounds[0]->draw();
    
//    // draw the orbits of the sounds
//    float orbitRadius = radius + radius;
//    // the fraction of the orbit occupied by the wave form
//    float orbitFrac = 1.0;
//    // scale factor of amplitude of wave form
//    float wavHeight = 10;
//    sounds = getSounds();
//    std::vector<std::vector<float>> data = sounds[0]->getData();
//    std::vector<float> points = data[0];
//    ofBeginShape();
//    std::cerr << "points.size(): " << points.size() <<  std::endl;
//    for (int i = 0; i < points.size(); ++i)
//    {
////        std::cerr << "i: " << i <<  std::endl;
//        float angle = i / 360.0;
//        float x = cos(angle);
//        float z = sin(angle);
//        x = x * radius;
//        z = z * radius;
//        float y = points[i] * wavHeight;
//        ofVertex(x, y, z);
//    }
//    ofEndShape();
//    std::cerr << "there" << std::endl;
}


