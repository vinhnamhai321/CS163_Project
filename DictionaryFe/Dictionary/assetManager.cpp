#include"assetManager.h"
assetManager::assetManager()
{

}
assetManager::~assetManager()
{

}
void assetManager::addTexture(int id, std::string filePath)
{
	sf::Texture texture;
	if (texture.loadFromFile(filePath))
	{
		_textures[id] = texture;
	}
}
void assetManager::addFont(int id, std::string filePath)
{
	sf::Font font;
	if (font.loadFromFile(filePath))
	{
		_fonts[id] = font;
	}
}

sf::Texture& assetManager::getTexture(int id)
{
	return _textures[id];
}
sf::Font& assetManager::getFont(int id)
{
	return _fonts[id];
}
