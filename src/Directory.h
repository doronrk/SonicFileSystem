//
//  Directory.h
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#ifndef __SonicFileSystem__Directory__
#define __SonicFileSystem__Directory__

#include <stdio.h>
#include <boost/filesystem.hpp>
#include "Sound.h"
#include "ofMain.h"
#include "Orbit.h"

class Directory
{
public:
    Directory(boost::filesystem::path path);
    bool isValid();
    std::vector<Directory*> getSubDirs();
    std::vector<Sound*> getSounds();
    void setPosition(ofVec3f pos);
    void update(float secondsElapsed);
    void draw();
//    std::vector<Sound> getSoundsRecursively();

private:
    void updateFiles();
    
    
    ofVec3f position;
    float radius;
    boost::filesystem::path path;
    std::vector<Directory*> subDirs;
    std::vector<Sound*> sounds;
    bool filesCached;
};

#endif /* defined(__SonicFileSystem__Directory__) */
