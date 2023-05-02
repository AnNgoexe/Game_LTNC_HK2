#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "LTexture.h"

#define JUMP 1
#define FALL 2
#define RUN	0
#define GROUND 430
#define MAX_HEIGHT 250

class Character
{
	private:

	    int posX, posY; //position X , Y of the character

	    int status; //the status of the character
		
    public:

	    Character(); //Initializes the variables

	    void HandleEvent(SDL_Event& e, Mix_Chunk *gJump); //Takes key presses and adjusts the character's position

		void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture); //Shows the character on the screen

	    void Move(); //move the character up and down

	    int GetPosX(); //get the position X of the character

	    int GetPosY(); //get the position Y of the character

		bool IsOnGround(); //check whether the character is on ground or not
};

#endif 