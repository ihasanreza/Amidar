#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
//#include <string>
#include "graphics.h"
#include "AmidarGame.h"
using namespace std;
using namespace amidar;


AmidarGameplay::AmidarGameplay(int w, int h, int x, int y)
{
	windowWidth = w-98;
	windowHeight = h-100;
	startX = x;																	//left top x,y
	startY = y;
	score = 0;																	//score initialized with zero
}

void AmidarGameplay::createPlayingField()
{
	displayScore();
	displayButtons();
	createActors();
	createRectangles();
}

void AmidarGameplay::createRectangles()
{
	
	int partw = windowWidth/4;								//width of rect
	int parth = windowHeight/4;								//height of rect

	int partArea = partw * parth;							//rect Area

	int totalArea = windowWidth * windowHeight;				//area of the playing field
	rectAreaCount = totalArea/partArea;						//total no. of rect

	rectAreas = new RectangleArea[rectAreaCount];			//points to the very first rect
	int offset = 0;

	Point p;
	p.x = startX;
	p.y = startY;
	
	/*int j = 0;

	(rectAreas+j++)->setRect(p, partw, parth);

	p.x+=partw;
	(rectAreas+j++)->setRect(p, partw, parth);
	
	p.x=0;
	p.y+=parth;
	(rectAreas+j++)->setRect(p, partw, parth);
	
	p.x+=partw;
	(rectAreas+j)->setRect(p, partw, parth);*/

	for (int i = 0; i < sqrt(static_cast<float>(rectAreaCount)); i++)						//from 0 to 3 in a row
	{
		p.x = startX;
		

		for (int j = 0; j < sqrt(static_cast<float>(rectAreaCount)); j++)
		{
			(rectAreas+offset++)->setRect(p, partw, parth);									//points to the very next rect one by one
			p.x+=partw;																		//adds width of rect to reach the next rect of the same row
		}

		p.y+=parth;																			//adds height of rect to reach the next col.

	}

	brush->addAmidarEventListener(this);
	
	for (int i = 0; i < rectAreaCount; i++)													//from 0 to 15
	{
		(rectAreas+i)->setFillColor(GREEN);
		(rectAreas+i)->displayRect(false);
		
	}

	Point temp;
	temp.x = startX;
	temp.y = startY;
	rectAreas->calcatePerimeter(temp);
}


void AmidarGameplay::startGame()
{
	createPlayingField();
}

void AmidarGameplay::createActors()
{
	Point p;

	p.x = startX;
	p.y = startY;
	brush = new PaintBrush;
	brush->setColor(BLUE);
	brush->display(p);

	enemyCount = 1;

	enemies = new Enemy[enemyCount];

	p.x = windowWidth+startX;
	p.y = windowHeight+startY;

	(enemies)->display(p);

	//p.x = startX + windowWidth;
	//p.y = startY;

	//(enemies+1)->display(p);
	
}

