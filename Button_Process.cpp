#include "Button_Process.h"

//handle mouse event with play button 
void Process_PlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick) 
{
	if (!PlayButton.IsInside(e, BIG_BUTTON)) 
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT ; //when the mouse is not in the button
	}
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
void Process_HelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, LTexture gInstructionTexture, LTexture gBackButtonTexture, SDL_Renderer *gRenderer, Mix_Chunk *gClick)
{
	if (!HelpButton.IsInside(e, BIG_BUTTON)) 
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
	}
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

						if (!BackButton.IsInside(e, BIG_BUTTON)) BackButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
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
void Process_ExitButton(SDL_Event* e, Button& ExitButton, bool& Quit,Mix_Chunk* gClick) 
{
	if (!ExitButton.IsInside(e, BIG_BUTTON)) 
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;  //when the mouse is not in the button
	}
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

//handle mouse event with continue button
void Process_ContinueButton(SDL_Event* e, Button ContinueButton, bool& GameState, Mix_Chunk* gClick)
{
	bool BackGame = false; //resume playing or not
	while (!BackGame)
	{
		do
		{
			if (!ContinueButton.IsInside(e, SMALL_BUTTON)) 
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
			}
			else
			{
				switch (e->type)
				{
					case SDL_MOUSEMOTION: //when the mouse moves across the button
					    ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					    break;
				    case SDL_MOUSEBUTTONDOWN: //when you click the mouse
					    GameState = true;
					    BackGame = true;
					    ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					    Mix_PlayChannel(-1, gClick,0);
					    Mix_ResumeMusic();
						break;
				}
			}
		}  while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}

//handle mouse event with pause button
void Process_PauseButton(SDL_Event* e, SDL_Rect (&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, LTexture gContinueButtonTexture, bool &GameState, Mix_Chunk *gClick,SDL_Renderer* gRenderer)
{
	if (!PauseButton.IsInside(e, SMALL_BUTTON)) 
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT; //when the mouse is not in the button
	}
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
			    GameState = false;

				SDL_Rect* ContinueButton_Clip = &gContinueButton[ContinueButton.currentSprite]; //Renders texture at given point
			    ContinueButton.Render(ContinueButton_Clip, gRenderer, gContinueButtonTexture);
			    SDL_RenderPresent(gRenderer); //Update screen

			    Process_ContinueButton(e,ContinueButton, GameState, gClick);
			    break;
		}
	}
}
