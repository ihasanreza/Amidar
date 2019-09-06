#pragma once
namespace amidar
{

	struct Point
	{
		int x;
		int y;
	};

	enum Direction
	{UP, DOWN, LEFT, RIGHT, ESC, LMOUSECLICK, ENTER};

	enum EventType
	{KEYEVENT, PAINTEVENT, MOUSEEVENT};

	struct AmidarEvent
	{
		public:
			void* source;
			EventType type;														//Key, mouse, paint
			Direction dir;														//Up, Down, Left, Right, Enter, LMouse
			Point position;														//x, y
	};

	class AmidarEventListener													//base class
	{
		public:
			virtual void handleAmidarEvent(AmidarEvent* evt)=0;					//purevirtualfunc - Its object can't be created 
	};																			//Only its pointer can be created which can hold address of derived class' object
																			
	class RectangleArea
	{
		private:
			Point leftTop;
			int height;
			int width;
			int perimeter;
			int calcPerimeter;
			int fillColor;
			int score;
			Point prevVertex;																			//lastVertex
			bool painted;																				//if painted
			Point vertices[4];
			AmidarEventListener* ael;																	//base class' pointer
			void dispatchAmidarEvent(AmidarEvent*);
			void setPerimeter();
			void setVertices();
			

		public:
			RectangleArea(Point p, int w, int h);												
			RectangleArea();
			void setRect(Point p, int w, int h);
			~RectangleArea(void);
			void displayRect(bool);
			int getPerimeter();
			Point getPosition();
			int getHeight();
			int getWidth();
			bool isVertex(Point);
			void addAmidarEventListener(AmidarEventListener*);
			void setFillColor(int);
			bool calcatePerimeter(Point);
			void markPainted();
			void reset();																		//resets parameter to zero
			void setScore();
			int getScore();
			
	};

	class Enemy
	{
		private:
			int enemysize;
			Point position;
			void* character;
			void* loadCharacter(char*);
			AmidarEventListener* ael;

		public:
			Enemy();
			void display(Point);
			void move(Direction);
			Point getPosition();
			void setPosition(Point);
			void addAmidarEventListener(AmidarEventListener*);
	};

	class PaintBrush
	{
		private:
			int brushsize;
			Point position;
			void* brush;
			void* loadBrush(char*);
			int color;
			AmidarEventListener* ael;

		public:
			PaintBrush();
			void display(Point);
			void paint(Direction);
			void setColor(int);
			Point getPosition();
			void setPosition(Point);
			void addAmidarEventListener(AmidarEventListener*);
	};

	class AmidarGameplay :public AmidarEventListener
	{	
		private:
			int windowWidth;
			int windowHeight;
			int startX;
			int startY;
			int score;
			int rectAreaCount;
			int enemyCount;
			RectangleArea* rectAreas;
			PaintBrush* brush;
			Enemy* enemies;
			AmidarEvent pastKeyEvent;
			Direction pastDirection[1];
			void createRectangles();
			void createPlayingField();
			void createActors();
			bool isValidHorizontalMove(int);
			bool isValidVerticalMove(int);
			void calcScore(int);
			void displayScore();
			void displayButtons();
			Direction calcDirection(Point, Point);
			Point checkLimit(Point);
			bool isHit(Point, Point);
			void endScreen();


		public:
			AmidarGameplay(int, int, int, int);
			void startGame();
			void handleAmidarEvent(AmidarEvent*);
			
	};

	
	class GameController
	{
		private:
			bool keepRunning;
			AmidarEventListener* ael;

		public:
			void takeUserInput();
			void addAmidarEventListener(AmidarEventListener*);
	};

	class AmidarGame :public AmidarEventListener										//holds pointer of AGP and GC
	{
		private:
			int windowWidth;
			int windowHeight;
			AmidarGameplay* agp;
			GameController* gc;

		public:
			AmidarGame(int, int, int, int);
			~AmidarGame(void);
			void displayGameWindow(int, int);
			void init();																	
			void displayTitle();
			void handleAmidarEvent(AmidarEvent*);
	};

	


}
