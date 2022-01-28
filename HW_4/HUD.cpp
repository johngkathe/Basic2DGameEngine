//This is the file where we substantiate all the elements of Background
//John G. Kathe 10/23/20

//Will perform other functions according to the HUD class
//Soon will handle health, mana, and other functions when the next
//milestone uses that.

#include "HUD.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>



HUD::HUD(){}

HUD::~HUD(){}

//Instantiates the HUD icon of Gisela (the heroine)
void HUD::SetHUDIcon(const char* pngFile, SDL_Renderer* Renderer){
	SDL_Surface* TempHUDSurface = 
		IMG_Load(pngFile);

	HUDTexture = 
		SDL_CreateTextureFromSurface(Renderer, TempHUDSurface);

	SDL_FreeSurface(TempHUDSurface);
}

//Returns the HUD icon of Gisela
SDL_Texture* HUD::GetHUDIcon(){
	return HUDTexture;
}
