#include "Game_Button.h"

Button::Button(int x, int y)  //Initializes internal variables
{
	position.x = x;
	position.y = y;
	currentSprite = BUTTON_MOUSE_OUT;
}

void Button::SetPosition(int x, int y) //Sets top left position
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(SDL_Event *e, int size)  //check whether mouse is inside the button
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) //If mouse event happened
	{
		int x, y; //get mouse position
		int button_width, button_height; //check whether it is either a small button or a big button
		if (size == SMALL_BUTTON) 
		{
			button_width = SMALL_BUTTON_WIDTH;
			button_height = SMALL_BUTTON_HEIGHT;
		}
		else
		{
			button_width = COMMON_BUTTON_WIDTH;
			button_height = COMMON_BUTTON_HEIGHT;
		}
		SDL_GetMouseState(&x, &y); 
		bool inside = true; //Check if mouse is in button
		if (x < position.x) //Mouse is left of the button
		{
			inside = false;
		}
		else if (x > position.x + button_width) //Mouse is right of the button
		{
			inside = false;
		}
		else if (y < position.y)  //Mouse above the button
		{
			inside = false;
		}
		else if (y > position.y + button_height)  //Mouse above the button
		{
			inside = false;
		}
		return inside; //return the result
	}
	return false;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture) //Shows button sprite
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip); //Show current button sprite
}