//This is the file where we substantiate all the elements of GameSkeleton
//John G. Kathe 10/23/20

#include "GameSkeleton.h"
#include "Character.h"
#include "Background.h"
#include "HUD.h"
#include "Particle.h"
#include "Collider.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <iostream>
#include <cmath>	//sqrt()
#include <cstdlib>	//abs()

#define SPRITE_SIZE 32
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224

//Sets up the texture of the player
SDL_Texture* PlayerTexture;

GameSkeleton::GameSkeleton(){}

GameSkeleton::~GameSkeleton(){}


//Sets up the class objects for the background, HUD, and player
Background *HW3Background = NULL;

HUD *GiselaAlphaHUD = NULL;
Character *Gisela = NULL;

Particle *Waterfall1 = NULL;
Particle *Waterfall2 = NULL;

Particle *TorchFlame1 = NULL;
Particle *TorchFlame2 = NULL;

Particle *FlameSpellcast = NULL;

Collider *Detector = NULL;
Collider *River = NULL;


//Here we handle SDL Initialization
void GameSkeleton::InitializeGameScreen(const char* GameTitle,
					int ScreenXPos,
					int ScreenYPos,
					int ScreenWidth,
					int ScreenHeight,
					bool FullScreenOption){


/*****FULL SCREEN DECLARATION*****/


	int FullScreenChoice = 0;	//Used to choose fullscreen based on
					//SDL_CreateWindow's UInt32 parameter

	//If we chose the FullScreenOption as true then we'll get a full screen
	if(FullScreenOption) FullScreenChoice = SDL_WINDOW_FULLSCREEN;

/*********************************/


/*****INITIALIZE KEY ELEMENTS*****/

	//Checks to see if SDL initializes and acts accordingly
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
		StateOfGame = false;	//False since game isn't running
	}
	else{
		std::cout << "SDL initilization successful!" << std::endl;

		//We create the game's screen
		GameScreen = SDL_CreateWindow(GameTitle,
					      ScreenXPos, ScreenYPos,
					      ScreenWidth, ScreenHeight,
					      FullScreenChoice);

		if(GameScreen) std::cout <<  "GameScreen created!" << std::endl;

		//We create the renderer
		GameRenderer = SDL_CreateRenderer(GameScreen, -1, 0);
		if(GameRenderer){ 
			std::cout << "GameRenderer created!" << std::endl;
			
			//This creates a black background as the default
			SDL_SetRenderDrawColor(GameRenderer, 0, 0, 0, 255);
		}

		//Enable GPU enhanced textures using PNGs for spritesheets
		IMG_Init(IMG_INIT_PNG);

		StateOfGame = true;
	}

/*********************************/
};

void GameSkeleton::InitializeObjects(){
	//We set the Detector collision detector
	Detector = new Collider();

	//We insert the background
	HW3Background = new Background();
	HW3Background->SetBackground("MapElements/HW4 Sample Frame.png", 
				     GameRenderer);


	//We insert the HUD
	GiselaAlphaHUD = new HUD();
	GiselaAlphaHUD->SetHUDIcon("Sprites/Interface Components1.png", 
				   GameRenderer);
	
	
	//Now we create Gisela and set her up
	Gisela = new Character(SCREEN_WIDTH, SCREEN_HEIGHT);
	Gisela->SetCharacterTexture("Sprites/Gisela Sprite Sheet Updated.png", 
				    GameRenderer);
	//We give Gisela a starting point on the screen
	Gisela->SetXYCoordinates(270, 380);
	
	//We set up the starting sprite
	Gisela->UpdateCharacter(0, 2, SPRITE_SIZE);

	//Now we add the first waterfall to the screen
	Waterfall1 = new Particle("FX/SpriteSheetWaterfall.png", GameRenderer,
				  120, true, true);
	Waterfall1->SetParticleCoordinates(0, 0, 440, -15, 96, 96, 0);

	//Now we add the second waterfall to the screen
	Waterfall2 = new Particle("FX/SpriteSheetWaterfall.png", GameRenderer,
				  120, true, true);
	Waterfall2->SetParticleCoordinates(0, 0, 440, 490, 96, 96, 69);

	//Now we add the Torch Flames
	TorchFlame1 = new Particle("FX/SpriteSheetTorchFlame.png", GameRenderer, 120, true, false);
	TorchFlame1->SetParticleCoordinates(0, 0, -130, 92, 96, 96, 0);
	TorchFlame1->AssignCollider(30, 448, 700);


	TorchFlame2 = new Particle("FX/SpriteSheetTorchFlame.png", GameRenderer,
				   120, true, true);
	TorchFlame2->SetParticleCoordinates(0, 0, 1020, 92, 96, 96, 69);

	FlameSpellcast = new Particle("FX/SpriteSheetFlameThrowerFull.png", GameRenderer, 120, false, false);
				

	//We make the river impassible
	River = new Collider();
	River->AssignWall(594, 0, 96, 892);
};

//This handles the steps of handles the visual elements of the character sprite.
void GameSkeleton::UpdateGame(){	
	TickCount++;
	SDL_Rect tempSrc = Gisela->GetSpriteData();
	Gisela->UpdateCharacter(tempSrc.x, tempSrc.y, SPRITE_SIZE);

//This section waits for Gisela to walk to an appropriate area to light tha lamp	
	Circle TorchCircle = TorchFlame1->GetCollisionCircle();
	SDL_Rect GiselaCollider = Gisela->GetCollisionRect();
	bool CollisionCheck = Detector->CollisionCheck(GiselaCollider,
                                                       TorchCircle);
	if(CollisionCheck) TorchFlame1->ActivateParticle();
};


