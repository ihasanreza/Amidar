#include <iostream>
#include <stdio.h>
#include <cstdio>
#include "graphics.h"
#include "AmidarGame.h"
using namespace std;
using namespace amidar;

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESC 27
#define KB_ENTER 13

void GameController::takeUserInput()
{
	keepRunning = true;
	AmidarEvent* evt;
	evt = new AmidarEvent;
	char KB_code = NULL;
	int hit = -1;																				//arbitraty value

	while(keepRunning)
	{
		//if(kbhit() || KB_code != NULL)
		//{
		delay(5);

		hit = kbhit();																			//saves returned value of kbhit() in hit

		if (hit && hit !=-1)																	//if value of hit is changed
		{
			KB_code = getch();																	//assigns pressed button to KB_code
			hit=0;
		}
			

			switch(KB_code)
			{
				case KB_UP:
					
					//evt = new AmidarEvent;
					evt->source = this;														//pointed to current case
					evt->dir = UP;
					evt->type = KEYEVENT;
					ael->handleAmidarEvent(evt); 
					break;
				

				case KB_DOWN:
				
					//evt = new AmidarEvent;
					evt->source = this;
					evt->dir = DOWN;
					evt->type = KEYEVENT;
					ael->handleAmidarEvent(evt);
					break;
				

				case KB_LEFT:
			
					//evt = new AmidarEvent;
					evt->source = this;
					evt->dir = LEFT;
					evt->type = KEYEVENT;
					ael->handleAmidarEvent(evt);
					break;
				

				case KB_RIGHT:
				
					//evt = new AmidarEvent;
					evt->source = this;
					evt->dir = RIGHT;
					evt->type = KEYEVENT;
					ael->handleAmidarEvent(evt);
					break;

				case KB_ESC:

					evt->source = this;
					evt->dir = ESC;
					evt->type = KEYEVENT;
					ael->handleAmidarEvent(evt);

				case KB_ENTER:

					evt->source = this;
					evt->dir = ENTER;
					evt->type = KEYEVENT;
					ael->handleAmidarEvent(evt);
				
			}

			if(ismouseclick(WM_LBUTTONDOWN))
			{
				getmouseclick(WM_LBUTTONDOWN, evt->position.x, evt->position.y);					//x, y of the point where the mouse is clicked 
				evt->type = MOUSEEVENT;
				evt->dir = LMOUSECLICK;
				ael->handleAmidarEvent(evt);
			}
		//}
	}
}

void GameController::addAmidarEventListener(AmidarEventListener* ael)
{
	this->ael = ael;																				//now points agp to base GC's ael
}