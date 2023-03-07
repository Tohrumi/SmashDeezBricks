#pragma once

#include "pch.h"

using namespace sf;

/*
	class for paddle
*/
class Paddle
{
private:
	RectangleShape shape;
	float movementSpeed;

	void initVariables();
	void initShape();
	void initPos(float x, float y);

public:
	// Constructor & Destructor
	Paddle(RenderTarget *target);
	virtual ~Paddle();

	// Accessors
	RectangleShape getShape();

	// Functions
	void checkBounds(RenderTarget* target);
	void updateInput(RenderTarget* target);
	void update(RenderTarget* target);
	void render(RenderTarget* target);
};