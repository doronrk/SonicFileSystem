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
             float lfoGain)
{
    int nPoints = soundFrames * soundPeriods;
    float pointsPerLFOPeriod;
    if (lfoPeriods == 0)
    {
        pointsPerLFOPeriod = 1;
    } else {
        pointsPerLFOPeriod = (float) nPoints / lfoPeriods;
    }
    points.resize(nPoints);
    for (int i = 0; i < nPoints; ++i)
    {
        float angle = ((float) i / nPoints) * 2 * PI;

        float lfoInstPhase = ((float) i / pointsPerLFOPeriod) * 2 * PI;
        float lfoAmp = sin(lfoInstPhase) * lfoGain;
        float lfoX = lfoAmp * cos(angle);
        float lfoZ = lfoAmp * sin(angle);
        
        ofVec3f centerOffset;
        centerOffset.x = (cos(angle) * radius) + lfoX;
        centerOffset.z = (sin(angle) * radius) + lfoZ;
        centerOffset.y = 0.0 * radius;
        points[i] = centerOffset + center;
    }
    
    angularVelocity = PI/4;
    headAngle = 0.0;
}

void Orbit::update(float secondsElapsed)
{
    float angularDist = secondsElapsed * angularVelocity;
    headAngle = headAngle + angularDist;
    if (headAngle > (2 * PI))
    {
        headAngle = headAngle - (2 * PI);
    }
    float progress = headAngle / (2 * PI);
    head = round(progress * points.size());
}

void Orbit::draw()
{
    // draw the path
    ofPolyline line;
    line.addVertices(points);
    line.draw();
    
    // draw the head
    ofVec3f headPos = points[head];
    ofSpherePrimitive headSphere;
    headSphere.setPosition(headPos);
    headSphere.setRadius(10);
    headSphere.draw(OF_MESH_WIREFRAME);
}