#include <cstdio>
#include <iostream>
#include "graphics.h"
#include "AmidarGame.h"
using namespace std;
using namespace amidar;

Enemy::Enemy()
{
	character = NULL;
	enemysize = 32;
}

Point Enemy::getPosition()
{
	return position;
}

void* Enemy::loadCharacter(char* filename)
{
	readimagefile(filename, position.x, position.y, position.x+enemysize, position.y+enemysize);
	
	//void* ptr = new int;
	int size = imagesize(position.x, position.y, position.x+enemysize, position.y+enemysize);//
	void* ptr = malloc(size);


	getimage(position.x, position.y, position.x+enemysize, position.y+enemysize, ptr);
	
	return ptr;
}

void Enemy::display(Point p)
{
	setPosition(p);

	if (character == NULL)
	{
		character = loadCharacter("Enemy.gif");
	}
}

void Enemy::move(Direction dir)
{
	putimage(position.x, position.y, character, XOR_PUT);

	switch(dir)
	{
		case UP:
			position.y--; break;
		case DOWN:
			position.y++; break;
		case LEFT:
			position.x--; break;
		case RIGHT:
			position.x++; break;
	}

	putimage(position.x, position.y, character, XOR_PUT);

}

void Enemy::setPosition(Point p)
{
	position.x = p.x;
	position.y = p.y;
}

void Enemy::addAmidarEventListener(AmidarEventListener* ael)
{
	this->ael = ael;
}
