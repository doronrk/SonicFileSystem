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
    this->center = center;
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
        centerOffset.z = - (sin(angle) * radius) - lfoZ;
        centerOffset.y = 0.0 * radius;
        points[i] = centerOffset + center;
    }
    
    angularVelocity = -PI/2;
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

void Orbit::draw(const vector<float> data)
{
    vector<ofPoint> wavFormPoints;
    wavFormPoints.resize(data.size());
    int signOfVelocity;
    if (angularVelocity < 0)
    {
        signOfVelocity = -1;
    } else
    {
        signOfVelocity = 1;
    }
    for (int i = 0; i < data.size(); ++i)
    {
        float amp = data[i] * 10;
        int pointIndex = (head + (signOfVelocity * -1) * i);
        if (pointIndex < 0)
        {
            pointIndex = points.size() + pointIndex;
        }
        wavFormPoints[i] = points[pointIndex];
        wavFormPoints[i].y = data[i] * 10.0;
    }
    ofPolyline wavForm = ofPolyline(wavFormPoints);
    wavForm.draw();
}

void Orbit::drawTubes(const std::vector<float> data)
{
    int signOfVelocity;
    if (angularVelocity < 0)
    {
        signOfVelocity = -1;
    } else
    {
        signOfVelocity = 1;
    }
    for (int i = 0; i < data.size(); i = i + 16)
    {
        float amp = data[i] * 10;
        int pointIndex = (head + (signOfVelocity * -1) * i);
        if (pointIndex < 0)
        {
            pointIndex = points.size() + pointIndex;
        }
        ofVec3f point = points[pointIndex];
        
        ofPushMatrix();
        {
            ofNoFill();
            float rotation = ((float) pointIndex / points.size());
            rotation = rotation * 360.0;
            ofTranslate(point);
            ofRotateY(rotation);
            ofDrawCircle(ofVec3f(0, 0, 0), data[i] * 10.0);
        }
        ofPopMatrix();
        ofPopMatrix();
    }
}

void Orbit::drawPath()
{
    // draw the path
    ofPolyline line;
    line.addVertices(points);
    line.draw();
    
    // draw the head
    ofVec3f headPos = points[head];
    
    ofPushMatrix();
    {
        ofNoFill();
        float rotation = ((float) head / points.size());
        rotation = rotation * 360.0;
        ofTranslate(headPos);
        ofRotateY(rotation);
        ofDrawCircle(ofVec3f(0, 0, 0), 10.0);
    }
    ofPopMatrix();
    
    
//    
//    ofSpherePrimitive headSphere;
//    headSphere.setPosition(headPos);
//    headSphere.setRadius(10);
//    headSphere.draw(OF_MESH_WIREFRAME);
}