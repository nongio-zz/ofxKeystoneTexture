#include "testApp.h"
ofImage img;



int current_point = 0;
    int step = 10;
//--------------------------------------------------------------
void testApp::setup(){
    img.loadImage("fill.png");
    ktex.setTexture(img.getTextureReference());

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofNoFill();
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10,10);
    ofFill();
    ofSetColor(255,255,255);

    glPointSize(10.0);
    
    ofTranslate(200, 200);
    ktex.draw();
    ofNoFill();
    ofCircle(ktex.getPoint(current_point), 10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

    switch(key){
        case OF_KEY_RETURN:
            current_point = (current_point+1)%4;
            break;
        case OF_KEY_LEFT:
            moveLeft();
            break;
        case OF_KEY_RIGHT:
            moveRight();
            break;
        case OF_KEY_UP:
            moveUp();
            break;
        case OF_KEY_DOWN:
            moveDown();
            break;
    }

}
void testApp::moveLeft(){
    ofPoint c = ktex.getPoint(current_point);
    ktex.setPoint(current_point, c.x-step, c.y);
}
void testApp::moveRight(){
    ofPoint c = ktex.getPoint(current_point);
    ktex.setPoint(current_point, c.x+step, c.y);
}
void testApp::moveUp(){
    ofPoint c = ktex.getPoint(current_point);
    ktex.setPoint(current_point, c.x, c.y-step);
}
void testApp::moveDown(){
    ofPoint c = ktex.getPoint(current_point);
    ktex.setPoint(current_point, c.x, c.y+step);
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}