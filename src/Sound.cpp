//
//  Sound.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#include "Sound.h"

using namespace std;

Sound::Sound(SndfileHandle sndFile, boost::filesystem::path sndFilePath, ofVec3f dirCenter, float dirRadius)
{    
    player = new ofSoundPlayer();
    player->load(sndFilePath.string());
    initData(sndFile);
    orbit = new Orbit(dirCenter, dirRadius*2, nFrames, 1, 0, 0);
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
}

void Sound::draw()
{
    orbit->draw();
//    ofPushMatrix();
//        ofTranslate(position);
//        ofRotate(yAxisRotation, 0, 1.0, 0.0);
//    
//        float xScale = 25;
//        float yScale = 100;
//        float zScale = 1.0;
//        ofScale(xScale, yScale, zScale);
//    
//        ofBeginShape();
//        for (int i = 0; i < nFrames; ++i)
//        {
//            float x = data[0][i];
//            float y = ((float) i)/nFrames;
//            ofVertex(x, y, 0.0);
//        }
//        ofEndShape();
//    ofPopMatrix();
}

void Sound::playSound()
{
    player->play();
}
