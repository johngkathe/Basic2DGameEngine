//This is the file where we substantiate all the elements of Background
//John G. Kathe 10/23/20

#include "Background.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>



Background::Background(){}

Background::~Background(){}


//Here we set i[ a;; the details for the background
void Background::SetBackground(const char* pngFile, SDL_Renderer* Renderer){
	SDL_Surface* TempBackgroundSurface = 
		IMG_Load(pngFile);

	BackgroundTexture = 
		SDL_CreateTextureFromSurface(Renderer, TempBackgroundSurface);

	SDL_FreeSurface(TempBackgroundSurface);
}

//Returns the background
SDL_Texture* Background::GetBackground(){
	return BackgroundTexture;
}