void AmidarGameplay::handleAmidarEvent(AmidarEvent* evt)
{
	pastKeyEvent.type = KEYEVENT;

	if (evt->type == KEYEVENT)
	{
		Point p = brush->getPosition();

		switch(evt->dir)
		{
			case UP:
				/*if (p.y < startY)
				{
					p.y = startY;
					brush->setPosition(p);
				}
				else if (p.y > windowHeight + startY)
				{
					p.y = windowHeight + startY;
					brush->setPosition(p);
				}
				else if (p.x < startX)
				{
					p.x = startX;
					brush->setPosition(p);
				}
				else if (p.x > windowWidth + startX)
				{
					p.x = windowWidth + startX;
					brush->setPosition(p);
				}*/

				p = checkLimit(p);
				brush->setPosition(p);

				if (isValidHorizontalMove(p.x))
				{
					brush->paint(UP);
					pastKeyEvent.dir = UP;
				}
				else
					brush->paint(pastKeyEvent.dir);
				break;
				
			case DOWN:
				/*if (p.y > windowHeight + startY)
				{
					p.y = windowHeight + startY;
					brush->setPosition(p);
				}
				else if (p.y < startY)
				{
					p.y = startY;
					brush->setPosition(p);
				}
				else if (p.x > windowWidth + startX)
				{
					p.x = windowWidth + startX;
					brush->setPosition(p);
				}
				else if (p.x < startX)
				{
					p.x = startX;
					brush->setPosition(p);
				}*/

				p = checkLimit(p);
				brush->setPosition(p);

				if (isValidHorizontalMove(p.x))
				{
					brush->paint(DOWN);
					pastKeyEvent.dir = DOWN;
				}
				else
					brush->paint(pastKeyEvent.dir);
				break;

			case LEFT:
				/*if (p.x < startX)
				{
					p.x = startX;
					brush->setPosition(p);
				}
				else if (p.x > windowWidth + startX)
				{
					p.x = windowWidth + startX;
					brush->setPosition(p);
				}
				else if (p.y < startY)
				{
					p.y = startY;
					brush->setPosition(p);
				}
				else if (p.y > windowHeight + startY)
				{
					p.y = windowHeight + startY;
					brush->setPosition(p);
				}*/

				p = checkLimit(p);
				brush->setPosition(p);

				if (isValidVerticalMove(p.y))
				{
					brush->paint(LEFT);
					pastKeyEvent.dir = LEFT;
				}
				else
					brush->paint(pastKeyEvent.dir);
				break;
			case RIGHT:
				/*if (p.x > windowWidth + startX)
				{
					p.x = windowWidth + startX;
					brush->setPosition(p);
				}
				else if (p.x < startX)
				{
					p.x = startX;
					brush->setPosition(p);
				}
				else if (p.y > windowHeight + startY)
				{
					p.y = windowHeight + startY;
					brush->setPosition(p);
				}
				else if (p.y < startY)
				{
					p.y = startY;
					brush->setPosition(p);
				}*/

				p = checkLimit(p);
				brush->setPosition(p);

				if (isValidVerticalMove(p.y))
				{
					brush->paint(RIGHT);
					pastKeyEvent.dir = RIGHT;
				}
				else
					brush->paint(pastKeyEvent.dir);
				break;

			case ESC:
				setcolor(RED);
				settextstyle(10, HORIZ_DIR, 4);
				outtextxy(300, 7, "Paused...press any key to continue");
				getch();
				setcolor(BLACK);
				outtextxy(300, 7, "Paused...press any key to continue");
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
				setcolor(YELLOW);
				break;

			
		}
	}//if evt->type == KEYEVENT

	if (evt->type == MOUSEEVENT)
	{
		switch (evt->dir)
		{
			case LMOUSECLICK:
				if (evt->position.x >= getmaxx()-364 && evt->position.x <=  getmaxx()-255 && evt->position.y >=1 && evt->position.y <= 45)
				{
					setcolor(RED);
					settextstyle(10, HORIZ_DIR, 4);
					outtextxy(300, 7, "Paused...press any key to continue");
					getch();
					setcolor(BLACK);
					outtextxy(300, 7, "Paused...press any key to continue");
					settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
					setcolor(YELLOW);
				
				}
			

				if (evt->position.x >= getmaxx()-155 && evt->position.x <= getmaxx()-47 && evt->position.y >= 1 && evt->position.y <= 45)
				{
					closegraph();
					exit(0);
				}
				break;
		}
	}
	//else if (evt->type == VERTEXEVENT)
	//{
		//floodfill(evt->position.x, evt->position.y, BLACK);
	//}
	if (evt->type == PAINTEVENT)
	{
		for (int i = 0; i < rectAreaCount; i++)
		{
			if ((rectAreas+i)->isVertex(evt->position))
			{
				if ((rectAreas+i)->calcatePerimeter(evt->position))
				{
					(rectAreas+i)->markPainted();
					calcScore((rectAreas+i)->getScore());
					displayScore();
				}
			}
			

		}
		
		for (int i = 0; i < enemyCount; i++)
		{
			Direction dir = calcDirection(evt->position, (enemies+i)->getPosition());
			Point p = checkLimit((enemies+i)->getPosition());
			(enemies+i)->setPosition(p);

			switch(dir)
			{
			case UP:
			case DOWN:
				if (isValidHorizontalMove(p.x))
				{
					(enemies+i)->move(dir);
					pastDirection[i] = dir;
				}
				else
					(enemies+i)->move(pastDirection[i]);
				break;
				
			case LEFT:
			case RIGHT:
				if (isValidVerticalMove(p.y))
				{
					(enemies+i)->move(dir);
					pastDirection[i] = dir;
				}
				else
					(enemies+i)->move(pastDirection[i]);
				break;
			}
			if (isHit(brush->getPosition(), (enemies+i)->getPosition()))
			{
				endScreen();
				closegraph();
				exit(0);
			}

		}
		
		
	}



}

