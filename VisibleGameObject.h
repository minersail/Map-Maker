#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Load(std::string filename, bool tiled);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float deltaTime, sf::Event ev);

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(sf::Vector2f newPos);
	virtual void SetRotation(float angle);
	//Returns a vector containing x and y values of the sprite's center
	virtual sf::Vector2f GetPosition() const;
	virtual float GetRotation(bool useDegrees = true) const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual float GetDistance(VisibleGameObject other);

	// -------THREE DIFFERENT METHODS TO GET DIFFERENT RECTANGLES-------
	// #1 -- Returns an axis-aligned rectangle that contains the sprite including transformations -- mainly used in simple collision detection 
	virtual sf::Rect<float> GetBoundingRect() const;
	// #2 -- Returns the dimensions of the current sprite -- Used for setting origins and other calculations involving offsets
	virtual sf::Rect<float> GetSpriteRect() const;
	// #3 -- Returns the rectangle of the entire texture -- mainly used in sprite sheets
	virtual sf::Rect<int> GetTextureRect() const;

	virtual bool IsLoaded() const;
	bool pendingDestruction;
	float frameCount;
	
	//Name of the file used to load the texture
	std::string texturefile;
	//String name of the object, used to retrieve the object from the object manager
	std::string name;
	sf::Sprite& GetSprite();

protected:
	sf::Sprite  _sprite;

private:
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};
