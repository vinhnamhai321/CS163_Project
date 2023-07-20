#pragma once
class state
{
public:
	virtual void init() = 0;
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
