#include "Frame_Ground_Process.h"

//scrolling the main ground depending on time and speed
void Render_Scrolling_Ground(int& speed, int acceleration, LTexture gGroundTexture, SDL_Renderer* gRenderer)
{
	speed = speed - (GROUND_SPEED + acceleration) ;
	if (speed < -gGroundTexture.GetWidth())
	{
		speed = 0;
	}
	gGroundTexture.Render(speed, 0, gRenderer); //Render the ground
	gGroundTexture.Render(speed + gGroundTexture.GetWidth(), 0, gRenderer); //Render the ground
}

//animation cycle (character)
void Control_Char_Frame(int &frame) 
{
	frame++; //Go to next frame
	if (frame / 6 >= CHARACTER_RUNNING_FRAMES) //replay the animation cycle
	{
		frame = 0;
	}
}

//animation cycle(enemy)
void Control_Threat_Frame(int &frame) 
{
	frame++; //Go to next frame
	if (frame / 5 >= THREAT_FLYING_FRAMES) //replay the animation cycle
	{
		frame = 0;
	}
}

//the cycle animation
void Control_Award_Frame(int& frame)
{
	frame++; //Go to next frame
	if( frame / 8 >= AWARD_ROTATING_FRAMES) //Go to next frame
	{
		frame = 0 ;
	}
}

//scrolling the background depending on time and speed
void Render_Scrolling_BackGround(int& speed, int acceleration, LTexture gBackGroundTexture, SDL_Renderer* gRenderer)
{
	speed = speed - (BACKGROUND_SPEED + acceleration) ;
	if (speed < -gBackGroundTexture.GetWidth())
	{
		speed = 0;
	}
	gBackGroundTexture.Render(speed, 0, gRenderer); //Render the background
	gBackGroundTexture.Render(speed + gBackGroundTexture.GetWidth(), 0, gRenderer); //Render the background
}