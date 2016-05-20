#include "stdafx.h"
#include "Button.h"
#include "Game.h"

Button::Button(std::string filename, float width, float height)
{
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;

	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	currentState = Blank;
}

Button::Button(std::string filename, float width, float height, sf::IntRect subTexture)
{	
	Load(filename);
	assert(IsLoaded());
	texturefile = filename;
	
	_sprite.setTextureRect(subTexture);
	SetBoxSize(width, height);
	_sprite.setOrigin(GetTextureRect().width / 2, GetTextureRect().height / 2);

	currentState = Blank;
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& rw)
{
	rw.draw(_sprite);
	if (currentState == Message)
	{
		text.setPosition(GetPosition().x - 100, GetPosition().y - 25);
		rw.draw(text);
	}
}

void Button::Update(float deltaTime, sf::Event ev)
{
	sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
	sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);
	if (GetBoundingRect().contains(mouseCoords.x, mouseCoords.y))
	{
		SetActive(false);
	}
	else
	{
		SetActive(true);
	}
}

bool Button::Clicked(sf::Event ev)
{
	if (ev.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i mousePixels = sf::Mouse::getPosition(Game::GetWindow());
		sf::Vector2f mouseCoords = Game::GetWindow().mapPixelToCoords(mousePixels);
		if (GetBoundingRect().contains(mouseCoords.x, mouseCoords.y))
		{
			return true;
		}
	}
	return false;
}

void Button::SetActive(bool makeActive)
{
	if (makeActive)
		_sprite.setColor(sf::Color(255, 255, 255));
	else
		_sprite.setColor(sf::Color(128, 128, 128));
}