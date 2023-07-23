#pragma once
#include"state.h"
#include"system.h"
class Loading: public state
{
private:
	data* _data;
	sf::Time time;
	sf::Clock clock;
	sf::Text loading;
	sf::Sprite background;
public:
	Loading(data* data);
	~Loading();
	void init();
	void processInput();
	void update();
	void draw();
};

