#pragma once

#include "ofMain.h"

class ofxKeystoneTexture {
public:
    ofxKeystoneTexture();
    ~ofxKeystoneTexture();

    void setGridSize(int w, int h);
//    ofTexture & getTextureReference();
    void setTexture(ofTexture & t);
//
//
    void draw();
//  void draw(float x, float y);
//  void draw(float x, float y, float w, float h);
//  
//  float getHeight();
//  float getWidth();
    void setPoint(int which, float x, float y);
    ofPoint getPoint(int which);
    void setPoints(ofPoint pts[4]);
    
protected:

    void updatePoints();
    int grid_size_width;
    int grid_size_height;
    ofTexture tex;

    ofVboMesh mesh;
    ofPoint p[4];
    vector<ofPoint> plane_points;
    vector<ofPoint> plane_texc;
};
