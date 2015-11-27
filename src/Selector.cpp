//
//  Selector.cpp
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/18/15.
//
//

#include "Selector.h"

Selector::Selector()
{
    
}

void Selector::draw(ofVec3f source, ofVec3f target)
{
    ofPushMatrix();
    {
        ofTranslate(source);
        ofRotate(90, 1, 0, 0);
        ofDrawCircle(0, 0, 0, 5);
    }
    ofPopMatrix();
    ofBeginShape();
    {
        ofVertex(source);
        ofVertex(target);
    }
    ofEndShape();
}