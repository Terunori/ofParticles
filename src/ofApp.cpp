#include "ofApp.h"

//--------------------------------------------------------------
// variables

//Numbers of circles
static const int NUM = 1000;

float loc_x[NUM];
float loc_y[NUM];
float speed_x[NUM];
float speed_y[NUM];
float radius[NUM];
int red[NUM];
int green[NUM];
int blue[NUM];
bool mouse_pressed;
float gravity;
float friction;

int pmouseX, pmouseY;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    mouse_pressed = false;
    gravity = 1.0;
    friction = 0.999;
    
    //make initial value by NUM times
    for(int i=0;i<NUM;i++){
        // position
        loc_x[i] = ofGetWidth()/2;
        loc_y[i] = ofGetHeight()/2;
        
        //speed
        speed_x[i] = ofRandom(-10, 10);
        speed_y[i] = ofRandom(-10, 10);
        
        // radius
        radius[i] = ofRandom(1, 10);
        
        // color
        red[i] = ofRandom(0, 255);
        green[i] = ofRandom(0, 255);
        blue[i] = ofRandom(0, 255);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0;i<NUM;i++){
        // gather to mouse
        if(mouse_pressed){
            speed_x[i] = (mouseX - loc_x[i]) / 8.0;
            speed_y[i] = (mouseY - loc_y[i]) / 8.0;
        }
        
        // calc force by friction and gravity
        speed_x[i] *= friction;
        speed_y[i] *= friction;
        speed_y[i] += gravity;
        
        // update position of particles
        loc_x[i] += speed_x[i];
        loc_y[i] += speed_y[i];
        
        // boundary
        if(loc_x[i] < 0){
            // periodic boundary-condition
            // loc_x[i] = ofGetWidth();
            loc_x[i] = 0;
            speed_x[i] *= -0.9;
        } else if (loc_x[i] > ofGetWidth()){
            // periodic boundary-condition
            // loc_x[i] = 0;
            loc_x[i] = ofGetWidth();
            speed_x[i] *= -0.9;
        }
        
        if (loc_y[i] > ofGetHeight()){
            loc_y[i] = ofGetHeight();
            speed_y[i] *= -0.8;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0,0,0,23);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    // draw NUM circles
    for(int i=0; i<NUM; i++){
        ofSetColor(red[i], green[i], blue[i], 127);
        ofDrawCircle(loc_x[i], loc_y[i], radius[i]);
    }
    
    if (mouse_pressed) {
        ofSetColor(200, 200, 200, 100);
        ofDrawCircle(pmouseX, pmouseY, 10);
        ofDrawCircle(mouseX, mouseY, 5);
        ofSetColor(200, 200, 200, 200);
        ofDrawLine(pmouseX, pmouseY, mouseX, mouseY);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_pressed = true;
    pmouseX = x;
    pmouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouse_pressed = false;
    
    for(int i=0; i<NUM; i++){
        int theta = ofRandom(0,360);
        int dist = ofRandom(-10,10);
        speed_x[i] = (x-pmouseX)/5 + dist*sin(theta);
        speed_y[i] = (y-pmouseY)/5 + dist*cos(theta);
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
