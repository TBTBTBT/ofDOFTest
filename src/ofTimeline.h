#pragma once
#include "ofMain.h"
#define FRAME_COUNT 0;
#define MILLI_SECONDS 1;
using namespace std;
typedef void(*FUNC)();
class Key {
public:
	Key(int time, function<void()> func);
	Key(int time);
	int startTime;
	bool isEndFlag = false;
	function<void()> func;
};
class ofTimeline
{
public:
	ofTimeline();
	~ofTimeline();
	void reset();
	void update();
	void addKey(int time, function<void()> func);
	void end(int time,bool loop = false);
	float normalizedTime();
private:
	void action();
	Key* current();
	Key* next();
	int _mode = FRAME_COUNT;
	int _head = 0;
	int _time = 0;
	bool loop_ = false;
	vector<Key*> _keys;
};

