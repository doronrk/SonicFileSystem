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
              float angularVelocity, Directory* parent);
    bool isValid();
    std::vector<Directory*> getSubDirs();
    std::vector<Sound*> getSounds();
    void update(float secondsElapsed, int depth);
    void draw(ofVec3f center, int depth, bool dispNamesOn);
    void drawName();
    std::string getDisplayname();
    Directory* getSubDir(std::string displayName);
    void playSound(std::string displayName);
    Directory* getParent();
    ofVec3f getPosition();
    float getOuterRadius();
    void drawSubDirNames();
    void drawSoundNames();
    
private:
    void updateFiles();
    
    Directory* parent;
    ofColor color;
    ofVec3f center;
    Orbit* orbit;
    float sphereRadius;
    float orbitRadius;
    boost::filesystem::path path;
    std::string displayName;
    std::map<std::string, Directory*> subDirMap;
    std::map<std::string, Sound*> soundMap;
    Sound* selectedSound;
    //std::vector<Sound*> sounds;
    bool filesCached;
    
    float radiusConst;
    
    int maxDepth = 2;
    int numSatellites;
};

#endif /* defined(__SonicFileSystem__Directory__) */
