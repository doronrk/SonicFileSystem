//
//  Orbit.h
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/27/15.
//
//

#ifndef __SonicFileSystem__Orbit__
#define __SonicFileSystem__Orbit__

#include <stdio.h>
#include "ofMain.h"

class Orbit
{
public:
    Orbit(ofVec3f center,
          float radius,
          int soundFrames,
          int soundPeriods,
          int lfoPeriods,
          float lfoGain);
    
    void update(float secondsElapsed);
    void draw();
private:
    std::vector<ofVec3f> points;
    // radians per second
    float angularVelocity;
    float headAngle;
    int head;
};
#endif /* defined(__SonicFileSystem__Orbit__) */
