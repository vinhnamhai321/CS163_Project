#include "Confirm.h"
#include"HandmadeFunc.h"
#include"HomePage.h"
#include<locale>
#include<codecvt>
Confirm::Confirm(data* data, std::wstring status, std::wstring line) : _data(data), _status(status), _line(line)
{}
Confirm::~Confirm()
{}
void Confirm::init()
{
	removeWordFile.open(L"Resource\\RemoveWord.txt", std::ios::app);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	removeWordFile.imbue(loc);
	//set view
	view.setSize(sf::Vector2f(1600, 900));
	view.setCenter(sf::Vector2f(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2));
	
	//Set box 
	box = createRectangleShape(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2,
		_data->_window->getSize().x / 2,
		_data->_window->getSize().y / 2);
	box.setOrigin(sf::Vector2f(box.getLocalBounds().width / 2, box.getLocalBounds().height / 2));
	box.setOutlineThickness(3);
	box.setOutlineColor(sf::Color(0, 0, 0, 100));

	//Set yesButton
	yesButton = createRectangleShape(120, 40,
		600,
		_data->_window->getSize().y / 2 + 150);
	yesButton.setOrigin(sf::Vector2f(yesButton.getLocalBounds().width / 2, yesButton.getLocalBounds().height / 2));
	yesButton.setOutlineThickness(3);
	yesButton.setOutlineColor(sf::Color(0, 0, 0, 100));

	yes = createText(L"Yes", 570, _data->_window->getSize().y / 2 + 130);
	yes.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	yes.setFillColor(sf::Color::Yellow);

	//Set noButton
	noButton = createRectangleShape(120, 40,
		1000,
		_data->_window->getSize().y / 2 + 150);
	noButton.setOrigin(sf::Vector2f(noButton.getLocalBounds().width / 2, noButton.getLocalBounds().height / 2));
	noButton.setOutlineThickness(3);
	noButton.setOutlineColor(sf::Color(0, 0, 0, 100));

	no = createText(L"No", 980, _data->_window->getSize().y / 2 + 130);
	no.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	no.setFillColor(sf::Color::Red);

	//Set status
	status = createText(_status, _data->_window->getSize().x / 2 - 270, _data->_window->getSize().y / 2);
	status.setFont(_data->_assets->getFont(CHIVOMONO_LIGHT));
	status.setFillColor(sf::Color::Black);
}
void Confirm::processInput()
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
				yesButtonClick = (yesButtonHover ? 1 : 0);
				noButtonClick = (noButtonHover ? 1 : 0);
			}
			break;
		}
		yesButtonHover = isHover(yesButton, *_data->_window);
		noButtonHover = isHover(noButton, *_data->_window);
	}

}
void Confirm::update()
{
	//Hover
	(yesButtonHover ? yesButton.setOutlineColor(sf::Color::Black) : yesButton.setOutlineColor(sf::Color(0, 0, 0, 100)));
	(noButtonHover ? noButton.setOutlineColor(sf::Color::Black) : noButton.setOutlineColor(sf::Color(0, 0, 0, 100)));

	//Click;
	if (yesButtonClick)
	{
		_data->_states->removeState();
		if (_status == L"Are you sure to remove this word?")
		{
			removeWordFile << _line << std::endl;
			removeWord(_line, L"Resource\\History.txt");
			removeWord(_line, L"Resource\\FavList.txt");
		}
		if (_status == L"Are you sure to reset the app?")
		{
			std::ofstream historyFile("Resource\\History.txt");
			historyFile.clear();
			historyFile.close();
			std::ofstream favListFile("Resource\\FavList.txt");
			favListFile.clear();
			favListFile.close();
			std::ofstream removeFile("Resource\\RemoveWord.txt");
			removeFile.clear();
			removeFile.close();
			resetAddWord(_data->ee, L"Resource\\Eng-EngaddWord.txt");
			std::wofstream EEaddFile("Resource\\Eng-EngaddWord.txt");
			EEaddFile.clear();
			EEaddFile.close();
			resetAddWord(_data->ev, L"Resource\\Eng-ViaddWord.txt");
			std::wofstream EVaddFile("Resource\\Eng-ViaddWord.txt");
			EVaddFile.clear();
			EVaddFile.close();
			resetAddWord(_data->ve, L"Resource\\Vi-EngaddWord.txt");
			std::wofstream VEaddFile("Resource\\Vi-EngaddWord.txt");
			VEaddFile.clear();
			VEaddFile.close();
			resetAddWord(_data->emoji, L"Resource\\EmojiaddWord.txt");
			std::wofstream emojiaddFile("Resource\\EmojiaddWord.txt");
			emojiaddFile.clear();
			emojiaddFile.close();
			resetEditWord(_data->ee, L"Resource\\Eng-EngeditWord.txt");
			std::wofstream EEeditFile("Resource\\Eng-EngeditWord.txt");
			EEeditFile.clear();
			EEeditFile.close();
			resetEditWord(_data->ev, L"Resource\\Eng-VieditWord.txt");
			std::wofstream EVeditFile("Resource\\Eng-VieditWord.txt");
			EVeditFile.clear();
			EVeditFile.close();
			resetEditWord(_data->ve, L"Resource\\Vi-EngeditWord.txt");
			std::wofstream VEeditFile("Resource\\Vi-EngeditWord.txt");
			VEeditFile.clear();
			VEeditFile.close();
			resetEditWord(_data->emoji, L"Resource\\EmojieditWord.txt");
			std::wofstream emojieditFile("Resource\\EmojieditWord.txt");
			emojieditFile.clear();
			emojieditFile.close();
			_data->_states->addState(new HomePage(_data), 1);
		}
		removeWordFile.close();
		yesButtonClick = 0;
	}
	if (noButtonClick)
	{
		removeWordFile.close();
		_data->_states->removeState();
		noButtonClick = 0;
	}
}
void Confirm::draw()
{
	_data->_window->setView(view);
	_data->_window->draw(box);
	_data->_window->draw(yesButton);
	_data->_window->draw(yes);
	_data->_window->draw(noButton);
	_data->_window->draw(no);
	_data->_window->draw(status);
	_data->_window->display();
}