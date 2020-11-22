#include "ofApp.h"

Curve* c;
vector<Curve*> curves;

float angle;
float split_fraction;

float lastTime;
int lastRefresh = -1;

float minX, minY, maxX, maxY;

//--------------------------------------------------------------
void ofApp::setup(){
    keyPressed('1');
}

//--------------------------------------------------------------
void ofApp::update(){
    if(ofGetElapsedTimef() - lastTime < 0.1 && curves.size() < 100000 && ofGetFrameNum() - lastRefresh < 100)
    {
        split();
        lastTime = ofGetElapsedTimef();
    }
    else if(ofGetFrameNum() - lastRefresh >= 50)
    {
        keyPressed('1');
        lastRefresh = ofGetFrameNum();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofSetLineWidth(2);
    glPushMatrix();
    float scaleX = (float)(ofGetWidth()) / (maxX - minX);
    float scaleY = (float)(ofGetHeight()) / (maxY - minY);
    float scale = scaleX < scaleY ? scaleX : scaleY;
    glScalef(scale, scale, scale);

    glTranslatef(-minX, -minY, 0);
    for(int i=0;i<curves.size();i++)
    {
        ofColor c;
        c.setHsb(220 * i / ((float)curves.size()-1),255,255, ofClamp(255 * 20000 / (float)curves.size(),1,255));
        ofSetColor(c);
        curves[i]->draw();
    }
    
    glPopMatrix();
}

void ofApp::split()
{
    curves.clear();
    Curve* cc = c;
    while(cc)
    {
        curves.push_back(cc);
        cc = cc->next;
    }
    cout<<curves.size()<<endl;
    cout<<minX<<" "<< minY<<" "<<maxX<<" "<<maxY<<endl;

    minX = 99999;
    minY = 99999;
    maxX = -99999;
    maxY = -99999;
    for(int i=0;i<curves.size();i++)
    {
        if(curves[i]->pts[0].x < minX) minX = curves[i]->pts[0].x;
        if(curves[i]->pts[0].y < minY) minY = curves[i]->pts[0].y;
        if(curves[i]->pts[0].x > maxX) maxX = curves[i]->pts[0].x;
        if(curves[i]->pts[0].y > maxY) maxY = curves[i]->pts[0].y;
        curves[i]->split(angle, split_fraction);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
    {
        
    }
    if(key == '1')
    {
        for(int i=0;i<curves.size();i++)
        {
            delete curves[i];
        }
        curves.clear();
        c = new Curve(ofVec2f(ofGetWidth()*0.25, ofGetHeight() * 0.5), ofVec2f( ofGetWidth()*0.75, ofGetHeight()* 0.5));
        curves.push_back(c);
        angle = ofRandom(360);
        split_fraction = ofRandom(1.2,2);
        
        cout<<angle<<" "<<split_fraction<<endl;
        lastTime = ofGetElapsedTimef();
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
