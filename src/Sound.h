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

class Sound
{
public:
    Sound();
    ~Sound();
    bool load(boost::filesystem::path p);
    void draw();
    void setPosition(ofVec3f pos);
    ofVec3f getPosition();
    void setYAxisRotation(float rot);
    float getYAxisRotation();
    float getDist(ofVec3f p);
    void playSound();

private:
    ofSoundPlayer* player;
    std::vector<std::vector<float>> data;
    int nChannels;
    int nFrames;
    ofVec3f position;
    float yAxisRotation;
};

#endif /* defined(__SonicFileSystem__Sound__) */
