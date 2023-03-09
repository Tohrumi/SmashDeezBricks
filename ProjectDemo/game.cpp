#include "pch.h"
#include "game.h"

// Private Functions
void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 840;
	this->window = new RenderWindow(this->videoMode, "Demo", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);

}
void Game::initVariables()
{
	this->paddle = nullptr;
	this->paddle = new Paddle(this->window);
}
void Game::initStage()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			this->bricks[i][j] = new Brick(Vector2f(20 + i * 40, 20 + j * 30), 1);
}

// Contructor & Destructor
Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initStage();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

// Functions

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnBall()
{
	if (this->balls.empty()) {
		Balls newBall = Balls(this->paddle->getShape(), 1);
		this->balls.push_back(newBall);
	}
}

void Game::renderBall()
{
	for (int i = 0; i < this->balls.size(); i++)
	{
		if (this->balls[i].getState() == 0)
			balls.erase(balls.begin() + i);
		else
			this->balls[i].render(this->window);
	}
}

void Game::updateBrick()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (this->bricks[i][j] == nullptr)
				continue;
			if (this->bricks[i][j]->getHitPoint() <= 0)
				this->bricks[i][j] = nullptr;
		}
	}
	
}

void Game::renderBrick()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if(this->bricks[i][j] != nullptr)
				this->bricks[i][j]->render(this->window);	
}

void Game::updateBall()
{
	bool isLaunched = 0;
	if (Keyboard::isKeyPressed(Keyboard::Space))
		isLaunched = 1;
	for (int i = 0; i < this->balls.size(); i++) 
	{	
		if (isLaunched)
			this->balls[i].launch();
		this->balls[i].update(this->paddle, this->bricks, this->window);
	}
}

void Game::update()
{
	this->spawnBall();
	this->pollEvents();
	this->paddle->update(this->window);
	this->updateBrick();
	this->updateBall(); 
}

void Game::render()	
{
	this->window->clear(Color::Black);

	// draw game objects
	this->paddle->render(this->window);
	this->renderBrick();
	this->renderBall();
	this->window->display();
}

