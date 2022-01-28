//Instantiates the Collider Class
//John G. Kathe 11/15/20

#include "Collider.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

//Constructor and Destructor
Collider::Collider(){};
Collider::~Collider(){};

//Creates an invisible, rectangular wall
void Collider::AssignWall(int colX, int colY, int colW, int colH){
	WallRect.x = colX;
	WallRect.y = colY;
	WallRect.w = colW;
	WallRect.h = colH;
};

//Creats an invisible, circular wall
void Collider::AssignWall(int colX, int colY, int colRadius){
	WallCircle.x = colX;
	WallCircle.y = colY;
	WallCircle.radius = colRadius;
}

//Now we do collision detection, returning a bool if a collision is detected

//Comparing 2 Rects
bool Collider::CollisionCheck(SDL_Rect Rect1, SDL_Rect Rect2){
		
	//Declaring ints to make logic quicker
	int XMax1 = Rect1.x + Rect1.w;
	int YMax1 = Rect1.y + Rect1.h;

	int XMax2 = Rect2.x + Rect2.w;
	int YMax2 = Rect2.y + Rect2.h;

	//Check for Collision
	if(Rect1.x <= XMax2 &&
	   Rect2.x <= XMax1 &&
	   Rect1.y <= YMax2 &&
	   Rect2.y <= YMax1) return true;

	//No collision because if statement is false 
	else return false;
};

//Comparing a Rect and a Cirlce
//NOTE: Rect proceeds Circle in this function
bool Collider::CollisionCheck(SDL_Rect Rect1, Circle Circle2){
	
	//Declaring ints to make the logic quicker
	int XMax = Rect1.x + Rect1.w;
	int YMax = Rect1.y + Rect1.h;

	int CheckX, CheckY;
	
	//Now we determine which sides are used, the min or max of x and y
	//X edges
	if(Circle2.x < Rect1.x) CheckX = Rect1.x;
	else if(Circle2.x > XMax) CheckX = XMax;
	//Y edges
	if(Circle2.y < Rect1.y) CheckY = Rect1.y;
	else if(Circle2.y > YMax) CheckY = YMax;

	//Now we find the differences between each x and y
	int dx = Circle2.x - CheckX;
	int dy = Circle2.y - CheckY;

	//Get the distance separating the two
	double separation = (dx * dx + dy * dy);

	if(separation > Circle2.radius) return false;
	else return true;
};


bool Collider::CollisionCheck(Circle Circle1, Circle Circle2){
	
	//get the change in distance
	int dx = Circle1.x - Circle2.x;
	int dy = Circle1.y - Circle2.y;

	//Determining the distance squared from the 
	double separation = dx * dx + dy * dy;

	//If the distance is further than the radius then no collision
	if(separation >= (Circle1.radius * Circle1.radius)) return false;
	else return true;
}; 

SDL_Rect Collider::GetWallRect(){
	return WallRect;
};

Circle Collider::GetWallCircle(){
	return WallCircle;
};
