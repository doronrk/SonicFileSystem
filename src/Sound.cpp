//
//  Sound.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#include "Sound.h"

using namespace std;

Sound::Sound(SndfileHandle sndFile, boost::filesystem::path sndFilePath, ofVec3f dirCenter, float orbitRadius)
{    
    player = new ofSoundPlayer();
    player->load(sndFilePath.string());
    initData(sndFile);
    orbit = new Orbit(dirCenter, orbitRadius, nFrames, 5, 20, 5);
}

Sound::~Sound()
{
    delete player;
}

void Sound::initData(SndfileHandle sndFile)
{
    nChannels = sndFile.channels();
    nFrames = sndFile.frames();
    int length = nChannels * nFrames;
    float buffer [length];
    sndFile.read(buffer, length);
    
    data.resize(nChannels, std::vector<float>());
    for(int channelNum = 0; channelNum < nChannels; ++channelNum)
    {
        data[channelNum].resize(nFrames, 0.0);
        for(int frameNum = 0; frameNum < nFrames; ++frameNum)
        {
            int i = frameNum * nChannels + channelNum;
            data[channelNum][frameNum] = buffer[i];
        }
    }
}


void Sound::update(float secondsElapsed)
{
    orbit->update(secondsElapsed);
    bool crossedZero = orbit->getAndResetCrossedZero();
    if (crossedZero)
    {
        player->play();
    }
}

void Sound::draw()
{
    ofPushStyle();
    {
        ofColor soundColor;
        soundColor = soundColor.tomato;
        ofSetColor(soundColor);
        orbit->draw(data[0]);
    }
    ofPopStyle();
}

void Sound::drawOrbit()
{
    orbit->drawPath();
}

void Sound::playSound()
{
    player->play();
}
