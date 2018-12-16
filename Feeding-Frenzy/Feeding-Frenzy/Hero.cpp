#include "Hero.h"

const float PI = acos(-1);

Hero::Hero(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture) :Fish(xPos, yPos, zPos, m_Xscale, m_Yscale, m_Zscale, m_speed, type, object, texture)
{
	score = 0;
	playerCamera.SetPerspectiveProjection(45.0f, 1024.0f / 720.0f, 0.1f, 10000.0f);
	playerCamera.Strafe(xPos);
	playerCamera.Fly(yPos);
	playerCamera.Walk(-2000.0f);
	currentXPos = nextXPos = xPos;
	currentYPos = nextYPos = yPos;
}

void Hero::Eat()
{
	score++;
	if (score <= 10 && score % 5 == 0) {
		type++;
		scale(2.0f, 2.0f, 2.0f);
	}
}

void Hero::move(float valx, float valy, float valz)
{
	playerCamera.Strafe(valx);
	playerCamera.Fly(valy);
	m_translationMatrix = glm::translate(m_translationMatrix, glm::vec3(valx, valy, valz));
}

void Hero::GoTo(float newNextXPos, float newNextYPos)
{
	nextXPos = newNextXPos;
	nextYPos = newNextYPos;
}

void Hero::getGoing()
{
	if (fabs(nextXPos - currentXPos) < 10.0f)
		return;
	glm::vec2 mouth = GetMouth();
	float slope = (nextYPos - currentYPos) / (nextXPos - currentXPos), oldx = currentXPos, oldy = currentYPos;
	if (currentXPos < nextXPos)
	{
		currentXPos += m_speed;
		mouth.x += m_speed;
	}
	else
	{
		currentXPos -= m_speed;
		mouth.x -= m_speed;
	}
	currentYPos = nextYPos - slope * (nextXPos - currentXPos);
	mouth.y = nextYPos - slope * (nextXPos - mouth.x);
	if (mouth.x >= 1024.0f || mouth.x <= -1024.0f || mouth.y >= 720.0f || mouth.y <= -720.0f)
	{
		currentXPos = oldx;
		currentYPos = oldy;
		return;
	}
	move(currentXPos - oldx, currentYPos - oldy, 0.0f);
	getRotations();
}

void Hero::getRotations()
{
	float currentRotation = (atan2(nextYPos - currentYPos, nextXPos - currentXPos) * 180.0f) / PI;
	if (fabs(currentRotation) > 90)
	{
		ResetRotation();
		rotate(180.0f, 0.0f, 1.0f, 0.0f);
		if (currentRotation > 0)
			rotate(180.0f - currentRotation, 0.0f, 0.0f, 1.0f);
		else
			rotate(fabs(currentRotation) - 180.0f, 0.0f, 0.0f, 1.0f);
	}
	if (fabs(currentRotation) < 90)
	{
		ResetRotation();
		rotate(currentRotation, 0.0f, 0.0f, 1.0f);
	}
}

Hero::~Hero()
{
}
