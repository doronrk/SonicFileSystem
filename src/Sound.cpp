//
//  Sound.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#include "Sound.h"

using namespace std;

Sound::Sound(SndfileHandle sndFile, boost::filesystem::path sndFilePath,
             float orbitRadius, float angularVelocity, std::string dispName)
{
    displayName = dispName;
    dataInitialized = false;
    player = new ofSoundPlayer();
    player->load(sndFilePath.string());
    float lfoGain = orbitRadius/100.0;
    initData(sndFile);
    orbit = new Orbit(orbitRadius, angularVelocity, nFrames, 5, 20, lfoGain);
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
    dataInitialized = true;
}


void Sound::update(float secondsElapsed)
{
    orbit->update(secondsElapsed);
}

void Sound::draw(ofVec3f dirCenter, int depth, bool dispNamesOn)
{
    if (! dataInitialized)
    {
        return;
    }
    ofPushStyle();
    {
        vector<float> d = data[0];
        orbit->draw(dirCenter, d, displayName, depth, dispNamesOn);
    }
    ofPopStyle();
}

void Sound::drawName(ofVec3f center)
{
    orbit->drawName(displayName, center);
}

void Sound::drawOrbit()
{
    orbit->drawPath();
}

void Sound::playSound()
{
    player->play();
}
