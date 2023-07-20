#pragma once
#include"assetManager.h"
#include"stateMachine.h"

struct data
{
	assetManager* _assets;
	stateMachine* _states;
	sf::RenderWindow* _window;
	data()
	{
		_assets = new assetManager;
		_states = new stateMachine;
		_window = new sf::RenderWindow;
	}
};
class System
{
private:
	data* _data;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
public:
	System();
	~System();
	void run();
};



