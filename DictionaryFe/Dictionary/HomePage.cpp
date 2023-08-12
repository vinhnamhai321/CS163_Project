﻿#include"HomePage.h"
#include"HandmadeFunc.h"
#include"History.h"
#include"WordDefinition.h"
#include"FavList.h"
#include"Confirm.h"
#include"CreateWord.h"
#include"Quiz.h"
#include<locale>
#include<codecvt>
#include<iostream>
HomePage::HomePage(data* data) : _data(data), dataBoxHidden(1), blink(1)
{}
HomePage::~HomePage()
{}
void HomePage::init()
{
	time = sf::Time::Zero;

	historyFile.open(L"Resource\\History.txt", std::ios::app);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	historyFile.imbue(loc);
	//set view
	view.setSize(sf::Vector2f(1600, 900));
	view.setCenter(sf::Vector2f(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2));
	//Set navbar
	navbar = createRectangleShape(_data->_window->getSize().x, 60);
	navbar.setFillColor(sf::Color(29, 42, 87, 255));

	//Set favList
	favList = createText(L"Favorite List", 70, 10, 25);
	favList.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	favList.setFillColor(sf::Color::White);

	//Set history
	history = createText(L"History", 370, 10, 25);
	history.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	history.setFillColor(sf::Color::White);

	//Set addWord
	addWord = createText(L"Add new word", 570, 10, 25);
	addWord.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	addWord.setFillColor(sf::Color::White);
	
	//Set reset
	reset = createText(L"Reset app", 870, 10, 25);
	reset.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	reset.setFillColor(sf::Color::White);

	//Set quiz
	quiz = createText(L"Quizzes", 1170, 10, 25);
	quiz.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	quiz.setFillColor(sf::Color::White);

	//Set searchBox 
	searchBox = createRectangleShape(_data->_window->getSize().x / 2, 60,
									_data->_window->getSize().x / 2,
									_data->_window->getSize().y / 2);
	searchBox.setOrigin(sf::Vector2f(searchBox.getLocalBounds().width / 2, searchBox.getLocalBounds().height / 2));
	searchBox.setOutlineThickness(3);
	searchBox.setOutlineColor(sf::Color(0, 0, 0, 100));
	//Set searchBoxText
	
	searchBoxText = createText(L"",
								searchBox.getPosition().x - searchBox.getSize().x / 2 + 10, 
								searchBox.getPosition().y - searchBox.getSize().y / 2 + 10, 25);
	searchBoxText.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	searchBoxText.setFillColor(sf::Color::Black);

	//Set searchBoxLabel
	searchBoxPlaceholder = createText(L"Search...",
		searchBox.getPosition().x - searchBox.getSize().x / 2 + 10,
		searchBox.getPosition().y - searchBox.getSize().y / 2 + 10, 25);
	searchBoxPlaceholder.setFont(_data->_assets->getFont(LIGHT));
	searchBoxPlaceholder.setFillColor(sf::Color(0, 0, 0, 130));

	//Set cursor
	cursor = createText(L"|",
						searchBox.getPosition().x - searchBox.getSize().x / 2,
						searchBox.getPosition().y - searchBox.getSize().y / 2 + 7, 25);
	cursor.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	cursor.setFillColor(sf::Color::Black);

	//Set dictionaryIcon
	dictionaryIcon.setTexture(_data->_assets->getTexture(DICTIONARY_ICON));
	dictionaryIcon.setOrigin(sf::Vector2f(dictionaryIcon.getLocalBounds().width / 2, dictionaryIcon.getLocalBounds().height / 2));
	dictionaryIcon.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 300, 250));
	dictionaryIcon.setScale(sf::Vector2f(0.5, 0.5));

	//Set dictionary
	dictionary = createText(L"DICTIONARY",
		searchBox.getPosition().x - searchBox.getSize().x / 2 + 250,
		searchBox.getPosition().y - searchBox.getSize().y / 2 - 200, 80);
	dictionary.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	dictionary.setFillColor(sf::Color(10, 123, 233, 255));

	//Set searchIcon
	searchIcon.setTexture(_data->_assets->getTexture(SEARCH_ICON));
	searchIcon.setOrigin(sf::Vector2f(searchIcon.getLocalBounds().width / 2, searchIcon.getLocalBounds().height / 2));
	searchIcon.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 + 435, searchBox.getPosition().y));
	searchIcon.setScale(sf::Vector2f(0.1, 0.1));

	//Set searchIconBox
	searchIconBox = createRectangleShape(65, 65,
		_data->_window->getSize().x / 2 + 436,
		_data->_window->getSize().y / 2);
	searchIconBox.setOrigin(sf::Vector2f(searchIconBox.getLocalBounds().width / 2, searchIconBox.getLocalBounds().height / 2));
	searchIconBox.setFillColor(sf::Color(10, 123, 233, 255));

	//Set dataSet
	getDataSet = L"Eng-Eng";
	dataSet = createText(getDataSet,
		searchBox.getPosition().x - searchBox.getSize().x / 2 - 250,
		searchBox.getPosition().y - searchBox.getSize().y / 2, 35);
	dataSet.setFont(_data->_assets->getFont(CHIVOMONO_REGULAR));
	dataSet.setFillColor(sf::Color(0, 0, 0, 255));

	//Set downArr
	downArr.setTexture(_data->_assets->getTexture(DOWN_ARR));
	downArr.setOrigin(sf::Vector2f(downArr.getLocalBounds().width / 2, downArr.getLocalBounds().height / 2));
	downArr.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 450, searchBox.getPosition().y));
	downArr.setScale(sf::Vector2f(0.12, 0.12));

	//Set dataBox
	dataBox = createRectangleShape(190, 230,
		searchBox.getPosition().x - searchBox.getSize().x / 2 - 230,
		downArr.getPosition().y + 30);
	dataBox.setOutlineThickness(3);
	dataBox.setOutlineColor(sf::Color(0, 0, 0, 255));

	//Set dataBoxContent
	dataBoxContent[0] = createText(L"Eng-Eng",
		dataBox.getPosition().x + 10,
		dataBox.getPosition().y + 10, 35);
	dataBoxContent[1] = createText(L"Eng-Vi",
		dataBox.getPosition().x + 10,
		dataBox.getPosition().y + 60, 35);
	dataBoxContent[2] = createText(L"Vi-Eng",
		dataBox.getPosition().x + 10,
		dataBox.getPosition().y + 110, 35);
	dataBoxContent[3] = createText(L"Emoji",
		dataBox.getPosition().x + 10,
		dataBox.getPosition().y + 160, 35);
	for (int i = 0; i < 4; i++)
	{
		dataBoxContent[i].setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
		dataBoxContent[i].setFillColor(sf::Color::Black);
	}
	
	//Set status 
	statusOn = 0;
	status = createText(L"Not found!",
		searchBox.getPosition().x - searchBox.getSize().x / 2 + 10,
		searchBox.getPosition().y + 50, 20);
	status.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	status.setFillColor(sf::Color::Red);

	//Set random
	random = createText(L"Random word", _data->_window->getSize().x / 2 + 475, _data->_window->getSize().y / 2 - 25, 40);
	random.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	random.setFillColor(sf::Color(10, 123, 233, 255));

	//Set suggestBox
	suggestBox = createRectangleShape(searchBox.getLocalBounds().width, 300,
		searchBox.getPosition().x - searchBox.getSize().x / 2,
		searchBox.getPosition().y + 55);
	suggestBox.setOutlineThickness(3);
	suggestBox.setOutlineColor(sf::Color(0, 0, 0, 255));

	//Set suggest
	for (int i = 0; i < 5; i++)
	{
		suggest[i] = createText(L"",
			suggestBox.getPosition().x + 10,
			suggestBox.getPosition().y + 10 + 50*i, 35);
		suggest[i].setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
		suggest[i].setFillColor(sf::Color::Black);
	}
}
void HomePage::processInput()
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
				searchBoxFocus = isFocus(searchBox, *_data->_window);
				if (searchBoxFocus)
				{
					curPosX = sf::Mouse::getPosition(*_data->_window).x;
				}
				dataBoxHidden = (downArrHover ? !dataBoxHidden : dataBoxHidden);
				for (int i = 0; i < 4; i++)
				{
					if (!dataBoxHidden && dataBoxContentHover[i])
					{
						getDataSet = dataBoxContent[i].getString();
					}
				}
				favListClick = (favListHover ? 1 : 0);
				historyClick = (historyHover ? 1 : 0);
				addWordClick = (addWordHover ? 1 : 0);
				resetClick = (resetHover ? 1 : 0);
				quizClick = (quizHover ? 1 : 0);
				searchIconClick = (searchIconHover ? 1 : 0);
				randomClick = (randomHover ? 1 : 0);
				for (int i = 0; i < 5; i++)
				{
					if (!getSearchBoxText.empty() && suggestHover[i])
					{
						getSearchBoxText = suggest[i].getString();
					}
				}
			}
			break;
		case sf::Event::TextEntered:
		{
			
			if (searchBoxFocus && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (event.key.code == 8)
				{
					int i = 0;
					for (;i < getSearchBoxText.size();i++)
					{
						if (searchBoxText.findCharacterPos(i).x > curPosX)
							break;
					}
					if (i == getSearchBoxText.size() - 1 && i >= 1)
					{
						curPosX -= 15;
						getSearchBoxText.erase(i - 1, 1);
					}
					else if (i >= 1)
					{
						curPosX -= 15;
						getSearchBoxText.erase(i - 1, 1);
					}
				}
				else
				{
					if (getSearchBoxText.empty())
					{
						getSearchBoxText += static_cast<wchar_t>(event.key.code);
						curPosX = searchBoxText.findCharacterPos(0).x;
					}
					else
					{
						int i = 0;
						for (;i < getSearchBoxText.size();i++)
						{
							if (searchBoxText.findCharacterPos(i).x > curPosX)
								break;
						}
						curPosX += 15;
						getSearchBoxText.insert(getSearchBoxText.begin() + i, static_cast<wchar_t>(event.key.code));
					}
				}
				blink = 1;
			}
			getSuggest = suggestWord(_data, getDataSet, getSearchBoxText);
			for (int i = 0; i < 5 && i < getSuggest.size(); i++)
			{
				suggest[i].setString(getSuggest[i]);
			}
			break;
		}
		case sf::Event::KeyPressed:
			if (searchBoxFocus)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					curPosX -= 15;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					curPosX += 15;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					searchIconClick = 1;
				}
				blink = 1;
			}
			break;
		}
		
		favListHover = isHover(favList, *_data->_window);
		historyHover = isHover(history, *_data->_window);
		addWordHover = isHover(addWord, *_data->_window);
		resetHover = isHover(reset, *_data->_window);
		quizHover = isHover(quiz, *_data->_window);
		searchIconHover = isHover(searchIconBox, *_data->_window);
		downArrHover = isHover(downArr, *_data->_window);
		randomHover = isHover(random, *_data->_window);
		
		for (int i = 0; i < 4; i++)
		{
			dataBoxContentHover[i] = isHover(dataBoxContent[i], *_data->_window);
		}
		for (int i = 0; i < 5; i++)
		{
			suggestHover[i] = isHover(suggest[i], *_data->_window);
		}
    }
}
void HomePage::update()
{
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 0.5)
	{
		blink = !blink;
		clock.restart();
	}
	//Hover
	(favListHover ? favList.setFillColor(sf::Color(255, 255, 255, 200)) : favList.setFillColor(sf::Color::White));
	(historyHover ? history.setFillColor(sf::Color(255, 255, 255, 200)) : history.setFillColor(sf::Color::White));
	(addWordHover ? addWord.setFillColor(sf::Color(255, 255, 255, 200)) : addWord.setFillColor(sf::Color::White));
	(resetHover ? reset.setFillColor(sf::Color(255, 255, 255, 200)) : reset.setFillColor(sf::Color::White));
	(quizHover ? quiz.setFillColor(sf::Color(255, 255, 255, 200)) : quiz.setFillColor(sf::Color::White));
	(randomHover ? random.setFillColor(sf::Color(10, 123, 233, 200)) : random.setFillColor(sf::Color(10, 123, 233, 255)));
	
	(searchIconHover ? searchIconBox.setFillColor(sf::Color(10, 123, 233, 150)) : searchIconBox.setFillColor(sf::Color(10, 123, 233, 255)));
	(downArrHover ? downArr.setColor(sf::Color(255, 255, 255, 100)) : downArr.setColor(sf::Color::White));
	for (int i = 0;i < 4; i++)
	{
		(dataBoxContentHover[i] ? dataBoxContent[i].setFillColor(sf::Color(0, 0, 0, 100)) : dataBoxContent[i].setFillColor(sf::Color::Black));
	}
	for (int i = 0;i < 5; i++)
	{
		(suggestHover[i] ? suggest[i].setFillColor(sf::Color(0, 0, 0, 100)) : suggest[i].setFillColor(sf::Color::Black));
	}
	//Focus
	(searchBoxFocus ? searchBox.setOutlineColor(sf::Color(0, 0, 0, 200)) : searchBox.setOutlineColor(sf::Color(0, 0, 0, 100)));
	((!getSearchBoxText.empty()) ? searchBoxPlaceholder.setString("") : searchBoxPlaceholder.setString("Search..."));

	//Text  
	
	dataSet.setString(getDataSet);
	searchBoxText.setString(getSearchBoxText);
	((blink && searchBoxFocus) ? cursor.setString("|") : cursor.setString(""));
	
	if (getSearchBoxText.empty() || curPosX < searchBoxText.findCharacterPos(0).x) 
	{
		cursor.setPosition(searchBox.getPosition().x - searchBox.getSize().x / 2,
						searchBox.getPosition().y - searchBox.getSize().y / 2 + 7);
		curPosX = cursor.getPosition().x;
	}
	else if (curPosX >= searchBoxText.findCharacterPos(getSearchBoxText.size() - 1).x) {
		cursor.setPosition(searchBox.getPosition().x - searchBox.getSize().x / 2 + searchBoxText.getGlobalBounds().width + 7,
						searchBox.getPosition().y - searchBox.getSize().y / 2 + 7);
		curPosX = cursor.getPosition().x;
	}
	else
	{
		int i = 0;
		for (; i < getSearchBoxText.size(); i++)
		{
			if (curPosX <= searchBoxText.findCharacterPos(i).x)
				break;
		}
		cursor.setPosition(searchBoxText.findCharacterPos(i).x - 8,
						searchBox.getPosition().y - searchBox.getSize().y / 2 + 7);
		curPosX = cursor.getPosition().x;
	}

	//Click
	if (favListClick)
	{
		_data->_states->addState(new FavList(_data));
		favListClick = 0;
	}
	if (historyClick)
	{
		historyFile.close();
		_data->_states->addState(new History(_data));
		historyClick = 0;
	}
	if (addWordClick)
	{
		_data->_states->addState(new CreateWord(_data, L"Add new word", getDataSet));
		addWordClick = 0;
	}
	if (resetClick)
	{
		_data->_states->addState(new Confirm(_data, L"Are you sure to reset the app?"));
		resetClick = 0;
	}
	if (quizClick)
	{
		_data->_states->addState(new Quiz(_data));
		quizClick = 0;
	}
	if (randomClick)
	{
		std::wstring line = randomWord(_data);
		getDataSet = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
		getSearchBoxText = line.substr(0, line.find('('));
		randomClick = 0;
	}
	if (searchIconClick)
	{
		std::wstring dtset = dataSet.getString();
		std::wstring line = getSearchBoxText + L"(" + dtset + L")";
		if (!existWord(line , L"Resource\\RemoveWord.txt") && search(getDataset(dataSet.getString(), _data), getSearchBoxText) != nullptr)
		{
			if (getDataSet != L"Emoji")
			{
				historyFile << line << std::endl;
			}
			_data->_states->addState(new WordDefinition(_data, search(getDataset(dataSet.getString(), _data), getSearchBoxText), dataSet.getString()));
			getSearchBoxText.clear();
		}
		else
		{
			statusOn = 1;
		}
		searchIconClick = 0;
	}
}
void HomePage::draw()
{
	_data->_window->clear(sf::Color(248, 245, 251, 255));
	_data->_window->setView(view);
	_data->_window->draw(searchBox);
	_data->_window->draw(searchBoxText);
	_data->_window->draw(cursor);
	_data->_window->draw(searchBoxPlaceholder);
	_data->_window->draw(dictionaryIcon);
	_data->_window->draw(dictionary);
	_data->_window->draw(searchIconBox);
	_data->_window->draw(searchIcon);
	_data->_window->draw(dataSet);
	_data->_window->draw(downArr);
	_data->_window->draw(random);
	if (getSearchBoxText != L"")
	{
		_data->_window->draw(suggestBox);
		for (int i = 0; i < 5; i++)
		{
			_data->_window->draw(suggest[i]);
		}
	}
	
	if (!dataBoxHidden)
	{
		_data->_window->draw(dataBox);
		_data->_window->draw(dataBoxContent[0]);
		_data->_window->draw(dataBoxContent[1]);
		_data->_window->draw(dataBoxContent[2]);
		_data->_window->draw(dataBoxContent[3]);
	}
	if (statusOn)
	{
		_data->_window->draw(status);
	}
	
	//navbar
	_data->_window->draw(navbar);
	_data->_window->draw(favList);
	_data->_window->draw(history);
	_data->_window->draw(addWord);
	_data->_window->draw(reset);
	_data->_window->draw(quiz);
	_data->_window->display();
}