//This renders the screen
void GameSkeleton::RenderScreen(){

/*****BEGIN RENDER*****/

	//Clean out the current info in the renderer
	SDL_RenderClear(GameRenderer);

/**********************/


/**RENDER  BACKGROUND**/

	//Use the Painter Algorithm to put all the things to be rendered onto
	//the screen background -> foreground
	
	//Here we will render the background
	SDL_RenderCopy(GameRenderer, HW3Background->GetBackground(), NULL, NULL);

/**********************/


/****BG PARTICLE FX****/

	//We add the Particle Effects
	Waterfall1->RenderParticle();
	Waterfall2->RenderParticle();
	
	TorchFlame1->RenderParticle();
	TorchFlame2->RenderParticle();

/**********************/


/***RENDER CHARACTER***/

	//Here we will render the player character Gisela	
	Gisela->RenderCharacter(SPRITE_SIZE);
	//FIXME:
	FlameSpellcast->RenderParticle();	//For no apparent reason the
	//The FlameSpellcast does not appear on the screen.  The Spellcast
	//function works perfectly in placing the particle effect and the 
	//RenderParticle function indicates that the animation is read from
	//the sprite sheet as intended.  Any help on how this doesn't work
	//would be appreciated

/**********************/


/******RENDER UI*******/

	//We add the HUD icon last because it goes over the rest of the screen as
	//an element of the UI
	SDL_RenderCopy(GameRenderer, GiselaAlphaHUD->GetHUDIcon(), NULL, NULL);


/*****FINAL RESULT*****/

	//Now we load in the new information to render
	SDL_RenderPresent(GameRenderer);

/**********************/

};


//Clean out the game loop
void GameSkeleton::CleanMemory(){
	//We power down everything in the game
	SDL_DestroyRenderer(GameRenderer);
	SDL_DestroyWindow(GameScreen);

	IMG_Quit;
	SDL_Quit;
};


//This handles our events, notably how the game handles player inputs
void GameSkeleton::EventHandling(){
	SDL_Event GameInput;
	SDL_PollEvent(&GameInput);

//Sets up the collision check for when Gisela walks near the rive, although
//this will be scalable to any collider
	SDL_Rect RiverCollider = River->GetWallRect();
	SDL_Rect GiselaCollider = Gisela->GetCollisionRect();
	bool CollisionCheck = Detector->CollisionCheck(RiverCollider,
						       GiselaCollider);

	//These handle the movement of the character
	int x = 0;
	int y = 0;
	int speed = 5;

	char Direction;
	
	//Used for diagonal movement.  Speed*2 is to make diagonal movement
	//feel more synonymous to horizontal and vertical movement.
	float c = sqrt(speed*2);

	switch(GameInput.type){
		//Allows us to quit the game my x'ing out
		case SDL_QUIT:
			StateOfGame = false;
			break;
		//Allosw us to move the character
		case SDL_KEYDOWN:
			switch(GameInput.key.keysym.sym){
				//Horizontal and Vertical Movement
				case SDLK_w: 				//UP
					Direction = Gisela->UpdateMovement(0,-speed,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
				case SDLK_a: 				//Left
					Direction = Gisela->UpdateMovement(-speed,0,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
				case SDLK_s: 				//Down
					Direction = Gisela->UpdateMovement(0,speed,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
				case SDLK_d: 				//Right
					Direction = Gisela->UpdateMovement(speed,0,CollisionCheck);	
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
			
				//Diagonal Movement
				case SDLK_q:				//Up-Left	
					x = -round(c);
					y = -round(c);
					Direction = Gisela->UpdateMovement(x,y,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
				case SDLK_e:				//Up-Right
					x = round(c);
					y = -round(c);
					Direction = Gisela->UpdateMovement(x,y,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
				case SDLK_z:				//Down-Left
					x = -round(c);
					y = round(c);
					Direction = Gisela->UpdateMovement(x,y,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;
				case SDLK_c:				//Down-Right
					x = round(c);
					y = round(c);
					Direction = Gisela->UpdateMovement(x,y,CollisionCheck);
					Direction = Gisela->SpriteUpdate(0,Direction,SPRITE_SIZE);
					break;


				//Spellcast Flamethrower
				case SDLK_f:
					//We use the UpdateMovement to give Spellcast a direction
					Direction = Gisela->UpdateMovement(0,0,CollisionCheck);
					FlameSpellcast->Spellcast(Direction, Gisela, 96, 96);
					//At initiation or after a spellcast the particle needs
					//to be activated
					FlameSpellcast->ActivateParticle();
					break;

				//Reset Gisela's location on the map			
				case SDLK_r: 
					Gisela->SetXYCoordinates(270, 380);
					break;
				
				//Close the game
				case SDLK_ESCAPE:
					StateOfGame = false;
					break;
			}
		case SDL_KEYUP:
			Gisela->UpdateMovement(0,0,CollisionCheck);			
		default:
			break;
	}
};


//This handles the game status
bool GameSkeleton::GameStatus(){
	return StateOfGame;
};





















