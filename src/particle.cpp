#include "particle.h"




void particleSet::setup()
{
	for(auto i = 0;i < 100;i ++){
		particle.push_back(
			{
				ofRandom(10,50),
				ofRandom(0,359),
				ofRandom(1,10),
				ofRandom(0,5)
				
			}
		);
	}
	
}

void particleSet::update()
{
	frameCount += 1.;
	for (int i = 0; i < particle.size(); i++ ) {
		float a = particle[i].angle + particle[i].speed * frameCount;
		float x = particle[i].z * cos(PI * a / 180);
		float y = particle[i].y;
		float z = particle[i].z * sin(PI * a / 180);
		if (i >= particlePos.size()) {
			particlePos.push_back(ofVec3f(x,y,z));
		}
		else 
		{
			particlePos[i] = ofVec3f(x, y, z);
		}
	}
	vbo.setVertexData(&particlePos[0], particle.size(),GL_DYNAMIC_DRAW);
}

void particleSet::draw()
{
	vbo.draw(GL_POINTS,0,particlePos.size());
}
