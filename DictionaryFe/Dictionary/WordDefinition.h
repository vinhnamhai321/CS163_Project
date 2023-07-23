#pragma once
#include"state.h"
#include"system.h"
#include <vector>
class WordDefinition: public state
{
private:
	data* _data;
	WordDef* _keyword;

	sf::Sprite backArr;
	bool backArrHover;
	bool backArrClick;

	sf::Text word;
	std::vector<sf::Text> definition;
public:
	WordDefinition(data* data, WordDef* keyword);
	~WordDefinition();
	void init();
	void processInput();
	void update();
	void draw();
};

