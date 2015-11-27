//
//  Orbit.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/27/15.
//
//

#include "Orbit.h"

using namespace std;

Orbit::Orbit(ofVec3f center,
             float radius,
             int soundFrames,
             int soundPeriods,
             int lfoPeriods,
             float lfoAmp)
{
    int nPoints = soundFrames * soundPeriods;
    points.resize(nPoints);
    cerr << "points.size(): " << points.size() << endl;
}


void Orbit::draw()
{
    
}