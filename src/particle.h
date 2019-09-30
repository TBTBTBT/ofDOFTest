#pragma once
#include "ofMain.h"
struct particle
{
public:
	float z;
	float angle;
	float speed;
	float y;
};

class particleSet {
public:
	void setup();
	void update();
	void draw();
private:
	float frameCount = 0;
	vector<particle> particle;
	vector<ofVec3f> particlePos;
	ofVbo vbo;
};