bool AmidarGameplay::isValidHorizontalMove(int x)
{
	int count = sqrt(static_cast<float>(rectAreaCount));

	for(int i = 0; i < count; i++)
	{
		if (x == (rectAreas+i)->getPosition().x)
		{
			return true;
		}
	}

	if (x == ((rectAreas + count - 1)->getPosition().x) + ((rectAreas + count - 1)->getWidth()))
	{
		return true;
	}
	else
		return false;
}

bool AmidarGameplay::isValidVerticalMove(int y)
{
	int count = sqrt(static_cast<float>(sizeof(rectAreaCount)));

	for(int i = 0; i < rectAreaCount; i+=count)
	{
		if (y == (rectAreas+i)->getPosition().y)
		{
			return true;
		}
	}

	if (y == ((rectAreas + rectAreaCount - count)->getPosition().y) + ((rectAreas + rectAreaCount - count)->getHeight()))
	{
		return true;
	}
	else
		return false;
}

void AmidarGameplay::calcScore(int s)
{
	score+=s;																		
}

void AmidarGameplay::displayScore()
{
	char msg[20];
	string s = "Score : ";
	setcolor(YELLOW);
	string res = s + itoa(score, msg, 10);
	char msg2[20];
	strcpy(msg2, res.c_str());
	settextstyle(10, HORIZ_DIR, 4);
	outtextxy(50, 7, msg2);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

}

void AmidarGameplay::displayButtons()
{
	settextstyle(10, HORIZ_DIR, 4);

	rectangle(getmaxx()-364, 1, getmaxx()-255, 45);
	outtextxy(getmaxx()-357, 7, "Pause");

	rectangle(getmaxx()-155, 1, getmaxx()-47, 45);
	outtextxy(getmaxx()-140, 7, "Quit");

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
}

Point AmidarGameplay::checkLimit(Point p)
{
	if (p.y < startY)
	{
		p.y = startY;
	}
	else if (p.y > windowHeight + startY)
	{
		p.y = windowHeight + startY;
	}
	else if (p.x < startX)
	{
		p.x = startX;
	}
	else if (p.x > windowWidth + startX)
	{
		p.x = windowWidth + startX;
	}

	return p;
}

Direction AmidarGameplay::calcDirection(Point brushp, Point enemyp)
{
	srand(time(NULL));
	float slope;
	bool infinity = false;
	Direction dir ;

	if (brushp.x-enemyp.x != 0)
	{
		slope = ((static_cast<float>((brushp.y-enemyp.y))/(brushp.x-enemyp.x)));
	}
	else
	{
		slope = 500;
		infinity = true;
	}

	if (slope == 0 && brushp.x > enemyp.x)
	{
		dir = RIGHT;
		
	}
	else if (slope == 0 && brushp.x < enemyp.x)
	{
		dir = LEFT;
	}
	else if (infinity && brushp.y > enemyp.y)
	{
		dir = DOWN;
	}
	else if (infinity && brushp.y < enemyp.y)
	{
		dir = UP;
	}
	else if ((slope >= -1  && slope < 0) && brushp.x > enemyp.x)
	{
		//dir = RIGHT;
		dir = static_cast<Direction>(rand() % 4);
	}
	else if ((slope >= -1  && slope < 0) && brushp.x < enemyp.x)
	{
		//dir = LEFT;
		dir = static_cast<Direction>(rand() % 4);
	}
	else if (slope < -1 && brushp.y > enemyp.y)
	{
		dir = DOWN;
	}
	else if (slope < -1 && brushp.y < enemyp.y)
	{
		dir = UP;
	}
	else if ((slope > 0 && slope < 1) && brushp.x > enemyp.x)
	{
		dir = RIGHT;
	}
	else if ((slope > 0 && slope < 1) && brushp.x < enemyp.x)
	{
		dir = LEFT;
	}
	else if (slope >= 1 && brushp.y > enemyp.y)
	{
		dir = DOWN;
	}
	else if (slope >= 1 && brushp.y < enemyp.y)
	{
		dir = UP;
	}
	return dir;
}

bool AmidarGameplay::isHit(Point brushp, Point enemyp)
{
	if (brushp.x == enemyp.x && brushp.y == enemyp.y)
	{
		return true;
	}

	return false;
}

void AmidarGameplay::endScreen()
{
	cleardevice();
	setcolor(RED);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 8);
	outtextxy(windowWidth/2-200, windowHeight/2, "Game Over");
	delay(3000);
}


