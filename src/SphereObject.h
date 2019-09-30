#pragma once
#include "ofMain.h"
#include "ofTimeline.h"

using namespace std;

class SpherePoly  {
public:
	vector<ofVec3f> Verts;
	vector<ofFloatColor> Colors;
	ofVbo Vbo;
	int currentSlice = 0;
	int slices = 50;
	int stacks = 50;
	float durationWeight = 0;
	float height = 16;
	float low=5;
	float radiusY = 25;
	float radiusX = 25;
	void init(int maxSlice, int maxStack, int slice);
	void update();
	void drawPolygon();
private:
	void addVertex(ofVec3f vert, ofFloatColor color = ofFloatColor(1, 1, 1));
	void moveVertex(int index, ofVec3f vert, ofFloatColor color = ofFloatColor(1, 1, 1));
    
	ofVec3f spherePos(int count);
};
class SphereObject
{
public:
	
	SphereObject();
	~SphereObject();
	void Setup();
	void Update();
	void Draw();
	void SetParam(float rad, float durationWeight, float angle);
	//ofVbo Vbo;
	//ofVbo Vbo2;
	//vector<ofVec3f> Verts;
	//vector<ofFloatColor> Colors;
	ofPoint Position = ofPoint(0, 0, 0);
private:
	int frameCount = 0;
	int slices = 50;
	int stacks = 50;
	float angleZ = 0;
	void reset();
	void moveUp();
	void stay();
	void moveDown();
	void setTimeline();
	void addCount();
	vector<SpherePoly> polygons;
	//ofVec3f spherePos(int stackIndex, int sliceIndex, int count);
	ofTimeline timeline_;
};

