#pragma once
#include"system.h"
#include"state.h"
#include"Trie.h"
class Quiz : public state
{
private:
	data* _data;
	sf::View view;

	sf::Sprite backArr;
	bool backArrHover;
	bool backArrClick;

	sf::Text ques;
	sf::Text choice[4];
	sf::RectangleShape choiceBox[4];
	bool choiceHover[4];
	bool choiceClick[4];
	sf::RectangleShape layer[4];
	sf::RectangleShape button;
	sf::Text content;
	bool buttonHover;
	bool buttonClick;
	int ans;
	bool isChoose;

public:
	Quiz(data* data);
	~Quiz();
	void init();
	void processInput();
	void update();
	void draw();
};

