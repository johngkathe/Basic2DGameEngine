//This is the header for a particle effect
//This handles the particles of the game
//John G. Kathe 11/13/20

//Will perform the animation, initiation, and deactivation of particles
//Has a shared function for static structures that are to be places over the 
//map allowing them to cover the character.


#ifndef Particle_h
#define Particle_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Collider.h"
#include "Character.h"

class Particle{

	public:

		//Constructor takes in a png file, a Renderer, the number 
		//frames in the animation, and if the animation will be 
		//repeated.
		//Note: Stationary Objects should have -1 Frames
		Particle(const char* pngFile, SDL_Renderer* ParticleRenderer,
			 int numFrames, bool Repeat, bool Active);
		
		//Deconstructor
		~Particle();
		
		//Sets the size and the coordinates of the particle effect
		void SetParticleCoordinates(int srcX, int srcY, int destX,
					    int destY, int ParticleSizeX,
					    int ParticleSizeY, int FrameNumber);

		void Spellcast(char Direction, Character *Caster,
			       int ParticleSizeX, int ParticleSizeY);

		//This stops a particle from continuing its animations
		//
		void DeactivateParticle();
		void ActivateParticle();

		//Runs through a single frame of the particle animation
		//Leaves behind the next frame to render
		void RenderParticle();

		//If needed, here we add collider parameters to particles
		void AssignCollider(int colX, int colY, int colW, int colH);
		void AssignCollider(int colX, int colY, int colRadius);	
	
		//Returns particle colliders
		Circle GetCollisionCircle();
		SDL_Rect GetCollisionRect();

	private:

		//One determines if the animation will repeat, and
		//the other determines if the particle is active,
		//meaning that the animation will render
		bool ParticleRepeater, Activated;

		//These show the number of frames in the particle
		//effect and what frame is currently shown
		int ParticleFrames, CurrentFrame;
		
		SDL_Rect RectSrc, RectDest;

		SDL_Texture* ParticleTexture;

		SDL_Renderer* ParticleRenderer;

		//Colliders
		SDL_Rect CollisionRect;

		Circle CollisionCircle;
};
#endif
