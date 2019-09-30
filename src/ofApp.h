#pragma once

#include "ofMain.h"
#include "SphereObject.h"
#include "ofxGui.h"
#include "ofxDOF.h"
#include "particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		ofEasyCam Camera;
		SphereObject* Sphere;
		ofxPanel gui;
		ofxFloatSlider duration;
		ofxFloatSlider stack;
		ofxFloatSlider rotationY;
		ofxFloatSlider shrinkWeight;
		ofxFloatSlider radius;
		particleSet particles;
		//ofxFloatSlider shrinkWeight;
		ofShader shader;
		ofxDOF depthOfField;
};
