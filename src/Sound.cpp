//
//  Sound.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#include "Sound.h"

Sound::Sound()
{
    player = new ofSoundPlayer();
}

Sound::~Sound()
{
    delete player;
}

bool Sound::load(boost::filesystem::path p)
{
    bool loaded = player->load(p.string());
    if (loaded)
    {
        SndfileHandle myf = SndfileHandle(p.string());
        nChannels = myf.channels();
        nFrames = myf.frames();
        int length = nChannels * nFrames;
        float buffer [length];
        myf.read(buffer, length);
        
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
    return loaded;
}


void Sound::setPosition(ofVec3f pos)
{
    position = pos;
}

ofVec3f Sound::getPosition()
{
    return position;
}


float Sound::getDist(ofVec3f p){
    return position.distance(p);
}


void Sound::setYAxisRotation(float rot)
{
    yAxisRotation = rot;
}

float Sound::getYAxisRotation()
{
    return yAxisRotation;
}


void Sound::draw()
{
    ofPushMatrix();
        ofTranslate(position);
        ofRotate(yAxisRotation, 0, 1.0, 0.0);
    
        float xScale = 25;
        float yScale = 100;
        float zScale = 1.0;
        ofScale(xScale, yScale, zScale);
    
        ofBeginShape();
        for (int i = 0; i < nFrames; ++i)
        {
            float x = data[0][i];
            float y = ((float) i)/nFrames;
            ofVertex(x, y, 0.0);
        }
        ofEndShape();
    ofPopMatrix();
}

void Sound::playSound()
{
    player->play();
}


