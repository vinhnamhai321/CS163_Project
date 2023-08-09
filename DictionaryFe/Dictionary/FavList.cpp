#include "FavList.h"
#include"HandmadeFunc.h"
#include<locale>
#include<codecvt>
#include"WordDefinition.h"

FavList::FavList(data* data) : _data(data)
{}
FavList::~FavList()
{}
void FavList::init()
{
	//set view
	view.setSize(sf::Vector2f(1600, 900));
	view.setCenter(sf::Vector2f(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2));
	windowTranslateY = 0;

	// set historyList
	favFile.open(L"Resource\\FavList.txt", std::ios::in);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	favFile.imbue(loc);
	std::wstring getHistoryList;
	while (!favFile.eof())
	{
		getline(favFile, getHistoryList);
		if (getHistoryList.empty())
			continue;
		sf::Text historyWord;
		historyWord.setString(getHistoryList);
		favList.push_back(historyWord);
	}
	for (int i = 0; i < favList.size(); i++)
	{
		favList[i].setPosition(sf::Vector2f(100, (favList.size() - i) * 100 + 60));
		favList[i].setFont(_data->_assets->getFont(CHIVOMONO_REGULAR));
		favList[i].setFillColor(sf::Color::Black);
		favList[i].setCharacterSize(50);
	}
	favListHover = new bool[favList.size()];
	favListClick = new bool[favList.size()];
	for (int i = 0; i < favList.size(); i++)
	{
		favListHover[i] = 0;
		favListClick[i] = 0;
	}

	//Set clone
	clone.setFont(_data->_assets->getFont(CHIVOMONO_REGULAR));
	clone.setCharacterSize(50);
	clone.setFillColor(sf::Color(0, 0, 0, 100));
	clone.setString(L"");
	cloneIdx = -1;

	//Set backArr
	backArr.setTexture(_data->_assets->getTexture(BACK_ARR));
	backArr.setPosition(sf::Vector2f(0, 0));
	backArr.setScale(sf::Vector2f(0.2, 0.2));

	//Set tiltle
	title = createText(L"Favorite List", 400, 0, 80);
	title.setFont(_data->_assets->getFont(HELVETICA_BOLD));
	title.setFillColor(sf::Color(10, 123, 233, 255));

	//Set bar
	bar = createRectangleShape(_data->_window->getSize().x, 100);
	bar.setFillColor(sf::Color(248, 245, 251, 255));

	//Set deleteIcon
	deleteIcon.setTexture(_data->_assets->getTexture(DELETE_ICON));
	deleteIcon.setPosition(sf::Vector2f(1500, 770));
	deleteIcon.setScale(sf::Vector2f(0.2, 0.2));

}
void FavList::processInput()
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
			if (event.mouseWheelScroll.delta < 0 && windowTranslateY < favList.size() * 100 - 50) {
				view.move(sf::Vector2f(0, 30));
				translateY = 30;
				windowTranslateY += 30;
			}
			bar.move(sf::Vector2f(0, translateY));
			backArr.move(sf::Vector2f(0, translateY));
			title.move(sf::Vector2f(0, translateY));
			deleteIcon.move(sf::Vector2f(0, translateY));
			break;
		}
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				backArrClick = (backArrHover ? 1 : 0);
				for (int i = 0; i < favList.size(); i++)
				{
					if (isHover(favList[i], *_data->_window, windowTranslateY) && sf::Mouse::getPosition(*_data->_window).y > 100)
					{
						clone.setString(favList[i].getString());
						cloneIdx = i;

					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				for (int i = 0; i < favList.size(); i++)
				{
					
					favListClick[i] = (favListHover[i] ? 1 : 0);
					
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.key.code == sf::Mouse::Left)
			{
				if (clone.getGlobalBounds().intersects(deleteIcon.getGlobalBounds()))
				{
					removeWord(clone.getString(), L"Resource\\FavList.txt");
					favList.erase(favList.begin() + cloneIdx);
				}
				clone.setString(L"");
			}
			break;
		case sf::Event::MouseMoved:
			clone.setPosition(sf::Mouse::getPosition(*_data->_window).x, sf::Mouse::getPosition(*_data->_window).y + windowTranslateY);
			break;
		}
		backArrHover = isHover(backArr, *_data->_window, windowTranslateY);
		for (int i = 0; i < favList.size(); i++)
		{
			favListHover[i] = isHover(favList[i], *_data->_window, windowTranslateY);
		}

	}
}
void FavList::update()
{
	//Hover
	(backArrHover ? backArr.setColor(sf::Color(255, 255, 255, 100)) : backArr.setColor(sf::Color::White));
	for (int i = 0; i < favList.size(); i++)
	{
		(favListHover[i] ? favList[i].setFillColor(sf::Color(0, 0, 0, 100)) : favList[i].setFillColor(sf::Color::Black));
	}
	//Click
	if (backArrClick)
	{
		favFile.close();
		_data->_states->removeState();
		backArrClick = 0;
	}
	for (int i = 0; i < favList.size(); i++)
	{
		if (favListClick[i])
		{
			std::wstring line =favList[i].getString();
			std::wstring dtset = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
			std::wstring word = line.substr(0, line.find('('));
			favFile.close();
			favListClick[i] = 0;
			_data->_states->addState(new WordDefinition(_data, search(getDataset(dtset, _data), word), dtset), 1);

		}
	}
}
void FavList::draw()
{
	_data->_window->clear(sf::Color(248, 245, 251, 255));
	_data->_window->setView(view);
	for (int i = 0; i < favList.size(); i++)
	{
		_data->_window->draw(favList[i]);
	}
	_data->_window->draw(clone);
	//fixed obj
	_data->_window->draw(bar);
	_data->_window->draw(title);
	_data->_window->draw(backArr);
	_data->_window->draw(deleteIcon);
	_data->_window->display();
}