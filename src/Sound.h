//
//  Sound.h
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#ifndef __SonicFileSystem__Sound__
#define __SonicFileSystem__Sound__

#include <stdio.h>
#include <boost/filesystem.hpp>
#include <sndfile.hh>
#include "ofMain.h"
#include "Orbit.h"

class Sound
{
public:
    Sound(SndfileHandle sndFile, boost::filesystem::path sndFilePath, float orbitRadius,
          float angularVelocity);

    ~Sound();
    void update(float secondsElapsed);
    void draw(ofVec3f dirCenter);
    void drawOrbit();
    void playSound();

private:
    void initData(SndfileHandle sndFile);
    
    Orbit* orbit;
    ofSoundPlayer* player;
    std::vector<std::vector<float>> data;
    int nChannels;
    int nFrames;
    bool dataInitialized;
};

#endif /* defined(__SonicFileSystem__Sound__) */
