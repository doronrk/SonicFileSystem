#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    std::string initDir = "/Users/Doron/Documents/Developer/openFrameworks/apps/myApps/SonicFileSystem/initDir/snare";
    
    topDir = new Directory(initDir, 50, 0.0, 0.0, nullptr);
    currentDir = topDir;

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
    inputMode = false;
    
    //////////////////////////
    //textBox.init();
    
    //ofAddListener(textBox.evtEnter, this, &ofApp::addText);
    
    cerr << "cam.getFov(): "  << cam.getFov() << endl;
}

void ofApp::exit()
{
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::update()
{
    float msElapsed = globalTimeMS - lastUpdateTime;
    float secondsElapsed = msElapsed / 1000.0;
    lastUpdateTime = globalTimeMS;
    
    //currentDir->update(secondsElapsed, 0);
    topDir->update(secondsElapsed, 0);
    
    ofVec3f dirPosition = currentDir->getPosition();
        
    float outerOrbit = currentDir->getOuterRadius();
    
    ofVec3f camPos = dirPosition - ofVec3f(0, outerOrbit, outerOrbit*2);

    cam.setPosition(camPos);
    cam.lookAt(dirPosition);

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
        topDir->draw(ofVec3f(0, 0, 0), 0, dispNamesOn);
        if (dispNamesOn)
        {
            currentDir->drawName();
            currentDir->drawSatNames();
        }
        //currentDir->draw(ofVec3f(0, 0, 0), 0, dispNamesOn);
    }
    
    ofPopStyle();
    cam.end();
    
    
    //////////////////////////////////
    //I've left the draw call as manual
    // but this could also be event driven
    // like textInput::keyPressed
    ofPushMatrix();
    ofScale(5,5);
    textBox.draw();
    ofPopMatrix();
    
    //drawEntries();
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
    if (key == OF_KEY_LEFT_COMMAND || key == OF_KEY_RIGHT_COMMAND)
    {
        inputMode = ! inputMode;
        return;
    }
    if (inputMode)
    {
        if (key == OF_KEY_RETURN)
        {
            string text = textBox.getText();
            handleTextInput(text);
            textBox.clear();
        } else {
            textBox.keyPressed(key);
        }
        return;
    }
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

void ofApp::handleTextInput(string text)
{
    int length = text.size();
    if (length < 4)
    {
        cerr << "no match" << endl;
        return;
    }
    string suffix = text.substr(3, length);
    int l = text.find("cd ");
    if (l == 0)
    {
        if (suffix.size() == 2 && suffix.find("..") == 0)
        {
            Directory* parent = currentDir->getParent();
            if (parent != nullptr)
            {
                currentDir = parent;
            }
        } else {
            Directory* newDir = currentDir->getSubDir(suffix);
            if (newDir != nullptr)
            {
                currentDir = newDir;
            }
        }
        return;
    }
    l = text.find("pl ");
    if (l == 0)
    {
        currentDir->playSound(suffix);
        return;
    }
    cerr << "no match" << endl;
}

