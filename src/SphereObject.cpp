#include "SphereObject.h"
#include "ofMain.h"
using namespace std::experimental;






ofVec3f SpherePoly::spherePos(int count) {

	/*int actualStack = stackIndex + (loopCount + 1) % 2;
	float posY = cos(PI * actualStack / stacks) * radius;
	float posX = cos(PI * 2 * currentSlice / slices)*radius *sin(PI * actualStack / stacks);
	float posZ = sin(PI * 2 * currentSlice / slices)*radius *sin(PI * actualStack / stacks);
	return ofVec3f(posX, posY, posZ);*/
	//int actualSlice = currentSlice;//(count % 2) ? currentSlice + 1 : currentSlice;
	//int stackIndex = count;
	//float posY = cos(PI * stackIndex / stacks) * radiusY;
	//float posX = cos(PI * 2 * actualSlice / slices)*radiusX *sin(PI * stackIndex / stacks);
	//float posZ = sin(PI * 2 * actualSlice / slices)*radiusX *sin(PI * stackIndex / stacks);
	float distortion = ((float)count / 10) * durationWeight;
	float posY = cos(PI * count / stacks) * radiusY;
	float posX = cos(2 * PI * (distortion + currentSlice) / slices)* radiusX * sin(PI * count / stacks);
	float posZ = sin(2 * PI * (distortion + currentSlice) / slices)*radiusX * sin(PI * count / stacks);
	return ofVec3f(posX, posY, posZ);
}

void SpherePoly::moveVertex(int index, ofVec3f vert, ofFloatColor color)
{ 

}

void SpherePoly::init(int maxSlice,int maxStack, int slice)
{
	currentSlice = slice;
	stacks = maxStack;
	slices = maxSlice;
	//addVertex(spherePos(0));
	for (int i = 0; i < stacks + 1; i++) {
		addVertex(spherePos(i),ofFloatColor(1,1,1,1));
	}
	Vbo.setVertexData(&Verts[0], Verts.size(), GL_DYNAMIC_DRAW);
	Vbo.setColorData(&Colors[0], Colors.size(), GL_DYNAMIC_DRAW);
}

void SpherePoly::update()
{
	//x = left , y = right
	for (int i = 0; i < stacks + 1; i++) {
		Verts[i] = spherePos(i);
	}
	Vbo.updateVertexData(&Verts[0], Verts.size());
}

void SpherePoly::drawPolygon()
{
	Vbo.draw(GL_LINE_STRIP, min(low, (float)Verts.size()), min((float)Verts.size() - low ,height));
	//Vbo.draw(GL_QUADS, 0, Verts.size());
}

void SpherePoly::addVertex(ofVec3f vert, ofFloatColor color)
{
	Verts.push_back(vert);
	Colors.push_back(color);
	
}


SphereObject::SphereObject()
{
}


SphereObject::~SphereObject()
{
}


void SphereObject::addCount() {
	/*if (loopCount % 2 == 1) {
		currentSlice = (currentSlice + 1) % (slices);
		if (currentSlice == 0) {
			currentStack = (currentStack + 1) % stacks;
		}

	}*/
}

ofVec3f lerp(ofVec3f s,ofVec3f e,float time) {
	return e * time + s * (1 - time);
}
void SphereObject::reset()
{
	for (auto& element : polygons) {
		element.low = 0;
		element.height = 0;
	}
}
void SphereObject::moveUp()
{

	for (auto& element : polygons) {
		element.height++;
	}
}
void SphereObject::stay()
{
}
void SphereObject::moveDown()
{
	for (auto& element : polygons) {
		element.low++;
		
		
	}
}
void SphereObject::setTimeline()
{
	timeline_.addKey(0, [&] {this->reset(); });
	timeline_.addKey(1, [&] {this->moveUp(); });
	timeline_.addKey(102, [&] {this->stay(); });
	timeline_.addKey(112, [&] {this->moveDown(); });
	timeline_.addKey(213, nullptr);
	timeline_.end(223,true);
}
void SphereObject::Setup() 
{
	stacks = 100;
	slices =50;
	for (int i = 0; i <slices; i++) {
		auto polygon = SpherePoly();
		polygon.init(slices, stacks,i);
		polygons.push_back(polygon);
		
	}
	setTimeline();

	//Mesh.
	//Verts.push_back(ofVec3f(0, 0, 0));
	//Colors.push_back(ofFloatColor(1, 1, 1,0.1f));
	//Vbo.setVertexData(&Verts[0],Verts.size(), GL_DYNAMIC_DRAW);
	//Vbo2.setVertexData(&Verts[0], Verts.size(), GL_DYNAMIC_DRAW);
	//setTimeline();
}

void SphereObject::Update()
{
	frameCount++;
	for each (auto element in polygons) {
		element.update();
	}

	timeline_.update();
	
	
}

void SphereObject::Draw() {
	ofPushMatrix();
	ofRotateY(angleZ);
	for each (auto element in polygons ) {
		element.drawPolygon();
	}
	ofPopMatrix();
	//ofDrawSphere(Position, 10.0);
	
	//Vbo2.draw(GL_TRIANGLE_STRIP, 0, Verts.size() - 1);
	//Vbo.draw(GL_LINES, 0, Verts.size());
}

void SphereObject::SetParam(float rad, float durationWeight,float angle)
{
	
	for (auto& element : polygons) {
		element.durationWeight = durationWeight;
		element.radiusY = rad;
		element.radiusX = rad;

	}
	angleZ = angle;
}

// SinglePoly ---

//void SinglePoly::addVertex(ofVec3f vert,ofFloatColor color = ofFloatColor(1,1,1))
//{
//	
//}
//
//void SinglePoly::moveVertex(int index, ofVec3f vert, ofFloatColor color = ofFloatColor(1, 1, 1))
//{
//}
//
//void SinglePoly::drawPolygon()
//{
//	
//}

// SpherePoly ---

