#ifndef LTEXTURE_H_
#define LTEXTURE_H_
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

#define TIME_MAX 2000
#define GROUND_SPEED 5
#define BASE_OFFSET_SPEED 0
#define BACKGROUND_SPEED 3
#define GROUND 430
#define TOTAL_ENDING 5

const int SCORE_MAX_1 = 0 ;
const int SCORE_MAX_2 = 50 ;
const int SCORE_MAX_3 = 100 ;
const int SCORE_MAX_4 = 300 ;
const int SCORE_MAX_5 = 500 ;

const int TEXT1_POSX = 350;
const int TEXT1_POSY = 15;
const int ROAD_POSX = 530;
const int ROAD_POSY = 15;

const int TEXT2_POSX = 80;
const int TEXT2_POSY = 15;
const int SCORE_POSX = 240;
const int SCORE_POSY = 15;

const int TEXT3_POSX = 700;
const int TEXT3_POSY = 15;
const int LIFE_POSX = 830;
const int LIFE_POSY = 15;

const int acceleration = 1 ;
const int CHARACTER_RUNNING_FRAMES = 6;
const int THREAT_FLYING_FRAMES = 5;
const int AWARD_ROTATING_FRAMES = 8;

const int JUMP_SPEED = -8;
const int FALL_SPEED = 8;

class LTexture //texture wrapper class
{
	private:

	    SDL_Texture* mTexture; //The actual hardware texture

	    int mWidth; //Image dimensions (width)

	    int mHeight; //Image dimensions (height)

    public:

	    LTexture(); //Initializes variables

	    ~LTexture(); //Deallocates memory

	    void Free(); //Deallocates texture

        void setColor( Uint8 red, Uint8 green, Uint8 blue ); //Set color modulation
		
		void setBlendMode( SDL_BlendMode blending ); //Set blending

		void setAlpha( Uint8 alpha ); //Set alpha modulation

	    bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer); //Creates image from font string
	
	    bool LoadFromFile(std::string path, SDL_Renderer *gRenderer); //Loads image at specified path
	
	    void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr); //Renders texture at given point

	    int GetWidth(); //Gets image dimensions (width)

	    int GetHeight(); //Gets image dimensions (height)
};

#endif 