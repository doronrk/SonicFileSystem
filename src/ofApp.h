#pragma once

#include "ofMain.h"
#include "Entity.h"
#include "Directory.h"
#include "Selector.h"

//#define PI 3.14159265

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
   
    void audioOut( ofSoundBuffer& buffer );

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
    void setDirectory(std::string path);
    
    
    ofEasyCam cam;
    Directory* currentDir;
    std::vector<Sound*> sounds;
    Sound* targetSound;
    Selector* selector;
    
    bool upPress;
    bool downPress;
    bool leftPress;
    bool rightPress;
    
    
    float sceneRadius = 500;
    float vertOffSet = -40;
};
