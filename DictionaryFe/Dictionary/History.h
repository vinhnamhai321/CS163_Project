#pragma once
#include"state.h"
#include"system.h"
#include<fstream>
#include<vector>
class History : public state
{
private:
	data* _data;
	sf::View view;
	int windowTranslateY;

	std::wfstream historyFile;
	std::vector<sf::Text> historyList;
	sf::Text clone;
	int cloneIdx;
	
	sf::Sprite backArr;
	bool backArrHover;
	bool backArrClick;
	sf::RectangleShape bar;

	sf::Text title;
	sf::Sprite historyClock;

	sf::Sprite deleteIcon;

	

public:
	History(data* data);
	~History();
	void init();
	void processInput();
	void update();
	void draw();
};

