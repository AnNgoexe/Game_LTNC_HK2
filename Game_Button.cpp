#include "Game_Button.h"

Button::Button(int x, int y)  //Initializes internal variables
{
	currentSprite = BUTTON_MOUSE_OUT;
	MousePosition.x = x;
	MousePosition.y = y;
}

void Button::SetPosition(int x, int y) //Sets top left position
{
	MousePosition.x = x;
	MousePosition.y = y;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture) //Shows button sprite
{
	gButtonTexture.Render(MousePosition.x, MousePosition.y, gRenderer, currentClip); //Show current button sprite
}

bool Button::IsInside(SDL_Event *e, int ButtonType)  //check whether mouse is inside the button
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) //If mouse event happened
	{
		int Button_Width, Button_Height; //check whether it is either a small button or a big button
		if (ButtonType == SMALL_BUTTON) 
		{
			Button_Width = SMALL_BUTTON_WIDTH;
			Button_Height = SMALL_BUTTON_HEIGHT;
		}
		else
		{
			Button_Width = BIG_BUTTON_WIDTH;
			Button_Height = BIG_BUTTON_HEIGHT;
		}

		int x, y; //get mouse position
		SDL_GetMouseState(&x, &y); 
		if((x < MousePosition.x)||(x > MousePosition.x + Button_Width)) //Mouse is left of the button or right of the button
		{
			return false ;
		}
		else if((y < MousePosition.y)||(y > MousePosition.y + Button_Height))  //Mouse above or under the button
		{
			return false ;
		}
		else
		{
			return true ;
		}
	}
	return false;
}