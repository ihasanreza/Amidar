#include "AmidarGame.h"
#include "graphics.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>

using namespace std;
using namespace amidar;

AmidarGame::AmidarGame(int w, int h, int x, int y)
{
	displayGameWindow(w, h);
	displayTitle();
	agp = new AmidarGameplay(w, h, x, y);
	gc = new GameController();

	gc->addAmidarEventListener(this);
	gc->takeUserInput();
}


AmidarGame::~AmidarGame(void)
{
}

void AmidarGame::displayGameWindow(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	initwindow(windowWidth, windowHeight, "Amidar");												//Amidar on Left Top
	setcolor(WHITE);
}

void AmidarGame::init()
{
	gc->addAmidarEventListener(agp);																//Points agp to GC's ael
	agp->startGame();																				//startGame() of AGP
}

void AmidarGame::displayTitle()
{
	int x,y;

	setcolor(YELLOW);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 8);
	outtextxy(getmaxx()/4+40, getmaxy()/4, "Amidar Game");														//displays Amidar Game

	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);

	rectangle(getmaxx()/4+40+100-10, getmaxy()/4+100-1, getmaxx()/4+40+100+145, getmaxy()/4+100+60);			//creates Rect
	outtextxy(getmaxx()/4+40+100, getmaxy()/4+100, "Play");														//displays Play in Rect

	rectangle(getmaxx()/4+40+400-10, getmaxy()/4+100-1, getmaxx()/4+40+400+145, getmaxy()/4+100+60);
	outtextxy(getmaxx()/4+40+400, getmaxy()/4+100, "Quit");

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
	//cleardevice();
}

void AmidarGame::handleAmidarEvent(AmidarEvent* evt)
{
	switch(evt->dir)
	{
		case ESC:
			closegraph();
			exit(0);

		case LMOUSECLICK:
			if (evt->position.x >= getmaxx()/4+40+100-10 && evt->position.x <= getmaxx()/4+40+100+145 && evt->position.y >= getmaxy()/4+100-1 && evt->position.y <= getmaxy()/4+100+60)
			{
				cleardevice();
				init();
			}

			if ( evt->position.x >= getmaxx()/4+40+400-10 && evt->position.x <= getmaxx()/4+40+400+145 && evt->position.y >= getmaxy()/4+100-1 && evt->position.y <= getmaxy()/4+100+60 )
			{
				closegraph();
				exit(0);
			}
			break;

		case ENTER:
			cleardevice();
			init();
			break;

	}

}



int main()
{
	AmidarGame ag(1366 , 768, 50, 50);
	
}




