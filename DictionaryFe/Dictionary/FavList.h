#pragma once
#include"state.h"
#include"system.h"
#include<fstream>
#include<vector>
class FavList : public state
{
private:
	data* _data;
	sf::View view;
	int windowTranslateY;

	std::wfstream favFile;
	std::vector<sf::Text> favList;
	sf::Text clone;
	int cloneIdx;
	bool* favListHover;
	bool* favListClick;

	sf::Sprite backArr;
	bool backArrHover;
	bool backArrClick;
	sf::RectangleShape bar;

	sf::Text title;
	
	sf::Sprite deleteIcon;

public:
	FavList(data* data);
	~FavList();
	void init();
	void processInput();
	void update();
	void draw();
};
