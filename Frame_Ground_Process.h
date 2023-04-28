#ifndef FRAME_GROUND_PROCESS_H_
#define FRAME_GROUND_PROCESS_H_

#include "LTexture.h"

//the cycle animation
void Control_Char_Frame(int& frame); 

//the cycle aimation
void Control_Threat_Frame(int& frame); 

//the cycle animation
void Control_Award_Frame(int& frame);

//scrolling the main ground depending on time and speed
void Render_Scrolling_Ground(int& speed, int acceleration, LTexture gGroundTexture, SDL_Renderer* gRenderer);

//scrolling the background depending on time and speed
void Render_Scrolling_BackGround(int& speed, int acceleration, LTexture gBackGroundTexture, SDL_Renderer* gRenderer);

#endif