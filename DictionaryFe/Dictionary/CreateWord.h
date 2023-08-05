#pragma once
#include"state.h"
#include"system.h"
#include<fstream>
#include<vector>
class CreateWord : public state
{
private:
	data* _data;
	std::wstring _type;
	std::wstring _word;
	std::vector<std::wstring> _def;
	sf::View view;
	int windowTranslateY;
	int windowTranslateX;
	sf::Time time;
	sf::Clock clock;
	bool blink;

	sf::Text title;
	sf::RectangleShape bar;
	sf::Sprite backArr;
	bool backArrHover;
	bool backArrClick;
	

	sf::Text keywordLabel;
	bool keywordHover;
	bool keywordClick;
	sf::RectangleShape keywordBox;
	bool keywordBoxHidden;
	sf::Text keyword;
	std::wstring getKeyword;
	sf::Text keywordCursor;
	int keywordCursorPos;

	sf::Text defLabel;
	sf::Text addDef;
	bool addDefHover;
	bool addDefClick;

	sf::Text removeDef;
	bool removeDefHover;
	bool removeDefClick;

	sf::RectangleShape defBox[20];
	bool defBoxFocus[20];
	int maxdefBox;
	sf::Text def[20];
	std::wstring getDef[20];
	sf::Text defCursor[20];
	int defCursorPos[20];
	
	sf::RectangleShape submitButton;
	sf::Text submit;
	bool submitHover;
	bool submitClick;
	

public:
	CreateWord(data* data, std::wstring type, std::wstring word = L"", std::vector<std::wstring> def = {});
	~CreateWord();
	void init();
	void processInput();
	void update();
	void draw();
};

