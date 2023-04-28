#include "Game_Award.h"

Award::Award(int _type) //Initializes internal variables
{
	X = 0;
	Y = 0;

	Width = 0;
	Height = 0;

	type = rand()%3 ;
	type = _type;
	if (type == AWARD_1) //the coin
	{
        X = rand() % (SCREEN_WIDTH + AWARD_3_RANGE) + SCREEN_WIDTH*2 ;
		Y = GROUND - 100 ;
	}
	else if (type == AWARD_2) //the diamond
	{
		X = rand() % (SCREEN_WIDTH + AWARD_2_RANGE) + SCREEN_WIDTH*2 ;
		Y = GROUND - 100 ;
	}
	else if (type == AWARD_3) //the heart
	{
		X = rand() % (SCREEN_WIDTH + AWARD_1_RANGE) + SCREEN_WIDTH*2;
		Y = GROUND - 100;
	}
	AwardTexture = nullptr;
}

Award::~Award() //Deallocates memory
{
	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;
	type = -1 ;
	if (AwardTexture != nullptr)
	{
		AwardTexture = nullptr;
	}
}

void Award:: free() 
{
	if(AwardTexture != NULL)
	{
		SDL_DestroyTexture(AwardTexture) ;
		AwardTexture = NULL ;
		Width = 0 ;
		Height = 0 ;
	}
}

void Award::LoadFromFile(std::string path, SDL_Renderer* gRenderer) //loading the image of enemy at specified path
{
	SDL_Texture* newTexture = nullptr; //The final texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //Load image at specified path
	if (loadedSurface == nullptr)
	{
		std::cout << "Can not load image." << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF)); //Color key image
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); //Create texture from surface pixels
		if (newTexture == nullptr)
		{
			std::cout << "Can not create texture from surface." << std::endl;
		}
		else
		{
			Width = loadedSurface->w;  //Get image dimensions
			Height = loadedSurface->h;  //Get image dimensions
		}
		SDL_FreeSurface(loadedSurface); //Get rid of old loaded surface
	}
	AwardTexture = newTexture; //return success
}

void Award::Move(const int &acceleration , int type) //get the speed of game award
{
	X += -(AWARD_SPEED + acceleration); //update position x
	if (X + MAX_AWARD_WIDTH < 0) //when the award touches the screen to the left
	{
		if(type == AWARD_3)
		{
			X = rand() % (SCREEN_WIDTH + AWARD_1_RANGE) + SCREEN_WIDTH;
		    Y = GROUND - 100 ;
		}
		else if (type == AWARD_1)
		{
			X = rand() % (SCREEN_WIDTH + AWARD_2_RANGE) + SCREEN_WIDTH ;
		    Y = GROUND - 100;
		}
		else if (type == AWARD_2)
		{
			X = (rand() % (SCREEN_WIDTH + AWARD_3_RANGE))*5 + SCREEN_WIDTH ;
		    Y = GROUND - 100 ;
		}
	}
}

void Award::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip) //Shows the award on the screen
{
	SDL_Rect renderQuad = { X, Y, Width, Height }; //Set rendering space and render to screen
	if (currentClip != nullptr) //Set clip rendering dimensions
	{
		renderQuad.w = currentClip->w;
		renderQuad.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, AwardTexture, currentClip, &renderQuad); //Render to screen
}

int Award::GetType() //get the type of award
{
	if (type == AWARD_1)
	{
		return AWARD_1;
	}
	else if(type == AWARD_2)
	{
		return AWARD_2;
	}
	else
	{
		return AWARD_3 ;
	}
}

int Award::GetSpeed(const int &acceleration) //get the speed of game award
{
	return AWARD_SPEED + acceleration;
}

int Award::GetPosX() // get the position(x) of the award
{
	return X;
}

int Award::GetPosY() // get the position(y) of the award
{
	return Y;
}

int Award::GetWidth() //get the width of the award
{
	return Width;
}

int Award::GetHeight() //get the height of the award
{
	return Height;
}

void Award::Award_Reset()
{
	X  = 0 - SCREEN_WIDTH;
}