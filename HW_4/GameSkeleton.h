//This is the header for the Game class
//It is used by Main to run the essential functions of the game
//John G. Kathe 10/23/20

#ifndef GameSkeleton_h
#define GameSkeleton_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class GameSkeleton{

	public:
		GameSkeleton();		//Constructor
		~GameSkeleton();	//Deconstructor

		//This handles the initialization of the game to handle all of
		//The necessary components to get the game started and running.
		void InitializeGameScreen(const char* GameTitle, 
					  int ScreenXPos,	
		        	          int ScreenYPos,
			        	  int ScreenHeight,
			 		  int ScreenWidth,
			        	  bool FullScreenOption);

		void InitializeObjects();
		//Used to handle all functions that will change the game in the
		//next screen.
		void UpdateGame();
		
		//Takes in all pertinent info and renders the screen as needed.
		void RenderScreen();
		
		//Turns off all SDL functions being used to end the game and
		//Turn off the game window
		void CleanMemory();
	
		//This handles movement commands in the game	
		void EventHandling();

		//Returns the state of the game
		bool GameStatus();
	private:

		//Counts the number of ticks that have occurred in the game
		int TickCount;
		
		//True = game running.  False = game stops
		bool StateOfGame;
	
		//The Window that functions as the game screen
		SDL_Window* GameScreen;

		//Renders all pertinent game elements for the objects that need
		//to be rendered.
		SDL_Renderer* GameRenderer;

};

#endif
