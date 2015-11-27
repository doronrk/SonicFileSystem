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
    for (int i = 0; i < nPoints; ++i)
    {
        float angle = ((float) i / nPoints) * 360.0;
        ofVec3f centerOffset;
        centerOffset.x = cos(angle) * radius;
        centerOffset.z = sin(angle) * radius;
        centerOffset.y = 0.0 * radius;
        points[i] = centerOffset + center;
    }
}


void Orbit::draw()
{
    ofPolyline line;
    line.addVertices(points);
    line.draw();
}