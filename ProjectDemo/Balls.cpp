#include "pch.h"
#include "Balls.h"

// private function

void Balls::initVariables(int state)
{
	this->speed = 5;
	this->direction = Vector2f(0.f, 0.f);
	this->state = state;
}

void Balls::initShape()
{
	this->shape.setFillColor(Color::White);
	this->shape.setRadius(5.0f);
	this->shape.setOutlineThickness(1);
}

void Balls::initPos(Vector2f paddlePos)
{
	float radius = this->shape.getRadius();
	this->shape.setOrigin(radius, radius);
	this->shape.setPosition(paddlePos);
}

// Constructor & Destructor

Balls::Balls(RectangleShape paddle, int state)
{
	// state: 
	// 1: attached to paddle
	// 0: dead
	// -1: detached from paddle
	// 2: collided
	this->initVariables(state);
	this->initShape();
	this->initPos(paddle.getPosition());
}

Balls::~Balls()
{

}

// Accessors

int Balls::getState()
{
	return this->state;
}

CircleShape Balls::getShape()
{
	return this->shape;
}

// public functions

void Balls::updateAttached(RectangleShape paddle)
{
	this->shape.setPosition(paddle.getPosition());
}

void Balls::launch()
{
	if (this->state == 1) 
	{
		this->direction.y = -1.f;
		this->state = -1;
		this->shape.move(this->speed * this->direction.x, this->speed * this->direction.y);
	}
}

void Balls::checkBoundCollision(RenderTarget* target)
{
	Vector2f circlePos = this->shape.getPosition();
	Vector2u windowSize = target->getSize();
	float circleRad = this->shape.getRadius();
	// Collision with topBound
	if (circlePos.y < circleRad)
	{
		this->direction.y *= -1;
	}
	// Collision with LeftBound or RightBound
	if (circlePos.x < circleRad || circlePos.x > windowSize.x - circleRad)
	{
		this->direction.x *= -1;
	}

	// Deadball
	if (circlePos.y - windowSize.y > 50.f)
		this->state = 0;
}

void Balls::checkPaddleCollision(RectangleShape paddle)
{
	Vector2f ballPos = this->shape.getPosition();
	Vector2f paddlePos = paddle.getPosition();
	FloatRect ballBounds = this->shape.getGlobalBounds();
	FloatRect paddleBounds = paddle.getGlobalBounds();
	if (ballBounds.intersects(paddleBounds) && this->state == -1)
	{
		float dist = 2 * (ballPos.x - paddlePos.x) / paddleBounds.width;
		float a = M_PI / 3;
		float b = -M_PI_2;
		float alpha = a * dist + b;
		this->direction.x = cos(alpha);
		this->direction.y = sin(alpha);
	}
}

void Balls::checkBrickCollision(Brick *bricks[20][20])
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (bricks[i][j] == nullptr)
				continue;
			switch (bricks[i][j]->checkBallCollision(this->shape)) 
			{
			// Vertical Collision
			case -1:
				if (state != 2)
				{
					this->direction.y *= -1;
					this->state = 2;
				}
				
				break;
			// Horizontal Collision
			case 1:
				if (state != 2)
				{
					this->direction.x *= -1;
					this->state = 2;
				}
				break;
			// Corner Cases
			case 2:
				if (state != 2)
				{
					this->direction.x *= -1;
					this->direction.y *= -1;
					this->state = 2;
				}
				break;
			}
		}
	}
}

void Balls::update(Paddle* paddle, Brick *bricks[20][20], RenderTarget* target)
{
	if (this->state == 1)
		updateAttached(paddle->getShape());
	else
	{	
		this->state = -1;
		this->checkBoundCollision(target);
		this->checkPaddleCollision(paddle->getShape());
		this->checkBrickCollision(bricks);
		this->shape.move(this->speed * this->direction.x, this->speed * this->direction.y);
	}


}

void Balls::render(RenderTarget* target)
{
	target->draw(this->shape);
}
