#include "Button_Process.h"

//handle mouse event with play button 
void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick) 
{
	if (!PlayButton.IsInside(e, COMMON_BUTTON)) PlayButton.currentSprite = BUTTON_MOUSE_OUT ; //when the mouse is not in the button
	else
	{
		switch (e->type) //Set mouse over sprite
		{
			case SDL_MOUSEMOTION: //when the mouse moves across the button
			    PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			    break;
		    case SDL_MOUSEBUTTONDOWN: //when you click the mouse
			    Play = true;
			    QuitMenu = true;
			    Mix_PlayChannel(-1, gClick, 0);
			    PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			    break;
		}
	}
}

//handle mouse event with help button
void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, LTexture gInstructionTexture, LTexture gBackButtonTexture, SDL_Renderer *gRenderer, Mix_Chunk *gClick)
{
	if (!HelpButton.IsInside(e, COMMON_BUTTON)) HelpButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
	else
	{
		switch (e->type) //Set mouse over sprite
		{
		    case SDL_MOUSEMOTION: //when the mouse moves across the button
			    HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			    break;
		    case SDL_MOUSEBUTTONDOWN: //when you click the mouse
			    HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			    Mix_PlayChannel(-1, gClick, 0);
			    bool ReadDone = false; //check whether players have read the instruction
			    while (!ReadDone)
			    {
				    do
				    {
					    gInstructionTexture.Render(0, 0, gRenderer); //Renders texture at given point

					    SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					    BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture); //Shows button sprite (back button)

						SDL_RenderPresent(gRenderer); //update screen

						if (!BackButton.IsInside(e, COMMON_BUTTON)) BackButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
						else
					    {
						    switch (e->type) //Set mouse over sprite
						    {
						        case SDL_MOUSEMOTION: //when the mouse moves across the button
							        BackButton.currentSprite = BUTTON_MOUSE_OVER;
							        break;
						        case SDL_MOUSEBUTTONDOWN: //when you click the mouse
							        BackButton.currentSprite = BUTTON_MOUSE_OVER;
							        Mix_PlayChannel(-1, gClick, 0);
							        ReadDone = true;
							        break;
						    }
					    }
				    } while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			    }
			    break;
		}
	}
}

//handle mouse event with exit button
void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit,Mix_Chunk* gClick) 
{
	if (!ExitButton.IsInside(e, COMMON_BUTTON)) ExitButton.currentSprite = BUTTON_MOUSE_OUT;  //when the mouse is not in the button
	else
	{
		switch (e->type)
		{
			case SDL_MOUSEMOTION: //when the mouse moves across the button
			    ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			    break;
		    
			case SDL_MOUSEBUTTONDOWN: //when you click the mouse
			    Quit = true;
			    ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			    Mix_PlayChannel(-1, gClick, 0);
			    break;
		}
	}
}

//handle mouse event with pause button
void HandlePauseButton(SDL_Event* e,SDL_Renderer* gRenderer, SDL_Rect (&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, LTexture gContinueButtonTexture, bool &Game_State, Mix_Chunk *gClick)
{
	if (!PauseButton.IsInside(e, SMALL_BUTTON)) PauseButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
	else
	{
		switch (e->type)
		{
		    case SDL_MOUSEMOTION: //when the mouse moves across the button
			    PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			    break;
		    
			case SDL_MOUSEBUTTONDOWN: //when you click the mouse
			    PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			    Mix_PlayChannel(-1, gClick, 0);
			    Mix_PauseMusic();
			    break;
		   
		    case SDL_MOUSEBUTTONUP:   //when you release a mouse click
			    Game_State = false;
			    HandleContinueButton(e, ContinueButton, gContinueButtonTexture, gRenderer, gContinueButton, Game_State, gClick);
			    break;
		}
	}
}

//handle mouse event with continue button
void HandleContinueButton(SDL_Event* e, Button ContinueButton, LTexture gContinueButtonTexture, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], bool& Game_State, Mix_Chunk* gClick)
{
	bool Back_To_Game = false; //resume playing or not
	while (!Back_To_Game)
	{
		do
		{
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite]; //Renders texture at given point
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer); //Update screen

			if (!ContinueButton.IsInside(e, SMALL_BUTTON)) ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			else
			{
				switch (e->type)
				{
					case SDL_MOUSEMOTION: //when the mouse moves across the button
					    ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					    break;
				    case SDL_MOUSEBUTTONDOWN: //when you click the mouse
					    ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					    Mix_PlayChannel(-1, gClick,0);
					    Mix_ResumeMusic();
					    Game_State = true;
					    Back_To_Game = true;
						break;
				}
			}
		}  while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}