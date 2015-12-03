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
    Directory(boost::filesystem::path path, float sphereRadius, float orbitRadius);
    bool isValid();
    std::vector<Directory*> getSubDirs();
    std::vector<Sound*> getSounds();
    void update(float secondsElapsed);
    void draw();
    
private:
    void updateFiles();
    
    ofVec3f center;
    Orbit* orbit;
    float sphereRadius;
    boost::filesystem::path path;
    std::vector<Directory*> subDirs;
    Sound* selectedSound;
    std::vector<Sound*> sounds;
    bool filesCached;
};

#endif /* defined(__SonicFileSystem__Directory__) */
