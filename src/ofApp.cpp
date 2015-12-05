#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    std::string initDir = "/Users/Doron/Documents/Developer/openFrameworks/apps/myApps/SonicFileSystem/initDir/snare";
    
    setDirectory(initDir);

    //Camera setup
    cam.begin();
    cam.setGlobalPosition(0, 0, 0);
    cam.setFov(60.0);
    cam.end();
    cam.enableMouseInput();
    
    // audio setup
    ofSoundStreamSetup(0, 2, 44100, 256, 4);
    
    // scene setup
    sceneRadius = 500;
    vertOffSet = -40;
    background = ofImage("/Users/Doron/Documents/Developer/openFrameworks/apps/myApps/SonicFileSystem/bin/data/stars.jpg");
    
    // variable init
    globalTimeMS = 0;
    lastUpdateTime = 0;
    dispNamesOn = false;
}

void ofApp::exit()
{
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::setDirectory(std::string path)
{
    Directory* newDir = new Directory(path, 50, 0.0, 0.0);
    std::vector<Sound*> newSounds = newDir->getSounds();
    delete currentDir;
    sounds.clear();
    currentDir = newDir;
    sounds = newSounds;
}

//--------------------------------------------------------------
void ofApp::update()
{
    float msElapsed = globalTimeMS - lastUpdateTime;
    float secondsElapsed = msElapsed / 1000.0;
    lastUpdateTime = globalTimeMS;

    currentDir->update(secondsElapsed, 0);
    
    // update camera position
    
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
    ofEnableSmoothing();
    ofBackground(0, 0, 0);
    //background.draw(0, 0);
    ofSetDepthTest(true);
    cam.begin();
    
    ofPushStyle();
    {
        currentDir->draw(ofVec3f(0, 0, 0), 0, dispNamesOn);
    }
    
    ofPopStyle();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::audioIn( ofSoundBuffer& buffer )
{
    globalTimeMS = globalTimeMS + buffer.getDurationMicros() / 1000.0;
    buffer.set(0);
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
        dispNamesOn = !dispNamesOn;
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
