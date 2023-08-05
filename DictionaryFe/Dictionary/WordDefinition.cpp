#include "WordDefinition.h"
#include "HandmadeFunc.h"
#include"Confirm.h"
#include"CreateWord.h"
#include<locale>
#include<codecvt>
WordDefinition::WordDefinition(data* data, WordDef* keyword, std::wstring dataset): _data(data), _keyword(keyword), _dataset(dataset)
{}
WordDefinition::~WordDefinition()
{}
void WordDefinition::init()
{
	windowTranslateX = 0;
	windowTranslateY = 0;
	//set view
	view.setSize(sf::Vector2f(1600, 900));
	view.setCenter(sf::Vector2f(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2));

	//Set backArr
	backArr.setTexture(_data->_assets->getTexture(BACK_ARR));
	backArr.setPosition(sf::Vector2f(0, 0));
	backArr.setScale(sf::Vector2f(0.2, 0.2));

	//Set word
	word = createText(_keyword->keyWord,200, 100, 60);
	word.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	word.setFillColor(sf::Color(10, 123, 233, 255));

	//Set def
	for (int i = 0;i < _keyword->definition.size(); i++)
	{
		sf::Text def;
		def.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
		def.setString(_keyword->definition[i]);
		def.setPosition(sf::Vector2f(200, i*50 + 200));
		def.setFillColor(sf::Color::Black);
		def.setCharacterSize(25);
		definition.push_back(def);
	}

	//Set addFavList
	addFavList.setFont(_data->_assets->getFont(MONTSERRAT_EXTRABOLD));
	addFavList.setString("Add to favorite list");
	addFavList.setPosition(sf::Vector2f(300, 50));
	addFavList.setFillColor(sf::Color(10, 123, 233, 255));

	favFile.open(L"Resource\\FavList.txt", std::ios::app);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	favFile.imbue(loc);

	//Set status
	status.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	status.setString("This word has been added to favorite list");
	status.setPosition(sf::Vector2f(300, 80));
	status.setFillColor(sf::Color::Red);
	status.setCharacterSize(20);

	//Set editWord
	editWord.setFont(_data->_assets->getFont(MONTSERRAT_EXTRABOLD));
	editWord.setString("Edit word");
	editWord.setPosition(sf::Vector2f(800, 50));
	editWord.setFillColor(sf::Color(10, 123, 233, 255));

	//Set removeWord
	removeWord.setFont(_data->_assets->getFont(MONTSERRAT_EXTRABOLD));
	removeWord.setString("Remove word");
	removeWord.setPosition(sf::Vector2f(1200, 50));
	removeWord.setFillColor(sf::Color::Red);

	//Set bar
	bar = createRectangleShape(_data->_window->getSize().x, 100);
	bar.setFillColor(sf::Color(248, 245, 251, 255));
}
void WordDefinition::processInput()
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
				addFavListClick = (addFavListHover ? 1 : 0);
				editWordClick = (editWordHover ? 1 : 0);
				removeWordClick = (removeWordHover ? 1 : 0);
			}
			break;
		case sf::Event::MouseWheelScrolled:
		{
			int translateY = 0;
			if (event.mouseWheelScroll.delta > 0 && windowTranslateY > 0) {
				view.move(sf::Vector2f(0, -30));
				translateY = -30;
				windowTranslateY -= 30;
			}
			if (event.mouseWheelScroll.delta < 0 && windowTranslateY < definition.size() * 50 - 50) {
				view.move(sf::Vector2f(0, 30));
				translateY = 30;
				windowTranslateY += 30;
			}
			bar.move(sf::Vector2f(0, translateY));
			addFavList.move(sf::Vector2f(0, translateY));
			backArr.move(sf::Vector2f(0, translateY));
			status.move(sf::Vector2f(0, translateY));
			editWord.move(sf::Vector2f(0, translateY));
			removeWord.move(sf::Vector2f(0, translateY));
			break;
		}
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
			addFavList.move(sf::Vector2f(translateX, 0));
			status.move(sf::Vector2f(translateX, 0));
			editWord.move(sf::Vector2f(translateX, 0));
			removeWord.move(sf::Vector2f(translateX, 0));
			break;
		}
		
		}
		
		backArrHover = isHover(backArr, *_data->_window, windowTranslateY, windowTranslateX);
		addFavListHover = isHover(addFavList, *_data->_window, windowTranslateY, windowTranslateX);
		editWordHover = isHover(editWord, *_data->_window, windowTranslateY, windowTranslateX);
		removeWordHover = isHover(removeWord, *_data->_window, windowTranslateY, windowTranslateX);
	}
}
void WordDefinition::update()
{
	//Hover
	(backArrHover ? backArr.setColor(sf::Color(255, 255, 255, 100)) : backArr.setColor(sf::Color::White));
	(addFavListHover ? addFavList.setFillColor(sf::Color(10, 123, 233, 100)) : addFavList.setFillColor(sf::Color(10, 123, 233, 255)));
	(editWordHover ? editWord.setFillColor(sf::Color(10, 123, 233, 100)) : editWord.setFillColor(sf::Color(10, 123, 233, 255)));
	(removeWordHover ? removeWord.setFillColor(sf::Color(255, 0, 0, 100)) : removeWord.setFillColor(sf::Color::Red));
	//Click
	if (backArrClick)
	{
		favFile.close();
		_data->_states->removeState();
		backArrClick = 0;
	}
	if (addFavListClick)
	{
		std::wstring line = _keyword->keyWord + L"(" + _dataset + L")";
		if (!existWord(line, L"Resource\\FavList.txt"))
		{
			favFile << line << std::endl;
		}
		statusOn = 1;
		addFavListClick = 0;
	}
	if (editWordClick)
	{
		_data->_states->addState(new CreateWord(_data, L"Edit word", _keyword->keyWord, _keyword->definition));
		favFile.close();
		editWordClick = 0;
	}
	if (editWordClick)
	{
		editWordClick = 0;
	}
	if (removeWordClick)
	{
		std::wstring line = _keyword->keyWord + L"(" + _dataset + L")";
		_data->_states->addState(new Confirm(_data, L"Are you sure to remove this word?", line));
		removeWordClick = 0;
	}
}
void WordDefinition::draw()
{
	_data->_window->clear(sf::Color(248, 245, 251, 255));
	_data->_window->setView(view);
	_data->_window->draw(word);
	for (int i = 0; i < definition.size(); i++)
	{
		_data->_window->draw(definition[i]);
	}
	_data->_window->draw(bar);
	_data->_window->draw(backArr);
	_data->_window->draw(addFavList);
	if (statusOn)
	{
		_data->_window->draw(status);
	}
	_data->_window->draw(editWord);
	_data->_window->draw(removeWord);
	_data->_window->display();
	
}