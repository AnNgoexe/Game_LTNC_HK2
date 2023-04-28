#ifndef BUTTON_PROCESS_H_
#define BUTTON_PROCESS_H_

#include "Game_Button.h"
#include "LTexture.h"

//handle mouse event with play button 
void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick); 

//handle mouse event with help button 
void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, LTexture gInstructionTexture, LTexture gBackButtonTexture, SDL_Renderer* gRenderer, Mix_Chunk* gClick);

//handle mouse event with exit button
void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick);  

//handle mouse event with continue button
void HandleContinueButton(SDL_Event* e, Button ContinueButton, LTexture gContinueButtonTexture, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], bool& Game_State, Mix_Chunk* gClick);

//handle mouse event with pause button
void HandlePauseButton(SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, LTexture gContinueButtonTexture, bool& game_state, Mix_Chunk* gClick);

#endif
