#pragma once

#include <vector>
#include <random>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Player.h"
#include "Road.h"
#include "Car.h"

class Game
{
	private:
		// Variables
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event event;

		// Add variables to control and show game status (level, lives)
		sf::Font font;
		sf::Text text;
		sf::Text highScoreText;
		sf::Text endGameText;

		// Add variables to control game end
		bool endGame;

		// Game objects (player, roads, cars)
		Player player;
		std::vector<Road> roads;
		std::vector<Car> cars;

		// Add a variable to keep track of the player's collision with cars
		int collision;

		// Add a variables to control road spawning
		float roadSpawnTimer;
		float roadSpawnTimerMax;
		int maxRoads;

		// Add variables to control car spawning
		float carSpawnTimer;
		float carSpawnTimerMax;
		int maxCars;

		// Initialization
		void initVariables();
		void initWindow();

	public:
		// Constructors and destructors
		Game();
		virtual ~Game();

		// Accessors
		const bool running() const;

		// Functions
		void pollEvents();
		void spawnRoad();
		void spawnCar();
		void updateCarHorizontalMovement();
		void updatePlayerCollision();
		void updateGameStatus();
		void updateHighScore();
		void updateEndGameText();
		void handleEndGame();
		void update();
		void renderGameStatus();
		void renderHighScore();
		void render();
};

