#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //setting 120 fps beacuse blacktrax works at 100hz and all is the main thread
    ofSetFrameRate(120);
    
    ofxRTTrPReceiver.setup(24002);
}

//-----------------------------------------_---------------------
void ofApp::update(){
    bool newMessage = ofxRTTrPReceiver.update();
    if (newMessage){
        //retrive all objects
        vector<RTTrPM *> &pms = ofxRTTrPReceiver.getRTTrPMs();
        if(pms.size() > 0){
            cid.set(pms.at(0)->cavMod->x, - pms.at(0)->cavMod->y, pms.at(0)->cavMod->z);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 20, 20);
    
    ofSetColor(255, 0, 0);
    float centerX = ofGetWidth() / 2.0;
    float centerY = ofGetHeight() / 2.0;

    ofDrawLine(0.0, centerY, ofGetWidth(), centerY);
    ofDrawLine(centerX, 0, centerX, ofGetHeight());
    
    float size = 10;
    ofDrawEllipse(centerX + cid.x * 10.0 , centerY + cid.y * 10.0, size, size );
    
    std::stringstream label;
    label <<"x: " << cid.x <<  " y: " << cid.y << " z: " <<  cid.z << endl;
    ofDrawBitmapStringHighlight(label.str(), 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
