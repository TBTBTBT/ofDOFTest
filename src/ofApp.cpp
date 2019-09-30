#include "ofApp.h"
#include "SphereObject.h"
bool enableShader = true;
float angle = 0;
//--------------------------------------------------------------
void ofApp::setup(){
	//OpenGL 2.0 glsl 1.1‚Ì‚Ý‘Î‰ž
#ifdef TARGET_OPENGLES
	//shader.load("shadersES2/shader");
#else
	//shader.load("shadersGL2/shader");
#endif
	//ofSetBackgroundAuto(false);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);  
	ofBackground(0);  
	ofSetLineWidth(2);
	Camera.setDistance(120);
	Camera.setPosition(0, 0, -20);
	Camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	Sphere = new SphereObject();
	Sphere->Setup();
	gui.setup();
	gui.add(duration.setup("duration", 0,-3,3));
	gui.add(stack.setup("stack", 0, 0, 100));
	gui.add(rotationY.setup("rotationY", 0, 0, 720));
	gui.add(shrinkWeight.setup("shrinkWeight", 0, -2, 2));
	gui.add(radius.setup("radius", 10, 0, 20));
	depthOfField.setup(ofGetWidth(), ofGetHeight());
	depthOfField.setFocalRange(10);
	depthOfField.setFocalDistance(5);
	depthOfField.setBlurAmount(1);
	particles.setup();
	glPointSize(5);
	//Camera.disableMouseInput();
}

//--------------------------------------------------------------
void ofApp::update(){
	//depthOfField.setFocalDistance(ofMap(sin(ofGetElapsedTimef() / 2), -1, 1, 20, 150));
	angle += 0.5f;
	duration = ofNoise(angle/100) * 6 - 3;
	//Camera.move(Camera.getXAxis()*1 + Camera.getZAxis());
	//Camera.getOrientationEuler
	Sphere->Update();
	Sphere->SetParam(radius,3,angle);
	particles.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//ofDisableDepthTest();
	//ofDrawBitmapString(ofToString(Camera.getZAxis()),0,100);

	//ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2,-50);
	//ofEnableDepthTest();
	if (enableShader) {
		depthOfField.begin();
	}
	Camera.begin(depthOfField.getDimensions());
	particles.draw();
	//ofNoFill();
	//ofPushMatrix();
	//ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	Sphere->Draw();
	
	//ofPopMatrix();
	Camera.end();
	if (enableShader) {
		depthOfField.end();
		depthOfField.getFbo().draw(0, 0);
	}
	gui.draw();
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
