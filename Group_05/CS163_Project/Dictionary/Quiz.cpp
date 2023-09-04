#include "Quiz.h"
#include"HandmadeFunc.h"
#include"Trie.h"
#include<string.h>
#include<iostream>
#include<Windows.h>
Quiz::Quiz(data* data) : _data(data)
{}
Quiz::~Quiz()
{}
void Quiz::init()
{
	//set view
	view.setSize(sf::Vector2f(1600, 900));
	view.setCenter(sf::Vector2f(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2));

	//Set backArr
	backArr.setTexture(_data->_assets->getTexture(BACK_ARR));
	backArr.setPosition(sf::Vector2f(0, 0));
	backArr.setScale(sf::Vector2f(0.2, 0.2));

	//Set ques
	ques.setCharacterSize(48);
	ques.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	ques.setFillColor(sf::Color(10, 123, 233, 255));

	//Set choiceBox;
	for (int i = 0; i < 4; i++)
	{
		choiceBox[i] = createRectangleShape(1550, 100, 20, 350 + 110*i);
		choiceBox[i].setOutlineThickness(3);
		choiceBox[i].setOutlineColor(sf::Color(0, 0, 0, 255));

		layer[i] = createRectangleShape(1550, 100, 20, 350 + 110 * i);
		layer[i].setOutlineThickness(3);
		layer[i].setOutlineColor(sf::Color(0, 0, 0, 255));

		choice[i].setPosition(sf::Vector2f(30, 360 + 110 * i));
		choice[i].setCharacterSize(25);
		choice[i].setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
		choice[i].setFillColor(sf::Color::Black);
	}

	//Set button
	button = createRectangleShape(150, 50,
		_data->_window->getSize().x / 2,
		_data->_window->getSize().y / 2 + 400);
	button.setOrigin(sf::Vector2f(button.getLocalBounds().width / 2, button.getLocalBounds().height / 2));
	button.setFillColor(sf::Color(10, 123, 233, 255));

	content = createText(L"Start",
		_data->_window->getSize().x / 2 - 55,
		_data->_window->getSize().y / 2 + 400 - 20, 30);
	content.setFont(_data->_assets->getFont(MONTSERRAT_EXTRABOLD));
	content.setFillColor(sf::Color::White);
}
void Quiz::processInput()
{
	sf::Event event;
	while (_data->_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_data->_window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				backArrClick = (backArrHover ? 1 : 0);
				buttonClick = (buttonHover ? 1 : 0);
				for (int i = 0; i < 4; i++)
				{
					choiceClick[i] = (choiceHover[i] ? 1 : 0);
				}
			}
		}
		backArrHover = isHover(backArr, *_data->_window);
		for (int i = 0; i < 4; i++)
		{
			if (content.getString() != L"Start")
			{
				choiceHover[i] = isHover(choiceBox[i], *_data->_window);
			}
		}
		buttonHover = isHover(button, *_data->_window);
	}
}
void Quiz::update()
{
	//Hover
	(backArrHover ? backArr.setColor(sf::Color(255, 255, 255, 100)) : backArr.setColor(sf::Color::White));
	(buttonHover ? button.setFillColor(sf::Color(10, 123, 233, 100)) : button.setFillColor(sf::Color(10, 123, 233, 255)));
	for (int i = 0; i < 4; i++)
	{
		(choiceHover[i] ? choiceBox[i].setFillColor(sf::Color(248, 245, 251, 255)) : choiceBox[i].setFillColor(sf::Color::White));
	}
	//Click
	if (backArrClick)
	{
		_data->_states->removeState();
		backArrClick = 0;
	}
	isChoose = 0;
	for (int i = 0; i < 4; i++)
	{
		srand(time(NULL));
		if (choiceClick[i] || buttonClick)
		{
			int dt = rand() % 3;
			if (dt == 0)
			{
				int id = rand() % 2;
				if (id == 0)
				{
					int a[4];
					for (int k = 0; k < 4; k++)
					{
						int idx = rand() % _data->eeKeyword.size();
						a[k] = idx;
						std::wstring def = _data->eeKeyword[idx].definition[_data->eeKeyword[idx].definition.size() - 1];
						def.erase(0, 1);
						choice[k].setString(def);
						for (int j = 0; j < def.size(); j++)
						{
							if(def[j] == L' ' && choice[k].findCharacterPos(j).x > 1400)
							{
								def.insert(def.begin() + j, L'\n');
								choice[k].setString(def);
							}
						}
					}
					ans = rand() % 4;
					ques.setString(_data->eeKeyword[a[ans]].keyWord);
					ques.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 200, _data->_window->getSize().y / 2 - 350));
				}
				if (id == 1)
				{
					int a[4];
					for (int k = 0; k < 4; k++)
					{
						int idx = rand() % _data->eeKeyword.size();
						a[k] = idx;
						std::wstring word = _data->eeKeyword[idx].keyWord;
						choice[k].setString(word);
					}
					ans = rand() % 4;
					std::wstring def = _data->eeKeyword[a[ans]].definition[_data->eeKeyword[a[ans]].definition.size() - 1];
					def.erase(0, 1);
					ques.setString(def);
					ques.setPosition(sf::Vector2f(200, _data->_window->getSize().y / 2 - 350));
					for (int j = 0; j < def.size(); j++)
					{
						if (def[j] == L' ' && ques.findCharacterPos(j).x > 1400)
						{
							def.insert(def.begin() + j, L'\n');
							ques.setString(def);
						}
					}
				}
			}
			if (dt == 1)
			{
				int id = rand() % 2;
				if (id == 0)
				{
					int a[4];
					for (int k = 0; k < 4; k++)
					{
						int idx = rand() % _data->evKeyword.size();
						a[k] = idx;
						std::wstring def = _data->evKeyword[idx].definition[_data->evKeyword[idx].definition.size() - 1];
						def.erase(0, 1);
						choice[k].setString(def);
						for (int j = 0; j < def.size(); j++)
						{
							if (def[j] == L' ' && choice[k].findCharacterPos(j).x > 1400)
							{
								def.insert(def.begin() + j, L'\n');
								choice[k].setString(def);
							}
						}
					}
					ans = rand() % 4;
					ques.setString(_data->evKeyword[a[ans]].keyWord);
					ques.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 200, _data->_window->getSize().y / 2 - 350));
				}
				if (id == 1)
				{
					int a[4];
					for (int k = 0; k < 4; k++)
					{
						int idx = rand() % _data->evKeyword.size();
						a[k] = idx;
						std::wstring word = _data->evKeyword[idx].keyWord;
						choice[k].setString(word);
					}
					ans = rand() % 4;
					std::wstring def = _data->evKeyword[a[ans]].definition[_data->evKeyword[a[ans]].definition.size() - 1];
					def.erase(0, 1);
					ques.setString(def);
					ques.setPosition(sf::Vector2f(200, _data->_window->getSize().y / 2 - 350));
					for (int j = 0; j < def.size(); j++)
					{
						if (def[j] == L' ' && ques.findCharacterPos(j).x > 1400)
						{
							def.insert(def.begin() + j, L'\n');
							ques.setString(def);
						}
					}
				}
			}
			if (dt == 2)
			{
				int id = rand() % 2;
				if (id == 0)
				{
					int a[4];
					for (int k = 0; k < 4; k++)
					{
						int idx = rand() % _data->veKeyword.size();
						a[k] = idx;
						std::wstring def = _data->veKeyword[idx].definition[_data->veKeyword[idx].definition.size() - 1];
						def.erase(0, 1);
						choice[k].setString(def);
						for (int j = 0; j < def.size(); j++)
						{
							if (def[j] == L' ' && choice[k].findCharacterPos(j).x > 1400)
							{
								def.insert(def.begin() + j, L'\n');
								choice[k].setString(def);
							}
						}
					}
					ans = rand() % 4;
					ques.setString(_data->veKeyword[a[ans]].keyWord);
					ques.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 200, _data->_window->getSize().y / 2 - 350));
				}
				if (id == 1)
				{
					int a[4];
					for (int k = 0; k < 4; k++)
					{
						int idx = rand() % _data->veKeyword.size();
						a[k] = idx;
						std::wstring word = _data->veKeyword[idx].keyWord;
						choice[k].setString(word);
					}
					ans = rand() % 4;
					std::wstring def = _data->veKeyword[a[ans]].definition[_data->veKeyword[a[ans]].definition.size() - 1];
					def.erase(0, 1);
					ques.setString(def);
					ques.setPosition(sf::Vector2f(200, _data->_window->getSize().y / 2 - 350));
					for (int j = 0; j < def.size(); j++)
					{
						if (def[j] == L' ' && ques.findCharacterPos(j).x > 1400)
						{
							def.insert(def.begin() + j, L'\n');
							ques.setString(def);
						}
					}
				}
			}
			isChoose = 1;
			if (isChoose && content.getString() != L"Start")
			{
				for (int j = 0; j < 4; j++)
				{
					_data->_window->draw(layer[j]);

				}
				_data->_window->display();
				Sleep(500);
			}
			for (int j = 0; j < 4; j++)
			{
				if (j == ans)
				{
					layer[j].setFillColor(sf::Color(0, 255, 0, 100));
				}
				else
				{
					layer[j].setFillColor(sf::Color(255, 0, 0, 100));
				}
			}
			
			if (buttonClick)
			{
				content.setString("Skip");
			}
			choiceClick[i] = 0;
			buttonClick = 0;
		}
	}

	
}
void Quiz::draw()
{
	
	_data->_window->clear(sf::Color(214, 246, 244, 255));
	_data->_window->setView(view);
	
	_data->_window->draw(backArr);
	_data->_window->draw(ques);
	if (content.getString() != L"Start")
	{
		for (int i = 0; i < 4; i++)
		{
			_data->_window->draw(choiceBox[i]);
			_data->_window->draw(choice[i]);
		}
	}
	
	_data->_window->draw(button);
	_data->_window->draw(content);
	_data->_window->display();
	
}