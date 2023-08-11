#pragma once
#include"SFML/Graphics.hpp"
#define EV "Data-set\\EV_final.txt"
#define EE "Data-set\\EE_final.txt"
#define VE "Data-set\\VE_final.txt"
#define EVADD "Resource\\ENG-VIaddWord.txt"
#define EEADD "Resource\\ENG-ENGaddWord.txt"
#define VEADD "Resource\\VI-ENGaddWord.txt"
enum
{
	HELVETICA_BOLD = 0, LIGHT, CHIVOMONO_LIGHT, CHIVOMONO_REGULAR, KANIT, MONTSERRAT_EXTRABOLD,DICTIONARY_ICON, SEARCH_ICON, DOWN_ARR, BACK_ARR,
	HISTORY_CLOCK, DELETE_ICON, BACKGROUND

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


