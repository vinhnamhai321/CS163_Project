#include "CreateWord.h"
#include"HandmadeFunc.h"
CreateWord::CreateWord(data* data, std::wstring type, std::wstring dtset, std::wstring word, std::vector<std::wstring> def) 
: _data(data), _type(type), _dtset(dtset), _word(word), _def(def), blink(1)
{}
CreateWord::~CreateWord()
{}
void CreateWord::init()
{
	time = sf::Time::Zero;
	//set view
	view.setSize(sf::Vector2f(1600, 900));
	view.setCenter(sf::Vector2f(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2));
	windowTranslateY = 0;
	windowTranslateX = 0;

	//Set backArr
	backArr.setTexture(_data->_assets->getTexture(BACK_ARR));
	backArr.setPosition(sf::Vector2f(0, 0));
	backArr.setScale(sf::Vector2f(0.2, 0.2));

	//Set tiltle
	title = createText(_type, 400, 0, 80);
	title.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	title.setFillColor(sf::Color(10, 123, 233, 255));

	//Set bar
	bar = createRectangleShape(_data->_window->getSize().x, 100);
	bar.setFillColor(sf::Color(248, 245, 251, 255));

	

	//Set keywordLabel
	keywordLabel = createText(L"Key word", 100, 150, 60);
	keywordLabel.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	keywordLabel.setFillColor(sf::Color(29, 42, 87, 255));

	//Set keywordBox 
	keywordBox = createRectangleShape(600, 60,
		keywordLabel.getPosition().x + 300,
		keywordLabel.getPosition().y + 10);
	keywordBox.setOutlineThickness(3);
	keywordBox.setOutlineColor(sf::Color(0, 0, 0, 255));

	if (_type == L"Add new word")
	{
		keywordBoxHidden = 0;
	}
	if (_type == L"Edit word")
	{
		keywordBoxHidden = 1;
	}
	

	//Set keyword
	keyword = createText(L"",
		keywordBox.getPosition().x + 10,
		keywordBox.getPosition().y + 10, 25);
	keyword.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	keyword.setFillColor(sf::Color::Black);
	getKeyword = _word;

	//Set keywordCursor
	keywordCursor = createText(L"|",
		keywordBox.getPosition().x,
		keywordBox.getPosition().y + 7, 25);
	keywordCursor.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	keywordCursor.setFillColor(sf::Color::Black);

	//Set defLabel
	defLabel = createText(L"Definition", 100, 300, 60);
	defLabel.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	defLabel.setFillColor(sf::Color::Black);

	//Set addDef
	addDef = createText(L"+ New def", 600, 300, 60);
	addDef.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	addDef.setFillColor(sf::Color::Black);

	//Set removeDef
	removeDef.setString("X");
	removeDef.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	removeDef.setCharacterSize(60);
	removeDef.setFillColor(sf::Color::Black);
	

	//Set defBox + def
	maxdefBox = _def.size();
	for (int i = 0; i < 20; i++)
	{
		defBox[i] = createRectangleShape(1300, 60,
			defLabel.getPosition().x,
			defLabel.getPosition().y + 100 + 100*i);
		defBox[i].setOutlineThickness(3);
		defBox[i].setOutlineColor(sf::Color(0, 0, 0, 100));

		defBoxFocus[i] = 0;

		def[i] = createText(L"",
			defBox[i].getPosition().x + 10,
			defBox[i].getPosition().y + 10, 25);
		def[i].setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
		def[i].setFillColor(sf::Color::Black);

		defCursor[i] = createText(L"|",
			defBox[i].getPosition().x + 10,
			defBox[i].getPosition().y + 10, 25);
		defCursor[i].setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
		defCursor[i].setFillColor(sf::Color::Black);

		if (i < maxdefBox)
		{
			if (i != 0)
			{
				_def[i].erase(0, 1);
			}
			getDef[i] = _def[i];
		}
	}

	//Set submitButton + submit
	submitButton = createRectangleShape(150, 50,
		_data->_window->getSize().x / 2 - 75,
		_data->_window->getSize().y / 2 - 25 + maxdefBox * 100);
	submitButton.setOrigin(sf::Vector2f(submitButton.getLocalBounds().width / 2, submitButton.getLocalBounds().height / 2));
	submitButton.setFillColor(sf::Color(10, 123, 233, 255));

	submit = createText(L"Submit",
		_data->_window->getSize().x / 2 - 75 - 55,
		_data->_window->getSize().y / 2 - 25 + maxdefBox * 100 - 20, 30);
	submit.setFont(_data->_assets->getFont(MONTSERRAT_EXTRABOLD));
	submit.setFillColor(sf::Color::White);

	//Set dataset
	dataset = createText(_dtset,
		keywordBox.getPosition().x + 10,
		keywordBox.getPosition().y + 80, 40);
	dataset.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	dataset.setFillColor(sf::Color::Black);
}
void CreateWord::processInput()
{
	sf::Event event;
	while (_data->_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_data->_window->close();
			break;
		case sf::Event::MouseWheelScrolled:
		{
			int translateY = 0;
			if (event.mouseWheelScroll.delta > 0 && windowTranslateY > 0) {
				view.move(sf::Vector2f(0, -30));
				translateY = -30;
				windowTranslateY -= 30;
			}
			if (event.mouseWheelScroll.delta < 0 && windowTranslateY < defBox[maxdefBox - 1].getPosition().y - 75) {
				view.move(sf::Vector2f(0, 30));
				translateY = 30;
				windowTranslateY += 30;
			}
			bar.move(sf::Vector2f(0, translateY));
			backArr.move(sf::Vector2f(0, translateY));
			title.move(sf::Vector2f(0, translateY));
			break;
		}
		
		case sf::Event::TextEntered:

			if (!keywordBoxHidden && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (event.key.code == 8)
				{
					int i = 0;
					for (;i < getKeyword.size();i++)
					{
						if (keyword.findCharacterPos(i).x > keywordCursorPos)
							break;
					}
					if (i == getKeyword.size() - 1 && i >= 1)
					{
						keywordCursorPos -= 15;
						getKeyword.erase(i - 1, 1);
					}
					else if (i >= 1)
					{
						keywordCursorPos -= 15;
						getKeyword.erase(i - 1, 1);
					}
				}
				else
				{
					if (getKeyword.empty())
					{
						getKeyword += static_cast<wchar_t>(event.key.code);
						keywordCursorPos = keyword.findCharacterPos(0).x;
					}
					else
					{
						int i = 0;
						for (;i < getKeyword.size();i++)
						{
							if (keyword.findCharacterPos(i).x > keywordCursorPos)
								break;
						}
						keywordCursorPos += 15;
						getKeyword.insert(getKeyword.begin() + i, static_cast<wchar_t>(event.key.code));
					}
				}
				blink = 1;
			}
			for (int j = 0; j < maxdefBox; j++)
			{
				if (defBoxFocus[j] && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					if (event.key.code == 8)
					{
						int i = 0;
						for (;i < getDef[j].size();i++)
						{
							if (def[j].findCharacterPos(i).x > defCursorPos[j])
								break;
						}
						if (i == getDef[j].size() - 1 && i >= 1)
						{
							defCursorPos[j] -= 15;
							getDef[j].erase(i - 1, 1);
						}
						else if (i >= 1)
						{
							defCursorPos[j] -= 15;
							getDef[j].erase(i - 1, 1);
						}
					}
					else
					{
						if (getDef[j].empty())
						{
							getDef[j] += static_cast<wchar_t>(event.key.code);
							defCursorPos[j] = def[j].findCharacterPos(0).x;
						}
						else
						{
							int i = 0;
							for (;i < getDef[j].size();i++)
							{
								if (def[j].findCharacterPos(i).x > defCursorPos[j])
									break;
							}
							defCursorPos[j] += 15;
							getDef[j].insert(getDef[j].begin() + i, static_cast<wchar_t>(event.key.code));
						}
					}
					blink = 1;
				}
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				backArrClick = (backArrHover ? 1 : 0);
				addDefClick = (addDefHover ? 1 : 0);
				removeDefClick = (removeDefHover ? 1 : 0);
				submitClick = (submitHover ? 1 : 0);
				if(!keywordBox.getGlobalBounds()
.contains(sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x, sf::Mouse::getPosition(*_data->_window).y + windowTranslateY)))
				{
					keywordBoxHidden = 1;
				}
				keywordClick = ((keywordHover && _type == L"Add new word") ? 1 : 0);
				if (!keywordBoxHidden)
				{
					keywordCursorPos = sf::Mouse::getPosition(*_data->_window).x + windowTranslateX;
				}
				for (int i = 0; i < maxdefBox; i++)
				{
					defBoxFocus[i] = isFocus(defBox[i], *_data->_window, windowTranslateY);
					defCursorPos[i] = sf::Mouse::getPosition(*_data->_window).x;
				}
			}
			break;
		case sf::Event::KeyPressed:
		{
			int translateX = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && windowTranslateX > 0)
			{
				view.move(sf::Vector2f(-10, 0));
				windowTranslateX -= 10;
				translateX = -10;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && windowTranslateX < 1500)
			{
				view.move(sf::Vector2f(10, 0));
				windowTranslateX += 10;
				translateX = 10;
			}
			bar.move(sf::Vector2f(translateX, 0));
			backArr.move(sf::Vector2f(translateX, 0));
			title.move(sf::Vector2f(translateX, 0));
			break;
		}
		}
		backArrHover = isHover(backArr, *_data->_window, windowTranslateY, windowTranslateX);
		keywordHover = isHover(keywordLabel, *_data->_window, windowTranslateY, windowTranslateX);
		addDefHover = isHover(addDef, *_data->_window, windowTranslateY, windowTranslateX);
		removeDefHover = isHover(removeDef, *_data->_window, windowTranslateY, windowTranslateX);
		submitHover = isHover(submitButton, *_data->_window, windowTranslateY, windowTranslateX);
	}
}
void CreateWord::update()
{
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 0.5)
	{
		blink = !blink;
		clock.restart();
	}
	
	//Hover
	(backArrHover ? backArr.setColor(sf::Color(255, 255, 255, 100)) : backArr.setColor(sf::Color::White));
	((keywordHover && _type == L"Add new word") 
		? keywordLabel.setFillColor(sf::Color(29, 42, 87, 100)) 
		: keywordLabel.setFillColor(sf::Color(29, 42, 87, 255)));
	(addDefHover ? addDef.setFillColor(sf::Color(0, 0, 0, 100)) : addDef.setFillColor(sf::Color::Black));
	(removeDefHover ? removeDef.setFillColor(sf::Color(0, 0, 0, 100)) : removeDef.setFillColor(sf::Color::Black));
	(submitHover ? submitButton.setFillColor(sf::Color(10, 123, 233, 100)) : submitButton.setFillColor(sf::Color(10, 123, 233, 255)));
	//Focus
	for (int i = 0; i < maxdefBox; i++)
	{
		(defBoxFocus[i] ? defBox[i].setOutlineColor(sf::Color(0, 0, 0, 200)) : defBox[i].setOutlineColor(sf::Color(0, 0, 0, 100)));
	}
	//Text 
	(keywordBoxHidden ? keyword.setCharacterSize(60) : keyword.setCharacterSize(25));
	(keywordBoxHidden ? keyword.setPosition(keywordBox.getPosition().x + 10, keywordBox.getPosition().y - 15) 
					: keyword.setPosition(keywordBox.getPosition().x + 10, keywordBox.getPosition().y + 10));
	keyword.setString(getKeyword);
	((blink && !keywordBoxHidden) ? keywordCursor.setString("|") : keywordCursor.setString(""));
	if (getKeyword.empty() || keywordCursorPos < keyword.findCharacterPos(0).x)
	{
		keywordCursor.setPosition(keywordBox.getPosition().x,
			keywordBox.getPosition().y + 7);
		keywordCursorPos = keywordCursor.getPosition().x;
	}
	else if (keywordCursorPos >= keyword.findCharacterPos(getKeyword.size() - 1).x) {
		keywordCursor.setPosition(keywordBox.getPosition().x + keyword.getGlobalBounds().width + 7,
			keywordBox.getPosition().y + 7);
		keywordCursorPos = keywordCursor.getPosition().x;
	}
	else
	{
		int i = 0;
		for (; i < getKeyword.size(); i++)
		{
			if (keywordCursorPos <= keyword.findCharacterPos(i).x)
				break;
		}
		keywordCursor.setPosition(keyword.findCharacterPos(i).x - 8,
			keywordBox.getPosition().y + 7);
		keywordCursorPos = keywordCursor.getPosition().x;
	}

	for (int i = 0; i < maxdefBox; i++)
	{
		def[i].setString(getDef[i]);
		((blink && defBoxFocus[i]) ? defCursor[i].setString("|") : defCursor[i].setString(""));
		if (getDef[i].empty() || defCursorPos[i] < def[i].findCharacterPos(0).x)
		{
			defCursor[i].setPosition(defBox[i].getPosition().x,
				defBox[i].getPosition().y + 7);
			defCursorPos[i] = defCursor[i].getPosition().x;
		}
		else if (defCursorPos[i] >= def[i].findCharacterPos(getDef[i].size() - 1).x) {
			defCursor[i].setPosition(defBox[i].getPosition().x + def[i].getGlobalBounds().width + 7,
				defBox[i].getPosition().y + 7);
			defCursorPos[i] = defCursor[i].getPosition().x;
		}
		else
		{
			int j = 0;
			for (; j < getDef[i].size(); j++)
			{
				if (defCursorPos[i] <= def[i].findCharacterPos(j).x)
					break;
			}
			defCursor[i].setPosition(def[i].findCharacterPos(j).x - 8,
				defBox[i].getPosition().y + 7);
			defCursorPos[i] = defCursor[i].getPosition().x;
		}
	}
	//Click
	if (backArrClick)
	{
		_data->_states->removeState();
		backArrClick = 0;
	}
	if (addDefClick && maxdefBox < 20)
	{
		maxdefBox++;
		submitButton.move(sf::Vector2f(0, 100));
		submit.move(sf::Vector2f(0, 100));
		addDefClick = 0;
	}
	if (removeDefClick && maxdefBox > 0)
	{
		getDef[maxdefBox - 1].clear();
		maxdefBox--;
		submitButton.move(sf::Vector2f(0, -100));
		submit.move(sf::Vector2f(0, -100));
		removeDefClick = 0;
	}
	if (keywordClick)
	{
		keywordBoxHidden = 0;
		keywordClick = 0;
	}
	if (submitClick)
	{
		if (_type == L"Add new word")
		{
			std::vector<std::wstring> d;
			for (int i = 0; i < maxdefBox; i++)
			{
				d.push_back(getDef[i]);
			}
			addWord(getKeyword, d, _dtset, _data);
			std::wstring line = getKeyword + L"(" + _dtset + L")";
			removeWord(line, L"Resource\\RemoveWord.txt");
			_data->_states->removeState();
		}
		if (_type == L"Edit word")
		{
			std::vector<std::wstring> d;
			for (int i = 0; i < maxdefBox; i++)
			{
				d.push_back(getDef[i]);
			}
			editWord(getKeyword, d, _dtset, _data);
			_data->_states->removeState();
		}
		submitClick = 0;
	}
	//OverFlow
	if (keyword.findCharacterPos(getKeyword.size() - 1).x > keywordBox.getLocalBounds().width + keywordBox.getPosition().x - 30)
	{
		int newSizeX = keywordBox.getSize().x + 50;
		keywordBox.setSize(sf::Vector2f(newSizeX, 60));
	}
	for (int i = 0; i < maxdefBox; i++)
	{
		if (def[i].findCharacterPos(getDef[i].size() - 1).x > defBox[i].getLocalBounds().width + defBox[i].getPosition().x - 30)
		{
			int newSizeX = defBox[i].getSize().x + 50;
			defBox[i].setSize(sf::Vector2f(newSizeX, 60));
		}
	}
	if (maxdefBox > 0)
	{
		removeDef.setPosition(defBox[maxdefBox - 1].getPosition().x + defBox[maxdefBox - 1].getLocalBounds().width + 30,
			defBox[maxdefBox - 1].getPosition().y - 10);
	}
	
	
}
void CreateWord::draw()
{
	_data->_window->clear(sf::Color(248, 245, 251, 255));
	_data->_window->setView(view);
	_data->_window->draw(keywordLabel);
	if (!keywordBoxHidden)
	{
		_data->_window->draw(keywordBox);
		_data->_window->draw(keywordCursor);
	}
	_data->_window->draw(keyword);
	_data->_window->draw(defLabel);
	_data->_window->draw(addDef);
	_data->_window->draw(dataset);
	for (int i = 0; i < maxdefBox; i++)
	{
		_data->_window->draw(defBox[i]);
		_data->_window->draw(defCursor[i]);
		_data->_window->draw(def[i]);
	}
	if (maxdefBox > 0)
	{
		_data->_window->draw(removeDef);
	}
	_data->_window->draw(submitButton);
	_data->_window->draw(submit);
	//fixed obj
	_data->_window->draw(bar);
	_data->_window->draw(title);
	_data->_window->draw(backArr);
	_data->_window->display();
}