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
	}
}

void Balls::checkBoundCollision(RenderTarget* target)
{
	Vector2f circlePos = this->shape.getPosition();
	Vector2u windowSize = target->getSize();
	float circleRad = this->shape.getRadius();
	// Collision with topBound
	if (circlePos.y < circleRad)
		this->direction.y *= -1;
	// Collision with LeftBound or RightBound
	if (circlePos.x < circleRad || circlePos.x > windowSize.x - circleRad)
		this->direction.x *= -1;
	// Deadball
	if (circlePos.y - windowSize.y > 50.f)
		this->state = 0;
}

void Balls::checkPaddleCollision(RectangleShape paddle)
{
	Vector2f circlePos = this->shape.getPosition();
	Vector2f paddlePos = paddle.getPosition();
	FloatRect ballBounds = this->shape.getGlobalBounds();
	FloatRect paddleBounds = paddle.getGlobalBounds();
	if (ballBounds.intersects(paddleBounds))
	{
		//this->direction.y *= -1;
		float dist = circlePos.x - paddlePos.x;
		float sgn = dist / abs(dist);
		float var1 = dist / paddleBounds.width;
		float var2 = this->direction.x / this->speed;
		float alpha = acos(var1) - asin(var1) - acos(var2);
		if (alpha == 0)
			this->direction.y *= -1;
		else
		{
			alpha = -sgn * M_PI_2 - alpha;
			cout << alpha * 180 / M_PI << endl;
			this->direction.x = cos(alpha) * sgn;
			this->direction.y = sin(alpha) * sgn;
			
		}
	}
}

void Balls::update(Paddle* paddle, RenderTarget* target)
{
	if (this->state == 1)
		updateAttached(paddle->getShape());
	else if (this->state == -1)
	{
		this->shape.move(this->speed * this->direction.x, this->speed * this->direction.y);
		this->checkBoundCollision(target);
		this->checkPaddleCollision(paddle->getShape());
	}
}

void Balls::render(RenderTarget* target)
{
	target->draw(this->shape);
}
