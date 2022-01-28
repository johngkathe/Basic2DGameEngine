//This Class handles Collisions and Collider Boxes
//John G. Kathe 11/15/20

//Checks for Collisions
//Creates Boxes that serve no purpose other than acting as walls

#ifndef Collider_h
#define Collider_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


//A simple circle structure for circular colliders
struct Circle{
	int x, y, radius;
};

class Collider{

	public:

		//Constructor and Deconstructor
		Collider();
		~Collider();

		//These create independent colliders to serve a collision
		//purpose without being a particle or character
		void AssignWall(int colX, int colY, int colW, int colH);
		void AssignWall(int colX, int colY, int colRadius);

		//Three different Collision checks, note that rect circle
		//CollisionCheck requires the rect first.
		bool CollisionCheck(SDL_Rect Rect1, SDL_Rect Rect2);
		bool CollisionCheck(SDL_Rect Rect1, Circle Circle2);
		bool CollisionCheck(Circle Circle1, Circle Circle2);

		//Getter for the "wall" colliders
		SDL_Rect GetWallRect();
		Circle   GetWallCircle();

	private:
		//Checkers serve CollisionCheck functions
		//The Wall circle and rect are for a collision
		//box or circle
		SDL_Rect CheckRect1, CheckRect2, WallRect;
		Circle CheckCircle1, CheckCircle2, WallCircle;

		//A boolean to show is a collision occurred
		bool Collided;
};

#endif
