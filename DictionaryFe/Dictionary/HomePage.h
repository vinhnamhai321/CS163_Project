#pragma once
#include"state.h"
#include"system.h"
#include<fstream>
class HomePage: public state
{
private:
	data* _data;
	sf::Time time;
	sf::Clock clock;
	sf::View view;
	std::wfstream historyFile;

	sf::RectangleShape navbar;

	sf::Text favList;
	bool favListHover;
	bool favListClick;
	
	sf::Text history;
	bool historyHover;
	bool historyClick;

	sf::Text addWord;
	bool addWordHover;
	bool addWordClick;

	sf::Text reset;
	bool resetHover;
	bool resetClick;

	sf::Text quiz;
	bool quizHover;
	bool quizClick;

	sf::RectangleShape searchBox;
	bool searchBoxFocus;
	sf::Text searchBoxText;
	std::wstring getSearchBoxText;
	sf::Text searchBoxPlaceholder;
	
	sf::Text cursor;
	int curPosX;
	bool blink;

	sf::Sprite dictionaryIcon;
	sf::Text dictionary;
	
	sf::Sprite searchIcon;
	sf::RectangleShape searchIconBox;
	bool searchIconHover;
	bool searchIconClick;
	
	sf::Text dataSet;
	sf::Sprite downArr;
	bool downArrHover;
	sf::RectangleShape dataBox;
	sf::Text dataBoxContent[4];
	bool dataBoxContentHover[4];
	bool dataBoxHidden;
	std::wstring getDataSet;

	sf::Text random;
	bool randomHover;
	bool randomClick;
	

	sf::Text status; 
	bool statusOn;
public:
	HomePage(data* data);
	~HomePage();
	void init();
	void processInput();
	void update();
	void draw();
};

