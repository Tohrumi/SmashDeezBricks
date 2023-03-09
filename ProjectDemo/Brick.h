#pragma once

#include "pch.h"

using namespace std;
using namespace sf;

class Brick
{
private:
	// Variables
	RectangleShape shape;
	int hitPoint;

	// Functions
	void initVar(int hitPoint);
	void initShape();
	void initPos(Vector2f pos);

public:
	// Constructor & Destructor
	Brick(Vector2f pos, int hitPoint);
	virtual ~Brick();

	//Accessors
	int getHitPoint();

	// Functions
	int checkBallCollision(CircleShape ball);
	void update();
	void render(RenderTarget* target);
};

