#pragma once

#include "ofMain.h"
#include "Directory.h"
#include "textInput.h"

//#define PI 3.14159265

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
   
    void audioIn( ofSoundBuffer& buffer );

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
private:
    
    void handleTextInput(string text);
    
    ofImage background;
    
    ofEasyCam cam;
    Directory* topDir;
    Directory* currentDir;
    
    bool dispNamesOn;
    bool upPress;
    bool downPress;
    bool leftPress;
    bool rightPress;
    
    bool inputMode;
    
    float sceneRadius = 500;
    float vertOffSet = -40;
    
    float globalTimeMS;
    float lastUpdateTime;
    
    ofVec3f camLookAtPoint;
    
    //////////////
    textInput textBox;
    
    /////
    //for the purpose of this example
    //vector<string> textEntries;
    //void addText(string& s);
    //void drawEntries();
};
