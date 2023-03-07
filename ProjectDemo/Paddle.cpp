#include "pch.h"
#include "Paddle.h"

// private function

void Paddle::initVariables()
{
	this->movementSpeed = 10.0f;
}

void Paddle::initShape()
{
	this->shape.setFillColor(Color::Red);
	this->shape.setSize(Vector2f(80.f, 10.f));
}

void Paddle::initPos(float x, float y)
{
	FloatRect paddleBounds = this->shape.getGlobalBounds();
	this->shape.setOrigin(paddleBounds.width / 2, -paddleBounds.height / 2);
	this->shape.setPosition(x, y);
}


// Constructor & Destructor
Paddle::Paddle(RenderTarget* target) 
{
	Vector2u winSize = target->getSize();
	this->initVariables();
	this->initShape();
	this->initPos((float)winSize.x / 2, (float)winSize.y * 9 / 10);
}

Paddle::~Paddle()
{

}

// Accessors

RectangleShape Paddle::getShape()
{
	return this->shape;
}

// public function
void Paddle::checkBounds(RenderTarget* target)
{
	Vector2f paddlePos = this->shape.getPosition();
	FloatRect paddleBounds = this->shape.getGlobalBounds();
	if (paddlePos.x < paddleBounds.width / 2)
	{
		this->shape.setPosition(paddleBounds.width / 2, paddlePos.y);
	}
	if (paddlePos.x + paddleBounds.width / 2 > target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - paddleBounds.width / 2, paddlePos.y);
	}
}

void Paddle::updateInput(RenderTarget* target)
{
	// Keyboard input
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	this->checkBounds(target);
}

void Paddle::update(RenderTarget* target)
{
	// Bound collision check
	this->updateInput(target);
}

void Paddle::render(RenderTarget* target)
{
	target->draw(this->shape);
}


