#pragma once
#include "stdafx.h"
#include "Button.h"

class TextureBar : public VisibleGameObject
{
public:
	TextureBar(std::string filename);
	~TextureBar();

	void Update(float deltaTime, sf::Event ev);
	void Draw(sf::RenderWindow& rw);

	Button LeftButton;
	Button RightButton;
	Button ExportButton;

	std::vector<Button*> TextureButtons;

	// ID of the tile to map tiles with
	int newTextureID;
	// Tracks if the left or right buttons have been pushed
	int offset;
	sf::Vector2i pressLocation; 
	bool pressed;
};