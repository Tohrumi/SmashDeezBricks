#include "pch.h"
#include "game.h"

// Private Functions
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Demo", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);

}
void Game::initVariables()
{
	this->paddle = nullptr;
	this->paddle = new Paddle(this->window);
}

// Contructor & Destructor
Game::Game()
{
	this->initWindow();
	this->initVariables();
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

void Game::updateBall()
{
	bool isLaunched = 0;
	if (Keyboard::isKeyPressed(Keyboard::Space))
		isLaunched = 1;
	for (int i = 0; i < this->balls.size(); i++) 
	{	
		if (isLaunched)
			this->balls[i].launch();
		this->balls[i].update(this->paddle, this->window);
	}
}

void Game::update()
{
	this->spawnBall();
	this->pollEvents();
	this->paddle->update(this->window);
	this->updateBall();
	
}

void Game::render()
{
	this->window->clear(Color::Black);

	// draw game objects
	this->paddle->render(this->window);
	this->renderBall();
	this->window->display();
}

