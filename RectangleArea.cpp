#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include "graphics.h"
#include "AmidarGame.h"
using namespace std;
using namespace amidar;

RectangleArea::RectangleArea()
{
	painted = false;
	prevVertex.x = -1;
	prevVertex.y = -1;
	setPerimeter();
	setScore();
}

RectangleArea::RectangleArea(Point p, int w, int h)
{
	leftTop.x = p.x;
	leftTop.y = p.y;
	height = h;
	width = w;
	setPerimeter();
	setVertices();
	painted = false;
	prevVertex.x = -1;
	prevVertex.y = -1;
	setPerimeter();
	setScore();
}

void RectangleArea::setRect(Point p, int w, int h)
{
	leftTop.x = p.x;
	leftTop.y = p.y;
	height = h;
	width = w;
	setPerimeter();
	setVertices();
	setScore();
}

RectangleArea::~RectangleArea(void)
{
}

void RectangleArea::displayRect(bool fill)
{
	setcolor(YELLOW);
	rectangle(vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y);
	if (fill)
	{
		setfillstyle(SOLID_FILL, fillColor);
		floodfill(leftTop.x+(vertices[2].x-vertices[0].x)/2, leftTop.y+(vertices[2].y-vertices[0].y)/2, BLUE);
	}
	char msg[10] = {""};
	itoa(score, msg, 10);
	outtextxy(leftTop.x+(vertices[2].x-vertices[0].x)/2-10, leftTop.y+(vertices[2].y-vertices[0].y)/2, msg);

}

int RectangleArea::getPerimeter()
{
	perimeter = 2*(width+height);
	return perimeter;
}

Point RectangleArea::getPosition()
{
	return leftTop;
}

int RectangleArea::getHeight()
{
	return height;
}

int RectangleArea::getWidth()
{
	return width;
}

bool RectangleArea::isVertex(Point position)
{
	bool ratVal = false;
	
	if ((!painted) && (position.x >= vertices[0].x-1 && position.x <= vertices[2].x+1 ) && (position.y >= vertices[0].y-1 && position.y <= vertices[2].y+1))
	{
		for (int i = 0; i < 4; i++)
		{
			if ((position.x == vertices[i].x) && (position.y == vertices[i].y))
			{
				ratVal = true;
			}
		}

		/*if(position.x == leftTop.x && position.y == leftTop.y)
		{
			return true;
		}
		else if (position.x == leftTop.x+width && position.y == leftTop.y)
		{
			return true;
		}
		else if (position.x == leftTop.x && position.y == leftTop.y+height)
		{
			return true;
		}
		else if(position.x == leftTop.x+width && position.y == leftTop.y+height)
		{
			return true;
		}
		else
			return false;*/
	}
	else
	{
		reset();
	}
	return ratVal;
}

void RectangleArea::addAmidarEventListener(AmidarEventListener* ael)
{
	this->ael = ael;
}

/*void RectangleArea::dispatchAmidarEvent(AmidarEvent* evt)
{
	AmidarEvent* dispevt;
	dispevt = new AmidarEvent;
	dispevt->source = this;
	dispevt->type = VERTEXEVENT;
	dispevt->dir = evt->dir;
	dispevt->position = evt->position;
	
	ael->handleAmidarEvent(dispevt);
}*/

void RectangleArea::setFillColor(int color)
{
	fillColor = color;
}

bool RectangleArea::calcatePerimeter(Point p)
{
	if (prevVertex.x == -1)
	{
		calcPerimeter = 0;
	}
	else
	{
		calcPerimeter+=sqrt(static_cast<float>((p.x-prevVertex.x)*(p.x-prevVertex.x)+(p.y-prevVertex.y)*(p.y-prevVertex.y)));
	}
	
	prevVertex = p;

	if (calcPerimeter == perimeter)
	{
		
		return true;
	}
	else
	{
		return false;
	}		
}

void RectangleArea::markPainted()
{
	painted = true;
	setfillstyle(SOLID_FILL, fillColor);
	//putpixel(leftTop.x+(vertices[2].x-vertices[0].x)/2, leftTop.y+(vertices[2].y-vertices[0].y)/2, YELLOW);
	setcolor(BLUE);
	rectangle(vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y); 
	floodfill(leftTop.x+(vertices[2].x-vertices[0].x)/2, leftTop.y+(vertices[2].y-vertices[0].y)/2, BLUE);
	setcolor(YELLOW);
}

void RectangleArea::setPerimeter()
{
	perimeter = 2*(width+height);
}

void RectangleArea::setVertices()
{
	Point temp;

	vertices[0] = leftTop;

	vertices[1].x = leftTop.x+width;
	vertices[1].y = leftTop.y;
	//vertices[1] = temp;

	vertices[2].x = leftTop.x+width;
	vertices[2].y = leftTop.y+height;
	//vertices[2].x = temp;

	vertices[3].x = leftTop.x;
	vertices[3].y = leftTop.y+height;
	//vertices[3] = temp;
}

void RectangleArea::reset()
{
	calcPerimeter = 0;
	prevVertex.x = -1;
	prevVertex.y = -1;
}

void RectangleArea::setScore()
{
	score = perimeter;
}

int RectangleArea::getScore()
{
	return score;
}
