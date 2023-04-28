#ifndef GAME_BUTTON_H_
#define GAME_BUTTON_H_

#include "LTexture.h"

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

const int COMMON_BUTTON_WIDTH = 150; //Button constants
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 389; //Button constants
const int PLAY_BUTTON_POSY= 186;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 293;
const int EXIT_BUTTON_POSX = 389;
const int EXIT_BUTTON_POSY = 402;
const int BACK_BUTTON_POSX = 0;
const int BACK_BUTTON_POSY = 0;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

class Button //The mouse button
{
	private:
	    
		SDL_Point position; //Top left position
		
	public:
        
		ButtonSprite currentSprite; //Currently used global sprite
	    
		Button(int x, int y); //Initializes internal variables
	    
		void SetPosition(int x, int y);  //Sets top left position
	    
		bool IsInside(SDL_Event *e, int size);  //check whether mouse is inside the button
	    
		void Render(SDL_Rect* currentClip , SDL_Renderer* gRenderer, LTexture gButtonTexture); //Shows button sprite
};

#endif 