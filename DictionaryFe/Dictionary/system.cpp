#include"system.h"
#include"Loading.h"
#include<omp.h>
#include<iostream>
System::System() : _data(new data)
{
	_data->eeDone = 0;
	_data->evDone = 0;
	_data->veDone = 0;
	_data->emojiDone = 0;
	_data->_window->create(sf::VideoMode(1600, 900), "Dictionary", sf::Style::Default);
	_data->_states->addState(new Loading(_data));
	run();
}
System::~System()
{
}
void System::run()
{
#pragma omp parallel sections
	{
#pragma omp section
		{
			sf::Clock clock;
			sf::Time timeSinceLastFrame = sf::Time::Zero;

			while (_data->_window->isOpen())
			{
				timeSinceLastFrame += clock.restart();
				while (timeSinceLastFrame > TIME_PER_FRAME)
				{
					timeSinceLastFrame -= TIME_PER_FRAME;
					_data->_states->processStateChange();
					_data->_states->getCurrentState()->processInput();
					_data->_states->getCurrentState()->update();
					_data->_states->getCurrentState()->draw();
				}
			}
		}
#pragma omp section
		{
			if (!_data->eeDone)
			{
				_data->ee.loadDataSet(EE, _data->eeKeyword);
				_data->ee.loadDataSet(EEADD, _data->eeKeyword);
				_data->eeDone = 1;
			}
		}
#pragma omp section
		{
			if (!_data->evDone)
			{
				_data->ev.loadDataSet(EV, _data->evKeyword);
				_data->ev.loadDataSet(EVADD, _data->evKeyword);
				_data->evDone = 1;
			}
		}
#pragma omp section
		{
			if (!_data->veDone && !_data->emojiDone)
			{
				_data->ve.loadDataSet(VE, _data->veKeyword);
				_data->ve.loadDataSet(VEADD, _data->veKeyword);
				_data->veDone = 1;
				_data->emoji.loadDataSet(EMOJI, _data->emojiIcon);
				_data->emojiDone = 1;

			}
		}
	}
	
}

