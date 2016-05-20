#pragma once
#include "stdafx.h"
#include "GameObjectManager.h"

class Game {
public:
	static void Start();
	static sf::RenderWindow& GetWindow(); // Returns game window
	static GameObjectManager& GetObjectManager(); // Returns _gameObjectManager
	// Enter an object into the gameobjectmanager and set its position
	static void Initialize(std::string name, VisibleGameObject* obj, float x, float y);

	const static int SCREEN_HEIGHT = 870;
	const static int SCREEN_WIDTH = 800;

	static sf::Font regular;

	enum GameState {
		Uninitialized, Paused, Talking,
		ShowingWorld, Playing, Exiting, GameOver
	};

	static GameState _gameState; // Current GameState

	static int score;
	static int player;
	static int clicks;

private:
	static bool IsExiting(); // Checks if exit event has been called
	static void GameLoop(); // Main game function
	static void LoadFonts(); // Load font(s)

	static sf::RenderWindow _mainWindow; // main window. duh
	static GameObjectManager _gameObjectManager; // GameObjectManager of current tile
};