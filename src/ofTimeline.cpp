#include "ofTimeline.h"



ofTimeline::ofTimeline()
{
}


ofTimeline::~ofTimeline()
{
}

void ofTimeline::reset()
{
	_keys.clear();
	_head = 0;
	_time = 0;
}

void ofTimeline::update() {
	if (next()->startTime <= _time) {
		_head++;
	}
	if (current()->isEndFlag) 
	{
		if (loop_) 
		{
			_head = 0;
			_time = 0;
		}
		else {
			return;
		}
	}
	_time++;
	action();

}
float ofTimeline::normalizedTime() {
	if (_keys.size() <= 0) {
		return 0;
	}
	auto end = _keys.back()->startTime;
	auto cur = _time;
	return (float)cur / end;
}
void ofTimeline::addKey(int time, function<void()> func)
{
	

	_keys.push_back(new Key(time, func));
}

void ofTimeline::end(int time,bool loop)
{
	loop_ = loop;
	_keys.push_back(new Key(time));
}
void ofTimeline::action()
{
	if (current()->func != nullptr) {
		current()->func();
	}
}

Key* ofTimeline::current()
{

	return _keys[_head];
}

Key* ofTimeline::next()
{
	return _keys[_head + 1];
}

Key::Key(int time, function<void()> func)
{
	if (func != nullptr) {
		func();
	}
	startTime = time;
	this->func = func;
}

Key::Key(int time)
{
	startTime = time;
	func = nullptr;
	isEndFlag = true;

}
