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
    Directory(boost::filesystem::path path, float sphereRadius, float orbitRadius,
              float angularVelocity);
    bool isValid();
    std::vector<Directory*> getSubDirs();
    std::vector<Sound*> getSounds();
    void update(float secondsElapsed, int depth);
    void draw(ofVec3f center, int depth, bool dispNamesOn);
    std::string getDisplayname();
    
private:
    void updateFiles();
    
    ofColor color;
    ofVec3f center;
    Orbit* orbit;
    float sphereRadius;
    float orbitRadius;
    boost::filesystem::path path;
    std::string displayName;
    std::map<std::string, Directory*> subDirMap;
    //std::vector<Directory*> subDirs;
    Sound* selectedSound;
    std::vector<Sound*> sounds;
    bool filesCached;
    
    int maxDepth = 2;
};

#endif /* defined(__SonicFileSystem__Directory__) */
