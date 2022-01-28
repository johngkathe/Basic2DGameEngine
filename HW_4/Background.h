//This is the header for the Background
//This handles the background of the game
//John G. Kathe 10/23/20

#ifndef Background_h
#define Background_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class Background{

	public:
		Background();	//Constructor
		~Background();	//Deconstructor

		//Sets up the background
		void SetBackground(const char* pngFile, SDL_Renderer* Renderer);
		SDL_Texture* GetBackground();

	private:
		//A Texture that holds the background
		SDL_Texture* BackgroundTexture;

};

#endif
