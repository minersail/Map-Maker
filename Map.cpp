#include "stdafx.h"
#include "Map.h"

Map::Map(std::string filename, sf::Vector2i tile, int* tiles, int width, int height)
{
	Load(filename); // stores the tileset in this object's sprite's texture
	assert(IsLoaded());

	mapWidth = width;
	mapHeight = height;
	tileMap = tiles;
	tileSize = tile;

    // resize the vertex array to fit the level size
    VerticeList.setPrimitiveType(sf::Quads);
    VerticeList.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i)
	{
        for (int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
			int tu = tileNumber % (GetSprite().getTexture()->getSize().x / tile.x);
			int tv = tileNumber / (GetSprite().getTexture()->getSize().x / tile.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &VerticeList[(i + j * width) * 4];

            // define its 4 corners
			quad[0].position = sf::Vector2f(i * tile.x, j * tile.y);
			quad[1].position = sf::Vector2f((i + 1) * tile.x, j * tile.y);
			quad[2].position = sf::Vector2f((i + 1) * tile.x, (j + 1) * tile.y);
			quad[3].position = sf::Vector2f(i * tile.x, (j + 1) * tile.y);

            // define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tile.x, tv * tile.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile.x, tv * tile.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile.x, (tv + 1) * tile.y);
			quad[3].texCoords = sf::Vector2f(tu * tile.x, (tv + 1) * tile.y);
        }
	}
}

Map::Map(std::string filename, sf::Vector2i tile, std::string mapname, int width, int height)
{
	Load(filename); // stores the tileset in this object's sprite's texture
	assert(IsLoaded());

	mapWidth = width;
	mapHeight = height;
	tileMap = new int[width * height];
	for (int i = 0; i < width * height; i++)tileMap[i] = 0;
	tileSize = tile;
	
	LoadMap(mapname, width, height);

    // resize the vertex array to fit the level size
    VerticeList.setPrimitiveType(sf::Quads);
    VerticeList.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i)
	{
        for (int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tileMap[i + j * width];

            // find its position in the tileset texture
			int tu = tileNumber % (GetSprite().getTexture()->getSize().x / tile.x);
			int tv = tileNumber / (GetSprite().getTexture()->getSize().x / tile.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &VerticeList[(i + j * width) * 4];

            // define its 4 corners
			quad[0].position = sf::Vector2f(i * tile.x, j * tile.y);
			quad[1].position = sf::Vector2f((i + 1) * tile.x, j * tile.y);
			quad[2].position = sf::Vector2f((i + 1) * tile.x, (j + 1) * tile.y);
			quad[3].position = sf::Vector2f(i * tile.x, (j + 1) * tile.y);

            // define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tile.x, tv * tile.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile.x, tv * tile.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile.x, (tv + 1) * tile.y);
			quad[3].texCoords = sf::Vector2f(tu * tile.x, (tv + 1) * tile.y);
        }
	}
}

Map::~Map()
{
}

void Map::Reload(int position, int newValue)
{
	tileMap[position] = newValue;

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < mapWidth; ++i)
	{
        for (int j = 0; j < mapHeight; ++j)
        {
            // get the current tile number
            int tileNumber = tileMap[i + j * mapWidth];

            // find its position in the tileset texture
			int tu = tileNumber % (GetSprite().getTexture()->getSize().x / tileSize.x);
			int tv = tileNumber / (GetSprite().getTexture()->getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &VerticeList[(i + j * mapWidth) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
	}
}

void Map::LoadMap(std::string filename, int width, int height)
{
	std::ifstream inputfile(filename);
	std::string map;

	for (int i = 0; i < height; i++)
	{
		std::getline(inputfile, map);
		for (int j = 0; j < width * 4; j += 4)
		{
			int num1 = (map[j] - '0') * 10;
			int num2 = map[j + 1] - '0';

			tileMap[i * height + j / 4] = num1 + num2;
		}
	}
	inputfile.close();
}

void Map::Export()
{
	std::string name;
	std::cout << "Enter name to store map with (type cancel to cancel): ";
	std::cin >> name;

	if (name == "cancel")
	{
		std::cout << "Export canceled." << std::endl;
		return;
	}
	else
	{
		std::cout << "Map data saved to \"maps/" + name + ".txt\"." << std::endl;
	}

	std::ofstream outputfile;
	outputfile.open("maps/" + name + ".txt");
	
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			outputfile << (tileMap[j + i * mapHeight] < 10 ? "0" : "") << tileMap[j + i * mapHeight] << ", ";
		}
		outputfile << std::endl;
	}

	outputfile.close();
}

void Map::Draw(sf::RenderWindow& rw)
{
	rw.draw(VerticeList, GetSprite().getTexture());
}