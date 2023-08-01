#pragma once
#include"SFML/Graphics.hpp"
#include"Trie.h"
#include"system.h"
sf::RectangleShape createRectangleShape(float width, float height, float x = 0, float y = 0);
sf::Text createText(std::wstring string, float x, float y, int size = 30);
template<class hover> 
bool isHover(hover obj, sf::Window& data, int translate = 0)
{
	bool isHover;
	isHover = (obj.getGlobalBounds()
		.contains(sf::Vector2f(sf::Mouse::getPosition(data).x, sf::Mouse::getPosition(data).y + translate))
		? 1 : 0);
	return isHover;
}
template<class focus>
bool isFocus(focus obj, sf::Window& data, int translate = 0)
{
	return isHover(obj, data, translate);
}
void removeWord(std::wstring line, std::wstring path);
Trie getDataset(std::wstring dataset, data* _data);
bool existWord(std::wstring line, std::wstring path);






