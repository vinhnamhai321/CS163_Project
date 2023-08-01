#pragma once
#include"state.h"
#include"system.h"
#include <vector>
#include<fstream>
class WordDefinition: public state
{
private:
	data* _data;
	WordDef* _keyword;
	std::wstring _dataset;
	sf::View view;

	sf::Sprite backArr;
	bool backArrHover;
	bool backArrClick;

	sf::Text word;
	std::vector<sf::Text> definition;

	sf::Text addFavList;
	std::wfstream favFile;
	bool addFavListHover;
	bool addFavListClick;
	sf::Text status;
	bool statusOn;

	sf::Text editWord;
	bool editWordHover;
	bool editWordClick;

	sf::Text removeWord;
	bool removeWordHover;
	bool removeWordClick;
public:
	WordDefinition(data* data, WordDef* keyword, std::wstring dataset);
	~WordDefinition();
	void init();
	void processInput();
	void update();
	void draw();
};

