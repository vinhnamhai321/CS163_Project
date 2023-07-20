#pragma once
#include"SFML/Graphics.hpp"

sf::RectangleShape createRectangleShape(float width, float height, float x = 0, float y = 0);

sf::Text createText(std::wstring string, float x, float y, int size = 30);

template<class hover> 
bool isHover(hover obj, sf::Window& data, int translate)
{
	bool isHover;
	isHover = (obj.getGlobalBounds()
		.contains(sf::Vector2f(sf::Mouse::getPosition(data).x, sf::Mouse::getPosition(data).y + translate))
		? 1 : 0);
	return isHover;
}
template<class focus>
bool isFocus(focus obj, sf::Window& data, int translate)
{
	return isHover(obj, data, translate);
}
void removeWord(std::wstring word, std::wstring path);




