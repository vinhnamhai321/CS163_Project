#pragma once
#include"SFML/Graphics.hpp"
enum
{
	HELVETICA_BOLD = 0, LIGHT, CHIVOMONO_LIGHT, CHIVOMONO_REGULAR, KANIT, DICTIONARY_ICON, SEARCH_ICON, DOWN_ARR, BACK_ARR,
	HISTORY_CLOCK, DELETE_ICON

};
class assetManager
{
private:
	sf::Texture* _textures = new sf::Texture[100];
	sf::Font* _fonts = new sf::Font[100];


public:
	assetManager();
	~assetManager();
	void addTexture(int id, std::string filePath);
	void addFont(int id, std::string filePath);
	sf::Texture& getTexture(int id);
	sf::Font& getFont(int id);

};


