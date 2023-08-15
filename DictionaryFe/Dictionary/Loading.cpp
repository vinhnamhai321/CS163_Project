#include "Loading.h"
#include "HomePage.h"
#include"HandmadeFunc.h"
#include<iostream>


Loading::Loading(data* data): _data(data)
{}
Loading::~Loading()
{}
void Loading::init()
{
	_data->_assets->addFont(LIGHT, "Fonts\\Light.ttf");
	_data->_assets->addFont(HELVETICA_BOLD, "Fonts\\Helvetica-Bold.ttf");
	_data->_assets->addFont(CHIVOMONO_LIGHT, "Fonts\\ChivoMono-Light.ttf");
	_data->_assets->addFont(CHIVOMONO_REGULAR, "Fonts\\ChivoMono-Regular.ttf");
	_data->_assets->addFont(KANIT, "Fonts\\Kanit-Regular.ttf");
	_data->_assets->addFont(MONTSERRAT_EXTRABOLD, "Fonts\\Montserrat-ExtraBold.ttf");
	_data->_assets->addTexture(DICTIONARY_ICON, "Img\\dictionaryIcon.png");
	_data->_assets->addTexture(SEARCH_ICON, "Img\\searchIcon.png");
	_data->_assets->addTexture(DOWN_ARR, "Img\\downArr.png");
	_data->_assets->addTexture(BACK_ARR, "Img\\backArr.png");
	_data->_assets->addTexture(HISTORY_CLOCK, "Img\\historyClock.png");
	_data->_assets->addTexture(DELETE_ICON, "Img\\deleteIcon.png");
	_data->_assets->addTexture(BACKGROUND, "Img\\background.jpg");
	
	
	//set loading
	loading.setFont(_data->_assets->getFont(MONTSERRAT_EXTRABOLD));
	loading.setCharacterSize(60);
	loading.setString("LOADING...");
	loading.setFillColor(sf::Color(10, 123, 233, 255));
	loading.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 200, _data->_window->getSize().y / 2 + 200));

	//set background
	background.setTexture(_data->_assets->getTexture(BACKGROUND));
	background.setPosition(sf::Vector2f(_data->_window->getSize().x / 2 - 350, _data->_window->getSize().y / 2 - 400));
	background.setScale(sf::Vector2f(0.65, 0.65));
	background.setColor(sf::Color(255, 255, 255, 200));
}
void Loading::processInput()
{
	sf::Event event;
	while (_data->_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_data->_window->close();
			break;
		}
	}
}
void Loading::update()
{
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 0.1)
	{
		clock.restart();
	}
	if (_data->eeDone && _data->evDone && _data->veDone && _data->emojiDone)
	{
		_data->_states->addState(new HomePage(_data), 1);
	}
}
void Loading::draw()
{
	_data->_window->clear(sf::Color(214, 246, 244, 255));
	_data->_window->draw(background);
	_data->_window->draw(loading);
	
	_data->_window->display();
}