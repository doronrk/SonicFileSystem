#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    std::string initDir = "/Users/Doron/Documents/Developer/openFrameworks/apps/myApps/SonicFileSystem/initDir/snare";
//    currentDir = new Directory(initDir);
//    sounds = currentDir->getSounds();
    
    setDirectory(initDir);

    //Camera setup
    cam.begin();
    cam.setGlobalPosition(0, 0, 0);
    cam.setFov(60.0);
    cam.end();
    cam.enableMouseInput();
    
    // scene setup
    sceneRadius = 500;
    vertOffSet = -40;
}

//--------------------------------------------------------------
void ofApp::setDirectory(std::string path)
{
    Directory* newDir = new Directory(path);
    std::vector<Sound*> newSounds = newDir->getSounds();
    delete currentDir;
    sounds.clear();
    currentDir = newDir;
    sounds = newSounds;
    
    // set position and rotation of sounds
    int nSounds = sounds.size();
    
    for (int i = 0; i < nSounds; ++i)
    {
        float yRot = 360.0/nSounds * i;
        ofVec3f pos = ofVec3f(0, vertOffSet, -sceneRadius);
        pos = pos.getRotated(yRot, ofVec3f(0, 1, 0));
        sounds[i]->setPosition(pos);
        sounds[i]->setYAxisRotation(yRot);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (upPress)
    {
        ofVec3f dir = cam.getLookAtDir();
        dir = dir.normalize();
        dir = dir*3;
        cam.move(dir);
    }
    if (downPress)
    {
        ofVec3f dir = cam.getLookAtDir();
        dir = dir.normalize();
        dir = dir*-3;
        cam.move(dir);
    }
    if (leftPress)
    {
        cam.rotate(1, 0, 1, 0);
    }
    if (rightPress)
    {
        cam.rotate(-1, 0, 1, 0);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    cam.begin();
    
    
    ofPushStyle();
    {
        ofNoFill();
        ofEnableSmoothing();
    
        ofSetColor(255, 255, 255);
        
        ofVec3f dir = cam.getLookAtDir();
        ofVec2f dir2d = ofVec2f(dir.x, dir.z);
        ofVec2f orthDir = dir2d.getPerpendicular();
        orthDir = orthDir.normalize();
        orthDir = orthDir;
        dir2d = dir2d.normalize();
        
        float minProj = INFINITY;
        
        // draw sounds, find aimed at sound
        int nSounds = sounds.size();
        targetSound = nullptr;
        for (int i = 0; i < nSounds; ++i)
        {
            sounds[i]->draw();
            ofVec3f soundP = sounds[i]->getPosition();
            ofVec3f zerodSoundP = soundP - cam.getGlobalPosition();
            ofVec2f soundP2d = ofVec2f(zerodSoundP.x, zerodSoundP.z);
            float proj = soundP2d.dot(orthDir);
            proj = abs(proj);
            if (proj < minProj && (soundP2d.dot(dir2d) >= 0))
            {
                minProj = proj;
                targetSound = sounds[i];
            }
        }
    
        // draw selector
        if (targetSound != nullptr)
        {
            ofVec3f p = cam.getGlobalPosition();
            dir = dir.normalize();
            dir = dir*100;
            ofVec3f selectorSource = p + dir;
            selectorSource.y = vertOffSet;
            ofVec3f selectorTarget = targetSound->getPosition();
            selector->draw(selectorSource, selectorTarget);
        }
    }
    
    ofPopStyle();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::audioOut( ofSoundBuffer& buffer )
{
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == OF_KEY_UP)
    {
        upPress = true;
    } else if (key == OF_KEY_DOWN)
    {
        downPress = true;
    } else if (key == OF_KEY_LEFT)
    {
        leftPress = true;
    } else if (key == OF_KEY_RIGHT)
    {
        rightPress = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == OF_KEY_UP)
    {
        upPress = false;
    } else if (key == OF_KEY_DOWN)
    {
        downPress = false;
    } else if (key == OF_KEY_LEFT)
    {
        leftPress = false;
    } else if (key == OF_KEY_RIGHT)
    {
        rightPress = false;
    } else if (key == 'r')
    {
        if (targetSound != nullptr)
        {
            targetSound->playSound();
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
