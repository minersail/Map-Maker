#include "stdafx.h"
#include "TextureBar.h"
#include "Game.h"
#include "Map.h"

TextureBar::TextureBar(std::string filename, std::string tilesetname, int mapW, int mapH)
	: LeftButton("images/leftbutton.png", 25, 64), RightButton("images/rightbutton.png", 25, 64),
	ExportButton("images/exportbutton.png", 40, 64)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	for (int i = 0; i < 9; i++)
	{
		Button* Tile = new Button(tilesetname, 64, 64, sf::IntRect(i * 16, 0, 16, 16));
		Tile->SetPosition((i + 1) * 74, 835);
		TextureButtons.push_back(Tile);
	}

	LeftButton.SetPosition(20, 835);
	RightButton.SetPosition(723, 835);
	ExportButton.SetPosition(770, 835);

	newTextureID = 0;
	offset = 0;
	pressed = false;
	mapWidth = mapW;
	mapHeight = mapH;
}

TextureBar::~TextureBar()
{
}

void TextureBar::Update(float deltaTime, sf::Event ev)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(Game::GetWindow());
	if (ev.type == sf::Event::MouseButtonPressed && mousePos.x <= 16 * mapHeight && mousePos.x >= 0 &&
		mousePos.y <= 16 * mapHeight && mousePos.y >= 0) // Mouse was initially pressed in map box
	{
		pressed = true;
		pressLocation = mousePos;
	}
	else if (ev.type == sf::Event::MouseButtonReleased && mousePos.x <= 16 * mapWidth && mousePos.x >= 0 && 
			 mousePos.y <= 16 * mapHeight && mousePos.y >= 0 && pressed)
	{   // Mouse was released in map box
		int tileX = mousePos.x / 16;
		int tileY = mousePos.y / 16;
		Map* map = dynamic_cast<Map*>(Game::GetObjectManager().Get("Map"));

		int leftX = std::min(tileX, pressLocation.x / 16); // Since the iterators only go forwards
		int rightX = std::max(tileX, pressLocation.x / 16); // Set a left and a right and top and bottom
		int topY = std::min(tileY, pressLocation.y / 16);
		int bottomY = std::max(tileY, pressLocation.y / 16);

		for (int i = leftX; i <= rightX; i++)
		{
			for (int j = topY; j <= bottomY; j++)
			{
				map->Reload(i + j * mapHeight, newTextureID);
			}
		}
		pressed = false;
	}
	else if (LeftButton.Clicked(ev))
	{
		if (offset != 0)
		{
			offset -= 1;
		}
		for (int i = 0; i < 9; i++)
		{
			sf::IntRect newRect(((i + offset) % 10) * 16, ((i + offset) / 10) * 16, 16, 16);
			TextureButtons[i]->GetSprite().setTextureRect(newRect);
		}
	}
	else if (RightButton.Clicked(ev))
	{
		if (offset != 35) // CHANGE IF MORE TILES ARE ADDED
		{
			offset += 1;
		}
		for (int i = 0; i < 9; i++)
		{
			sf::IntRect newRect(((i + offset) % 10) * 16, ((i + offset) / 10) * 16, 16, 16);
			TextureButtons[i]->GetSprite().setTextureRect(newRect);
		}
	}
	else if (ExportButton.Clicked(ev))
	{
		Map* map = dynamic_cast<Map*>(Game::GetObjectManager().Get("Map"));
		map->Export();
	}
	else // The elses are not really necessary because the buttons do not overlap, 
	{    // but they make the program have to make less if checks
		for (int i = 0; i < 9; i++)
		{
			if (TextureButtons[i]->Clicked(ev))
			{
				newTextureID = i + offset;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		TextureButtons[i]->Update(deltaTime, ev);
	}
}

void TextureBar::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	LeftButton.Draw(rw);
	RightButton.Draw(rw);
	ExportButton.Draw(rw);

	for (int i = 0; i < 9; i++)
	{
		TextureButtons[i]->Draw(rw);
	}

	if (pressed)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(rw);

		if (mousePos.x <= mapWidth * 16 && mousePos.x >= 0 &&
			mousePos.y <= mapHeight * 16 && mousePos.y >= 0)
		{
			sf::RectangleShape outline(sf::Vector2f(sf::Mouse::getPosition(rw).x - pressLocation.x,
				sf::Mouse::getPosition(rw).y - pressLocation.y));
			outline.setPosition(pressLocation.x, pressLocation.y);
			outline.setOutlineColor(sf::Color::Blue);
			outline.setOutlineThickness(3);
			outline.setFillColor(sf::Color(255, 255, 255, 0));
			rw.draw(outline);
		}
		else
		{
			pressed = false;
		}
	}
}