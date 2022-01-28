//This is the header for a character
//This handles the characters of the game
//John G. Kathe 10/23/20

//Will perform the movement and animation of characters


#ifndef Character_h

#define Character_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Collider.h"

class Character{

	public:
		//Constructor that takes in the character's bounds
		//Possibly could be used to limit the ranges of characters
		Character( int ScreenWidth, int ScreenHeight);
		~Character();	//Deconstructor

		//Instantiates the Character sprite and sets pertinent details
		void SetCharacterTexture(const char* pngFile, 
                                         SDL_Renderer* CharacterRenderer);

		//Gets the character's texture
		SDL_Texture* GetCharacterTexture();

		//We Create a way to modify the x and y positions of the character
		void SetXYCoordinates(int x, int y);

		//We create a way to return the RectDest 
		SDL_Rect GetXYCoordinates();

		//Here we handle the movements of the character as well as
		//determine its sprite
		void UpdateCharacter(int x, int y, int SpriteSize);

		//We use this to modify player movement
		char UpdateMovement(int x, int y, bool CollisionCheck);

		//This changes the sprite being used by changing RectSrc
		char SpriteUpdate(int x, char Direction, int SpriteSize);

		//This returns the source rectangle of the sprite
		SDL_Rect GetSpriteData();
		
		//Here we render the character specifically
		void RenderCharacter(int SpriteSize);

		//Getting  colliders for characters
		SDL_Rect GetCollisionRect();

//FIXME: Mana and HP functions, both visual and status wise will be
//inserted here.

	private:

		//The locations for the (x,y) coordinates of RectDest
		int PosX;
		int PosY;
		
		//These handle the character in regard to the screen's
		//width and height
		int ScreenWidth;
		int ScreenHeight;
		
		//These bools are set up to handle the walk animation
		bool CharacterMoved;		//True = moved, False = Didn't
		bool FootingBuffer;		//Right = True, Left = False
		bool MiddleStep;		//For in between left and right
		
		char CharacterDirection;
		
		//These Rects handle the sprite used and their location on
		//the screen
		SDL_Rect RectSrc, RectDest;
		
		//Handles the sprite sheet for the character
		SDL_Texture* CharacterTexture;

		//USed to handle the rendering of the character
		SDL_Renderer* CharacterRenderer;
	
		//Colliders
		SDL_Rect CollisionRect;
		
};

#endif
