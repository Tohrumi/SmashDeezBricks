#include "pch.h"
#include "Brick.h"

// Private Functions

void Brick::initVar(int hitPoint)
{
	this->hitPoint = hitPoint;
}

void Brick::initShape()
{
	this->shape.setSize(Vector2f(40.f, 30.f));
	this->shape.setFillColor(Color::Blue);
	this->shape.setOutlineColor(Color::Color(236, 240, 241, 255));
	this->shape.setOutlineThickness(1);
}

void Brick::initPos(Vector2f pos)
{
	this->shape.setPosition(pos);
}

// Constructor & Destructor

Brick::Brick(Vector2f pos, int hitPoint)
{
	initVar(hitPoint);
	initShape();
	initPos(pos);
}

Brick::~Brick()
{

}

int Brick::getHitPoint()
{
	return this->hitPoint;
}

// Functions

int Brick::checkBallCollision(CircleShape ball)
{
	FloatRect brickBounds = this->shape.getGlobalBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	Vector2f ballCent = ball.getPosition();
	float ballRad = ball.getRadius();
	if (brickBounds.intersects(ballBounds))
	{
		//If the ball hit the top/bottom of the brick (vertical collision)
		if (brickBounds.contains(ballCent.x, ballBounds.top) || brickBounds.contains(ballCent.x, ballBounds.top + ballBounds.height))
		{
			this->hitPoint--;
			return -1;
		}

		//If the ball hit the left/right side of the brick (horizontal collision)
		else if (brickBounds.contains(ballBounds.left, ballCent.y) || brickBounds.contains(ballBounds.left + ballBounds.width, ballCent.y))
		{
			this->hitPoint--;
			return 1;
		}

		//Edge collision
		else 
		{
			//Top left edge
			if (pow(ballCent.x - brickBounds.left, 2) + pow(ballCent.y - brickBounds.top, 2) < pow(ballRad, 2) - 50.f)
			{
				this->hitPoint--;
				return 2;
			}

			//Top right edge
			if (pow(ballCent.x - (brickBounds.left + brickBounds.width), 2) + pow(ballCent.y - brickBounds.top, 2) < pow(ballRad, 2) - 50.f)
			{
				this->hitPoint--;
				return 2;
			}

			//Botom left edge
			if (pow(ballCent.x - brickBounds.left, 2) + pow(ballCent.y - (brickBounds.top + brickBounds.height), 2) < pow(ballRad, 2) - 50.f)
			{
				this->hitPoint--;
				return 2;
			}

			//Bottom right edge
			if (pow(ballCent.x - (brickBounds.left + brickBounds.width), 2) + pow(ballCent.y - (brickBounds.top + brickBounds.height), 2) < pow(ballRad, 2) - 50.f)
			{
				this->hitPoint--;
				return 2;
			}
		}
	}
}

void Brick::update()
{
	
}

void Brick::render(RenderTarget* target)
{
	target->draw(this->shape);
}
