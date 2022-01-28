//This is the header for the HUD
//This handles the HUD of the game
//John G. Kathe 10/23/20

//Currently identical to Background.h, but in the future will hold all
//of the details pertaining to the HUD (HP, Mana, etc.)


#ifndef HUD_h
#define HUD_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class HUD{

	public:
		HUD();	//Constructor
		~HUD();	//Deconstructor


		//Here we have setters and getters for the HUD icon
		//That is, the image in the top left picturing the
		//protagonist Gisela.
		void SetHUDIcon(const char* pngFile, SDL_Renderer* Renderer);
		SDL_Texture* GetHUDIcon();

//FIXME: Mana and HP functions, both visual and status wise will be
//inserted here.

	private:
		//A Texture that holds the main HUD image
		SDL_Texture* HUDTexture;

};

#endif
