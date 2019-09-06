#include <iostream>
#include <stdio.h>
#include <cstdio>
#include "graphics.h"
#include "AmidarGame.h"
using namespace std;
using namespace amidar;

PaintBrush::PaintBrush()
{
	brush = NULL;
	brushsize = 32;
}

Point PaintBrush::getPosition()
{
	return position;
}

void* PaintBrush::loadBrush(char* filename)
{
	readimagefile(filename, position.x, position.y, position.x+brushsize, position.y+brushsize);
	
	int size = imagesize(position.x, position.y, position.x+brushsize, position.y+brushsize);//
	//void* ptr = new int;
	void* ptr = malloc(size);

	getimage(position.x, position.y, position.x+brushsize, position.y+brushsize, ptr);
	//putimage(0, 0, ptr, XOR_PUT);

	return ptr;
}

void PaintBrush::display(Point p)
{
	setPosition(p);

	if (brush == NULL)
	{
		brush = loadBrush("PaintBrush.gif");
	}

	//putimage(position.x, position.y, brush, XOR_PUT);
}

void PaintBrush::paint(Direction dir)
{
	putimage(position.x, position.y, brush, XOR_PUT);

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

	putpixel(position.x, position.y, color);
	putimage(position.x, position.y, brush, XOR_PUT);

	AmidarEvent* evt;
	evt = new AmidarEvent;
	evt->source = this;
	evt->type = PAINTEVENT;
	evt->dir = dir;
	evt->position = position;

	ael->handleAmidarEvent(evt);

}

void PaintBrush::setColor(int color)
{
	this->color = color;
	//setcolor(this->color);
}

void PaintBrush::setPosition(Point p)
{
	position.x = p.x;
	position.y = p.y;
}

void PaintBrush::addAmidarEventListener(AmidarEventListener* ael)
{
	this->ael = ael;
}