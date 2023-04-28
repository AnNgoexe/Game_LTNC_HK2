#ifndef GAME_THREAT_H_
#define GAME_THREAT_H_

#include "LTexture.h"

#define THREAT_1_RANGE 100
#define THREAT_2_RANGE 350
#define THREAT_3_RANGE 500

#define IN_AIR_THREAT_1 0 //the bat
#define ON_GROUND_THREAT_1 1 //the cactus
#define ON_GROUND_THREAT_2 2 //the stone

#define THREAT_SPEED 5
#define MAX_THREAT_WIDTH 100


class Threat //the game threat (the obstable) move on the screen
{
	private:

	    int posX, posY; //The X and Y offsets of the game threat

	    int Width, Height; //the width and height of the game threat

	    int type; //type of game threat

	    SDL_Texture *ThreatTexture;

    public:

	    Threat(int _type); //Initializes internal variables

	    ~Threat(); //Deallocates memory

	    void LoadFromFile(std::string path, SDL_Renderer* gRenderer); // loading the image of threat at specified path

	    void Move(const int& acceleration , int type); //Moves the threat

	    void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr); //Shows the threat on the screen

	    int GetType();  // get the type of game threat

	    int GetSpeed(const int& acceleration); //get the speed of game threat

	    int GetPosX(); // get the position(x) of the threat

	    int GetPosY(); // get the position(y) of the threat

	    int GetWidth(); // get the width of the threat

	    int GetHeight(); //get the height of the threat

		void Disappear(); //game threats disappear when colliding with the character
};

#endif 