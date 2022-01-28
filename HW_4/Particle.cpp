//The is the file where we define the Particle.h functions
//This handles particles and structures in the game
//John G. Kathe 11/14/20

#include "Particle.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Collider.h"
#include "Character.h"

#include <iostream>

#define SCREEN_SIZE_MOD 4


//Constructor setting up the sprite sheet and its particulars
Particle::Particle(const char* pngFile, SDL_Renderer* Renderer, int numFrames,
		   bool Repeat, bool Active){
	
	SDL_Surface* TempParticleSurface = IMG_Load(pngFile);

	ParticleTexture = SDL_CreateTextureFromSurface(Renderer,
						       TempParticleSurface);

	SDL_FreeSurface(TempParticleSurface);

	ParticleRenderer = Renderer;

	ParticleRepeater = Repeat;

	Activated = Active;

	ParticleFrames = numFrames;

	CurrentFrame = 0;
};

//Deconstructor
Particle::~Particle(){
	delete this;
};

//Here we set up the coordinates for the particle effect.
void Particle::SetParticleCoordinates(int srcX, int srcY, int destX, int destY,
				      int ParticleSizeX, int ParticleSizeY,
				      int FrameNumber){

	RectSrc.w = ParticleSizeX;
	RectSrc.h = ParticleSizeY;
	RectSrc.x = srcX;
	RectSrc.y = srcY;

	RectDest.w = RectSrc.w * SCREEN_SIZE_MOD;
	RectDest.h = RectSrc.h * SCREEN_SIZE_MOD;
	RectDest.x = destX;
	RectDest.y = destY;

	CurrentFrame = FrameNumber;
};

//Here we create assign spellcast particle effect in front
//of the character.  It takes in the direction the character
//is facing as well for the spell to be appropriately placed. 
void Particle::Spellcast(char Direction, Character *Caster,
	       int ParticleSizeX, int ParticleSizeY){

std::cout << "Spellcast!: " << Direction << std::endl;


	SDL_Rect CasterDestRect = Caster->GetXYCoordinates();

	RectSrc.w = ParticleSizeX;
	RectSrc.h = ParticleSizeY;
	RectSrc.x = 0;

	RectDest.w = ParticleSizeX*SCREEN_SIZE_MOD;
	RectDest.h = ParticleSizeY*SCREEN_SIZE_MOD;

	if(Direction == 'U'){
		RectSrc.y = 0;
		RectDest.x = CasterDestRect.x;
		RectDest.y = CasterDestRect.y - ParticleSizeY +
			     (1/2)*CasterDestRect.h;
	}
	else if(Direction == 'L'){
		RectSrc.y = 1;
		RectDest.x = CasterDestRect.x - ParticleSizeX +
			     (1/2)*CasterDestRect.w;
		RectDest.y = CasterDestRect.y;
	}
	else if(Direction == 'D'){
		RectSrc.y = 2;
		RectDest.x = CasterDestRect.x;
		RectDest.y = CasterDestRect.y + (1/2)*CasterDestRect.h;
	}
	else if(Direction == 'R'){
		RectSrc.y = 3;
		RectDest.x = CasterDestRect.x + (1/2)*CasterDestRect.w;
		RectDest.y = CasterDestRect.y;
	}

	RectSrc.y *= RectSrc.w;

	RectDest.x = RectDest.x*SCREEN_SIZE_MOD;
	RectDest.y = RectDest.y*SCREEN_SIZE_MOD;

	std::cout << "(" << RectDest.x << "," << RectDest.y << ")" << std::endl;

	CurrentFrame = 0;

	CollisionRect.x = RectDest.x;
	CollisionRect.y = RectDest.y;
	CollisionRect.w = RectDest.w;
	CollisionRect.h = RectDest.h;
};

void Particle::DeactivateParticle(){
	Activated = false;
};

void Particle::ActivateParticle(){
	Activated = true;
};

void Particle::RenderParticle(){

	if(!Activated) return;

	if(CurrentFrame == ParticleFrames){
		if(ParticleRepeater) CurrentFrame = 0;
		else Activated = false; //Detetes a one time particle effect after use
	}

	RectSrc.x = CurrentFrame*RectSrc.w;

	SDL_RenderCopy(ParticleRenderer, ParticleTexture, &RectSrc, &RectDest);

	//With the contract that structures hold a -1 value for Particle Frames
	//Thsi guarantees the the CurrentFrame will only update for particles
	//with animations
	if(ParticleFrames >= 0) CurrentFrame += 1;
	else CurrentFrame = 0;
};

//Assigns a Rect Collider to the particle effect if desired
void Particle::AssignCollider(int colX, int colY, int colW, int colH){
	CollisionRect.x = colX;
	CollisionRect.y = colY;
	CollisionRect.w = colW;
	CollisionRect.h = colH;
};

//Assigns a circular collider to the particld effect if desired
void Particle::AssignCollider(int colX, int colY, int colRadius){
	CollisionCircle.x = colX;
	CollisionCircle.y = colY;
	CollisionCircle.radius = colRadius;
};

//Return CollisionCircle
Circle Particle::GetCollisionCircle(){
	return CollisionCircle;
};

//Return CollisionRect

SDL_Rect Particle::GetCollisionRect(){
	return CollisionRect;
};
