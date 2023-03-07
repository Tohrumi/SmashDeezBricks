#pragma once

#include "pch.h"
#include "Paddle.h"

using namespace sf;
using namespace std;

class Balls
{
private:
	// Variables
	CircleShape shape;
	float speed;
	Vector2f direction;
	int state;

	// Functions
	void initVariables(int state);
	void initShape();
	void initPos(Vector2f paddleBounds);

public:
	// Constructor & Destructor
	Balls(RectangleShape paddle, int state);
	virtual ~Balls();
	
	// Accessors
	int getState();

	// Functions
	void updateAttached(RectangleShape paddle);
	void launch();
	void checkBoundCollision(RenderTarget* target);
	void checkPaddleCollision(RectangleShape paddle);
	void update(Paddle* paddle, RenderTarget* target);
	void render(RenderTarget* target);
};

