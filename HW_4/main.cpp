//John G. Kathe


#include <SDL2/SDL.h>	//We use SDL2 Library
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "GameSkeleton.h"
#include "HUD.h"
#include "Background.h"
#include "Character.h"

//We use the screen dimensions of a Sega Genesis
#define SCREEN_WIDTH 	320
#define SCREEN_HEIGHT	224
#define SCREEN_SIZE_MOD 4	//We use this to keep the aforementioned ratio
				//While making it bigger for the user to see.

//We set sprite size as 16 because this is a 16 bit game
#define SPRITE_SIZE	32

//We determine the frame rate
const int FPS = 90;
const int FrameDelay = (1000/FPS) + 1;

Uint32 BeginningOfFrame;
int FrameDuration;


//We set up window details
SDL_Window* GameScreen = NULL;
SDL_Renderer* GameRenderer = NULL;
SDL_Event GameInput;


//We set up the GameSkeleton for the loop

GameSkeleton *GameLoop = NULL;

int main(void){

	//We start by creating a GameSkeleton object 
	GameLoop = new GameSkeleton();

	//Now we initialize it
	GameLoop->GameSkeleton::InitializeGameScreen("HW_4 Game Prototype",
				       	SDL_WINDOWPOS_CENTERED,
			    	        SDL_WINDOWPOS_CENTERED,
				   	(SCREEN_WIDTH*SCREEN_SIZE_MOD),
				 	(SCREEN_HEIGHT*SCREEN_SIZE_MOD),
				    	false);

	GameLoop->GameSkeleton::InitializeObjects();

	//GameStatus() is true so we keep the game going until it
	//becomes false
	while(GameLoop->GameStatus()){

		//Before we edit the frame we handle the FPS
		BeginningOfFrame = SDL_GetTicks();

		//Here we update the game for the next frame
		GameLoop->EventHandling();
		GameLoop->UpdateGame();
		GameLoop->RenderScreen();

		//Gets the duration of the frame
		FrameDuration = SDL_GetTicks() - BeginningOfFrame;

		//Now we delay the render update if need be
		if(FrameDuration < FrameDelay) SDL_Delay(FrameDelay - FrameDuration);
	}


	//Now we power down everything in the game
	GameLoop->CleanMemory();


	return 0;
}


