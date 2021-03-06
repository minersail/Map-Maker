#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Map : public VisibleGameObject
{
public:

	/*
	filename is the string for location of texture file
	tile is the size of each tile, for this game we will use 16x16
	tiles is a vector of ints that will be used to correspond to the tiles
	e.g. [0, 0, 0, 0  // 0 is grass and 1 is road
		  0, 1, 1, 0] 
	width and height are the width and height of the map, in number of tiles
	*/
    Map(const std::string filename, sf::Vector2i tile, int* tiles, int width, int height);
	/*
	Constructor 2 provides a way to load a map integer list from a file instead of in the code
	*/
    Map(const std::string filename, sf::Vector2i tile, std::string mapname, int width, int height);
	~Map();

	virtual void Draw(sf::RenderWindow& rw);
	void Reload(int position, int newValue);
	void Export();

	void LoadMap(std::string filename, int width, int height);

private:
	// Contains a list of vertices that are reference points to 
	// draw squares of the map's texture on
	sf::VertexArray VerticeList;

	int* tileMap;
	int mapWidth;
	int mapHeight;
	sf::Vector2i tileSize;
};