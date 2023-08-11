#pragma once
#include"state.h"
#include"system.h"
#include<fstream>
class Confirm : public state
{
private:
	data* _data;
	std::wstring _status;
	std::wstring _line;
	sf::View view;
	std::wfstream removeWordFile;

	sf::RectangleShape box;
	sf::RectangleShape yesButton;
	sf::Text yes;
	bool yesButtonHover;
	bool yesButtonClick;
	sf::RectangleShape noButton;
	sf::Text no;
	bool noButtonHover;
	bool noButtonClick;
	sf::Text status;

	
public:
	Confirm(data* data, std::wstring status, std::wstring line = L"");
	~Confirm();
	void init();
	void processInput();
	void update();
	void draw();
};

