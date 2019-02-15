#include "flowField.h"

void flowField::setup(int r){
    resolution = r;
    cols = ofGetWidth()/resolution;
    rows = ofGetHeight()/resolution;

    field.resize(cols);
    for (int i = 0; i < cols; i++){
        field[i].resize(rows);
    }
    init();

}

void flowField::init(){
    // Reseed noise so we get a new flow field every time
    
    //processing: noiseSeed((int)random(10000));
    //ofSeedRandom(); --this doesn't change anything
    // is noiseSeed implemented in oF yet?
    // in the mean time, use a random start value:
    float xoff_seed = ofRandom(0,1);
    float yoff_seed = ofRandom(0,1);
    
    float xoff = xoff_seed;
    for (int i = 0; i < cols; i++) {
        float yoff = yoff_seed;
        for (int j = 0; j < rows; j++) {
            float theta = ofMap(ofNoise(xoff,yoff),0,1,0,TWO_PI);
            // Polar to cartesian coordinate transformation to get x and y components of the vector
            field[i][j].set(cos(theta),sin(theta));
            yoff += 0.03;
        }
        xoff += 0.03;
    }
}


void flowField::draw(){
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            drawVector(field[i][j],i*resolution,j*resolution,resolution-2);
        }
    }
}


void flowField::drawVector(const ofPoint & v, float x, float y, float scayl){
    
    ofSetColor(ofColor::dodgerBlue, 127);
    
    ofPushMatrix();
    float arrowsize = 4;
    // Translate to location to render vector
    ofTranslate(x,y);
    //stroke(0,100);
    // Call vector heading function to get direction (note that pointing up is a heading of 0) and rotate
    ofRotate(ofPoint(1,0).angle(v));
    // Calculate length of vector & scale it to be bigger or smaller if necessary
    float len = v.length()*scayl;
    // Draw three lines to make an arrow (draw pointing up since we've rotate to the proper direction)
    ofDrawLine(0,0,len,0);
    ofDrawLine(len,0,len-arrowsize,+arrowsize/2);
    ofDrawLine(len,0,len-arrowsize,-arrowsize/2);
    ofPopMatrix();
}

ofPoint flowField::lookup(const ofPoint & lookup) const{
    int column = int(ofClamp(lookup.x/resolution,0,cols-1));
    int row = int(ofClamp(lookup.y/resolution,0,rows-1));
    return field[column][row];
}




