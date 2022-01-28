//This is the file where we substantiate all the elements of Character
//John G. Kathe 10/23/20

//Will perform other functions according to the Character header

#include "Character.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Collider.h"

#define SCREEN_SIZE_MOD 4	//We use this to work with a larger screen while
				//keeping a 320x224 ratio


//Here we make a character object, setting the parameters for the character
Character::Character(int SCREEN_WIDTH, int SCREEN_HEIGHT){
	//These limit the bounds of the screen.
	ScreenWidth = SCREEN_WIDTH*SCREEN_SIZE_MOD;
	ScreenHeight = SCREEN_HEIGHT*SCREEN_SIZE_MOD;

	//Determine the (x,y) coordinates of character when they
	//are initialized on the screen.  It is set as a default of 0.
	PosX = 0;
	PosY = 0;	//These could be modified in a more detailed constructor

	//Set up all the bools as false as the default
	CharacterMoved = false;
	FootingBuffer = false;
	MiddleStep = false;
}


Character::~Character(){}

//Instantiates the character texture
void Character::SetCharacterTexture(const char* pngFile, SDL_Renderer* Renderer){
	//Here we set up the Texture for the sprite sheet
	SDL_Surface* TempCharacterSurface = 
		IMG_Load(pngFile);

	CharacterTexture = 
		SDL_CreateTextureFromSurface(Renderer, TempCharacterSurface);

	SDL_FreeSurface(TempCharacterSurface);

	//Sets up the renderer for the character to be used
	CharacterRenderer = Renderer;
}

//Returns the character texture
SDL_Texture* Character::GetCharacterTexture(){
	return CharacterTexture;
}

//Sets the (x,y) coordinates of the character manually
void Character::SetXYCoordinates(int x, int y){
	PosX = x;
	PosY = y;
}

//Returns the Destination Rectangle of the Sprite Texture
SDL_Rect Character::GetXYCoordinates(){
	return RectDest;
}

//Updates the details of the Source Rectangle
void Character::UpdateCharacter(int x, int y, int SpriteSize){
//FIXME: Should modify sprite size to have 2 dimensions
	RectSrc.w = SpriteSize;
	RectSrc.h = SpriteSize;
	RectSrc.x = x;
	RectSrc.y = y;

	RectDest.w = RectSrc.w * SCREEN_SIZE_MOD;
	RectDest.h = RectSrc.h * SCREEN_SIZE_MOD;
	RectDest.x = PosX;
	RectDest.y = PosY;

	CollisionRect.w = RectDest.w;
	CollisionRect.h = RectDest.h;
	CollisionRect.x = RectDest.x;
	CollisionRect.y = RectDest.y;
}

//Handles the movement of the characters across the screen and within the 
//bounds of the screen, which it determines
char Character::UpdateMovement(int x, int y, bool CollisionCheck){
	
	if(PosX > (PosX + x)) CharacterDirection = 'L';
	if(PosX < (PosX + x)) CharacterDirection = 'R';
	if(PosY > (PosY + y)) CharacterDirection = 'U';
	if(PosY < (PosY + y)) CharacterDirection = 'D';

	float Rebound = 2;

	if(!CollisionCheck){
		PosX += x;
		PosY += y;
	}
	else{
		PosX -= x * Rebound;
		PosY -= y * Rebound; 
	}
	CharacterMoved = true;


//FIXME: This monstrosity
	//To stop before passing over the edge of the screen
	if(PosX < -(3*RectSrc.w/4)) PosX = -(3*RectSrc.w/4);	//Left
	if(PosY < -(3*RectSrc.h/4)) PosY = -(3*RectSrc.h/4);	//Top
	if(PosX > ScreenWidth - 3*RectSrc.w) PosX = ScreenWidth - 3*RectSrc.w; //Right
	if(PosY > ScreenHeight - 4*RectSrc.h) PosY = ScreenHeight - 4*RectSrc.h; //Bottom
	return CharacterDirection;
};

//Updates the sprite being used from the sprite sheet.
char Character::SpriteUpdate(int x, char Direction, int SpriteSize){
	
	int yDirection;	

	if(Direction == 'U') yDirection = 0;
	else if(Direction == 'L') yDirection = 1;
	else if(Direction == 'D') yDirection = 2;
	else if(Direction == 'R') yDirection = 3;
	
	RectSrc.x = x*SpriteSize;
	RectSrc.y = yDirection*SpriteSize;

	return CharacterDirection;
};

//Gets the Source Rectangle
SDL_Rect Character::GetSpriteData(){
	return RectSrc;
}

//Renders the character in the context of how it walks
void Character::RenderCharacter(int SpriteSize){
	if(CharacterMoved){	//Checks for movement
		if(MiddleStep){	//Animates the point in betwen left and right
				//footsteps.
			SDL_RenderCopy(CharacterRenderer, CharacterTexture, &RectSrc, &RectDest);
			MiddleStep = false;	//Makes sure the next step is
						//left of right.
		}
		else{		//Left of right step
			if(FootingBuffer){	//Takes a Right Step
				RectSrc.x = 1 * SpriteSize;
				SDL_RenderCopy(CharacterRenderer, CharacterTexture, &RectSrc, &RectDest);
				RectSrc.x = 0;
				FootingBuffer = false;	//Enables the next steo
							//to be a left footstep/
			}
			else{	//Takes a left footstep.
				RectSrc.x = 2 * SpriteSize;
				SDL_RenderCopy(CharacterRenderer, CharacterTexture, &RectSrc, &RectDest);
				RectSrc.x = 0;
				FootingBuffer = true;	//Enables the next step
							//to be a right footstep
			}
			MiddleStep = true;	//Next step will be in between
		}
		CharacterMoved = false;	//A moving animation will need an input 
					//making this bool true
	}
	//The character doesn't move
	else SDL_RenderCopy(CharacterRenderer, CharacterTexture, &RectSrc, &RectDest);
	SDL_Delay(5);	//Used to help make footsteps slow down.  This will 
			//need to be modified to make it more natural.
}

//Return CollisionRect

SDL_Rect Character::GetCollisionRect(){
	return CollisionRect;
};
