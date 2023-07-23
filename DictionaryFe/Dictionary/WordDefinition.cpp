#include "WordDefinition.h"
#include "HandmadeFunc.h"
WordDefinition::WordDefinition(data* data, WordDef* keyword): _data(data), _keyword(keyword)
{}
WordDefinition::~WordDefinition()
{}
void WordDefinition::init()
{
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
		def.setFont(_data->_assets->getFont(CHIVOMONO_REGULAR));
		def.setString(_keyword->definition[i]);
		def.setPosition(sf::Vector2f(200, i*50 + 200));
		def.setFillColor(sf::Color::Black);
		definition.push_back(def);
	}
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
			}
			break;
		}
		backArrHover = isHover(backArr, *_data->_window);
	}
}
void WordDefinition::update()
{
	//Hover
	(backArrHover ? backArr.setColor(sf::Color(255, 255, 255, 100)) : backArr.setColor(sf::Color::White));
	//Click
	if (backArrClick)
	{
		_data->_states->removeState();
		backArrClick = 0;
	}
}
void WordDefinition::draw()
{
	_data->_window->clear(sf::Color(248, 245, 251, 255));
	_data->_window->draw(backArr);
	_data->_window->draw(word);
	for (int i = 0; i < definition.size(); i++)
	{
		_data->_window->draw(definition[i]);
	}
	_data->_window->display();
}