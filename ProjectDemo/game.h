#pragma once

#include "pch.h"
#include "Paddle.h"
#include "Balls.h"

using namespace sf;
using namespace std;

/*
	Class for Game Engine
*/

class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	Paddle* paddle;
	vector<Balls> balls;

	void initWindow();
	void initVariables();

public:
	// Constructor & Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Functions
	void pollEvents();
	void spawnBall();
	void renderBall();
	void updateBall();
	void update();
	void render();
};

