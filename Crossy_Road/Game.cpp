#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;

    this->endGame = false;
    this->collision = 0;

    this->roadSpawnTimerMax = 10.f;
    this->roadSpawnTimer = roadSpawnTimerMax;
    this->maxRoads = 3;

    this->carSpawnTimerMax = 20.f;
    this->carSpawnTimer = carSpawnTimerMax;
    this->maxCars = this->maxRoads * 5; // 5 cars per road

    // Load font
    if (!this->font.loadFromFile("Fonts/Summer Dream Sans DEMO .ttf"))
		std::cout << "ERROR::GAME::INITVARIABLES::Failed to load font!" << std::endl;

	// Initialize text
	this->text.setFont(this->font);
    this->text.setCharacterSize(16);
    this->text.setFillColor(sf::Color::Cyan);
    this->text.setString("Score: 0\nLives: 3");
    this->text.setPosition(sf::Vector2f(20.f, 20.f));

	// Initialize highest score text
	this->highScoreText.setFont(this->font);
    this->highScoreText.setCharacterSize(16);
    this->highScoreText.setFillColor(sf::Color::Cyan);
    this->highScoreText.setString("Highest Score: 0");
    this->highScoreText.setPosition(sf::Vector2f(550.f, 30.f));

	// Initialize end game text
	this->endGameText.setFont(this->font);
    this->endGameText.setCharacterSize(28);
    this->endGameText.setFillColor(sf::Color::White);
    this->endGameText.setString("Your Score: 0");
    this->endGameText.setPosition(sf::Vector2f(400.f, 400.f));
}

void Game::initWindow()
{
    this->videoMode.height = 800;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Crossy Road", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                else {
                    for (auto& road : this->roads) {
                        if (road.getShape().getGlobalBounds().top >= this->window->getSize().y) {
                            this->roads.erase(this->roads.begin());
                        }

                        if (this->event.key.code == sf::Keyboard::Up)
                            road.move(0.f, 10.f);
                        else if (this->event.key.code == sf::Keyboard::Down)
                            road.move(0.f, -10.f);
                    }

                    for (auto& car : this->cars) {
                        if (car.getShape().getGlobalBounds().top + car.getShape().getGlobalBounds().height >= this->window->getSize().y) {
                            this->cars.erase(this->cars.begin());
                        }

                        if (this->event.key.code == sf::Keyboard::Up)
                            car.move(0.f, 10.f);
                        else if (this->event.key.code == sf::Keyboard::Down)
                            car.move(0.f, -10.f);
                    }
                }
                break;
            default:
                break;
        }
    }
}

void Game::spawnRoad()
{
    // Timer
   if (this->roadSpawnTimer < this->roadSpawnTimerMax)
		this->roadSpawnTimer += 1.f;
   else
   {
       if (this->roads.size() < this->maxRoads)
       {
			this->roads.push_back(Road(*this->window, roads.size()));
			this->roadSpawnTimer = 0.f;
		}
	}
}

void Game::spawnCar()
{
    // Timer
	if (this->carSpawnTimer < this->carSpawnTimerMax)
		this->carSpawnTimer += 1.f;
    else
    {
        if (this->cars.size() < this->maxCars)
        {
            float y = static_cast<float>(
                this->roads.back().getShape().getGlobalBounds().top + this->roads.back().getShape().getGlobalBounds().height / 2
                );
            this->cars.push_back(Car(*this->window, cars.size(), y));
			this->carSpawnTimer = 0.f;
		}
	}
}

void Game::updateCarHorizontalMovement()
{
    // Update cars horizontal movement
    for (auto& car : this->cars) {
        car.move(-10.f, 0.f);
        if (car.getShape().getGlobalBounds().left + car.getShape().getGlobalBounds().width <= 0.f) {
			car.move(this->window->getSize().x + car.getShape().getGlobalBounds().width, 0.f);
		}
    }
}

void Game::updatePlayerCollision()
{
	// Update player collision
    for (auto& car : this->cars) {
        if (car.hasCollided(this->player.getShape())) {
			this->collision++;
            this->player.updatePlayerLives();

            if (this->collision >= 3) {
				this->endGame = true;
            }
            else {
                this->player.resetPlayerPosition();
			}
		}
	}
}

void Game::updateGameStatus()
{
    // Update game status
	std::stringstream ss;

	ss << "Score: " << this->player.getPlayerLevel() << "\nLives: " << 4 - this->player.getPlayerLives();

	this->text.setString(ss.str());

    std::cout << this->player.getPlayerLevel() << std::endl;
    std::cout << this->player.getPlayerLives() << std::endl;
}

void Game::updateHighScore()
{
	// Update highest score
	std::ifstream ifs("score.txt");
	std::string line;
	int highestScore = 0;
    while (std::getline(ifs, line)) {
		if (std::stoi(line) > highestScore)
			highestScore = std::stoi(line);
	}
	ifs.close();

	std::stringstream ss;

	ss << "Highest Score: " << highestScore;

	this->highScoreText.setString(ss.str());
}

void Game::updateEndGameText()
{
    // Update end game text
    std::stringstream ss;

    ss << "Your Score: " << this->player.getPlayerLevel();

    this->endGameText.setString(ss.str());
}

void Game::handleEndGame()
{
	// Handle end game
    if (this->endGame) {
		std::cout << "Game Over!" << std::endl;
		this->window->close();
        //this->window->clear();
        //this->window->draw(this->endGameText);


        // save score to file
        std::ofstream ofs("score.txt", std::ios::app);
        ofs << this->player.getPlayerLevel() << std::endl;
        ofs.close();
	}
}

void Game::update()
{
    this->pollEvents();

    // Spawn roads
    this->spawnRoad();

    // Spawn cars
    this->spawnCar();

    // Update cars horizontal movement
    this->updateCarHorizontalMovement();

    this->player.update(this->window);

    // Update game status
    this->updateGameStatus();

    // Update highest score
    this->updateHighScore();

    // Update player collision
    this->updatePlayerCollision();

    this->updateEndGameText();

    // Handle end game
    this->handleEndGame();
}

void Game::renderGameStatus()
{
    // Draw game status
	this->window->draw(this->text);
}

void Game::renderHighScore()
{
	// Draw highest score
	this->window->draw(this->highScoreText);
}

void Game::render()
{
    // Clear old frame
    this->window->clear();

    // Draw game objects (player, roads, and cars)
    for (auto& road : this->roads)
		road.render(this->window);

    for (auto& car : this->cars)
        car.render(this->window);

    this->player.render(this->window);

    // Draw game status
    this->renderGameStatus();

    // Draw highest score
    this->renderHighScore();

    // Render the game
    this->window->display();
}
