#ifndef GAME_AWARD_H_
#define GAME_AWARD_H_

#include "LTexture.h"

#define AWARD_MAX_HEIGHT 300
#define AWARD_MIN_HEIGHT 350

#define AWARD_1_RANGE 100
#define AWARD_2_RANGE 250
#define AWARD_3_RANGE 400

#define AWARD_1 0 //the coin
#define AWARD_2 1 //the diamond
#define AWARD_3 2 //the heart

#define AWARD_SPEED 5
#define MAX_AWARD_WIDTH 100
#define TIME_APPEAR 180

class Award //the game award move on the screen
{
	private:

	    int X, Y; //The X and Y offsets of the game award

	    int Width, Height; //the width and height of the game award

	    int type; //type of game award

	    SDL_Texture *AwardTexture;

    public:

	    Award(int _type); //Initializes internal variables

	    ~Award(); //Deallocates memory

		void free() ;

	    void LoadFromFile(std::string path, SDL_Renderer* gRenderer); // loading the image of award at specified path

	    void Move(int& acceleration , int type); //Moves the award

	    void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr); //Shows the award on the screen

	    int GetType();  // get the type of game award

	    int GetSpeed(int& acceleration); //get the speed of game award

	    int GetPosX(); // get the position(x) of the award

	    int GetPosY(); // get the position(y) of the award

	    int GetWidth(); // get the width of the award

	    int GetHeight(); //get the height of the award

		void AwardReset(); //to make awards disappear when the character receives
};

#endif 