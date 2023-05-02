#ifndef BUTTON_PROCESS_H_
#define BUTTON_PROCESS_H_

#include "Game_Button.h"
#include "LTexture.h"

//handle mouse event with play button 
void Process_PlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick); 

//handle mouse event with help button 
void Process_HelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, LTexture gInstructionTexture, LTexture gBackButtonTexture, SDL_Renderer* gRenderer, Mix_Chunk* gClick);

//handle mouse event with exit button
void Process_ExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick);  

//handle mouse event with continue button
void Process_ContinueButton(SDL_Event* e, Button ContinueButton, bool& GameState, Mix_Chunk* gClick);

//handle mouse event with pause button
void Process_PauseButton(SDL_Event* e, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, LTexture gContinueButtonTexture, bool& GameState, Mix_Chunk* gClick,SDL_Renderer* gRenderer);

#endif
