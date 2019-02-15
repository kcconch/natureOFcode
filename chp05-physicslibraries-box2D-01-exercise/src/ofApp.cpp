// read more details on shared_ptr at:
// http://en.cppreference.com/w/cpp/memory/shared_ptr

#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(ofColor::beige);
    
    box2d.init();
    box2d.setFPS(60.0);
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    
    float w = 16;
    float h = 16;
    boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(1.0, 0.5, 0.3);
//    setPhysics(float density, float bounce, float friction)
    boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
    
    // remove shapes offscreen
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    cout << "boxes amount: " << boxes.size() << endl;
}


//--------------------------------------------------------------
void ofApp::draw() {
    
    for(auto & b : boxes) {
        ofSetHexColor(0xBF2545);
        b->draw();
    }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) { }
//--------------------------------------------------------------
void ofApp::keyReleased(int key) { }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) { }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) { }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) { }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) { }
//--------------------------------------------------------------
void ofApp::resized(int w, int h){ }

