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
            Sound* s = new Sound();
            bool success = s->load(p);
            if (success)
            {
                sounds.push_back(s);
            } else
            {
                delete s;
            }
        }
    }
    filesCached = true;
}


