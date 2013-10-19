#include "ofxMeshTexture.h"

ofxMeshTexture::ofxMeshTexture(){
    setGridSize(100, 100);
    
    p[0] = ofPoint(-0.5  , -0.5);
    p[1] = ofPoint(0.5, -0.5);
    p[2] = ofPoint(0.5, 0.5);
    p[3] = ofPoint(-0.5  , 0.5);
    
    setPoints(p);

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}
ofxMeshTexture::~ofxMeshTexture(){

}

void ofxMeshTexture::setGridSize(int w, int h){
    grid_size_width = w;
    grid_size_height = h;
    updatePoints();
}
void ofxMeshTexture::draw(){
    tex.bind();
    mesh.drawWireframe();
    tex.unbind();
}

void ofxMeshTexture::setTexture(ofTexture & t){
    tex = t;
    p[0] = ofPoint(-0.5*t.getWidth(),   -0.5*t.getHeight());
    p[1] = ofPoint(0.5*t.getWidth(),    -0.5*t.getHeight());
    p[2] = ofPoint(0.5*t.getWidth(),    0.5*t.getHeight());
    p[3] = ofPoint(-0.5*t.getWidth(),   0.5*t.getHeight());
    
    setPoints(p);
    updatePoints();
}

void ofxMeshTexture::setPoint(int which, float x, float y){
    p[which].x = x;
    p[which].y = y;
    
    updatePoints();
}

ofPoint ofxMeshTexture::getPoint(int which){
    return p[which];
}

void ofxMeshTexture::setPoints(ofPoint pts[4]){
    for(int i=0; i < 4; i++)
        p[i] = pts[i];
}

void ofxMeshTexture::updatePoints(){

    mesh.clear();
    float x_res = 1.0/(grid_size_width-1);
    float y_res = 1.0/(grid_size_height-1);

    float tex_width = tex.getWidth();
    float tex_height = tex.getHeight();

    ofVec3f v01  = (p[1] - p[0]);
    ofVec3f v12  = (p[2] - p[1]);
    ofVec3f v32  = (p[2] - p[3]);
    ofVec3f v30  = (p[3] - p[0]);

    int offset_x = 0;
    int offset_y = 0;
    for(int y = 0; y < grid_size_height; y++){
        for(int x = 0; x < grid_size_width; x++){

            int index = y*grid_size_width + x;

            float pctx  = (float)x * x_res;
            float pcty  = (float)y * y_res;
            
            ofVec3f pb = (v01 * pctx) + p[0];
            ofVec3f pt = (v32 * pctx) + p[3];
            ofVec3f pl = (v30 * pcty) + p[0];
            ofVec3f pr = (v12 * pcty) + p[1];
            
            ofVec2f texc = ofVec2f(tex_width*pctx, tex_height*pcty);

            ofVec3f vec;
            vec.y = offset_y + ((pt - pb) * pcty + pb).y;
            vec.x = offset_x + ((pr - pl) * pctx + pl).x;

            mesh.addVertex(vec);
            mesh.addTexCoord(texc);
        }
    }
    
    for(int y = 0; y < grid_size_height-1; y++) {
        // even rows //
        if((y&1)==0) {
            for(int x = 0; x < grid_size_width; x++) {
                mesh.addIndex( (y) * grid_size_width + x );
                mesh.addIndex( (y+1) * grid_size_width + x);
            }
        } else {
            for(int x = grid_size_width-1; x >0; x--) {
                mesh.addIndex( (y+1) * grid_size_width + x );
                mesh.addIndex( y * grid_size_width + x-1 );
            }
        }
    }
    
    if(grid_size_height%2!=0) mesh.addIndex(mesh.getNumVertices()-grid_size_width);

}