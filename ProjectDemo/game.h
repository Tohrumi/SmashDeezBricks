#pragma once

#include "pch.h"
#include "Paddle.h"
#include "Balls.h"
#include "Brick.h"

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
	Brick *bricks[20][20];

	void initWindow();
	void initVariables();
	void initStage();

public:
	// Constructor & Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Functions
	void pollEvents();
	void spawnBall();
	void updateBall();
	void renderBall();
	
	void spawnBrick();
	void updateBrick();
	void renderBrick();

	void update();
	void render();
};

