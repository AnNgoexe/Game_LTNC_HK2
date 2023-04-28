#include "Game_Threat.h"

Threat::Threat(int _type) //Initializes internal variables
{
	posX = 0;
	posY = 0;
	Width = 0;
	Height = 0;
	type = rand()%3 ;
	type = _type;
	if (type == IN_AIR_THREAT_1) //the bat
	{
		posX = rand() % (SCREEN_WIDTH + THREAT_1_RANGE) + SCREEN_WIDTH;
		posY = GROUND  ;
	}
	else if (type == ON_GROUND_THREAT_1) //the cactus
	{
		posX = rand() % (SCREEN_WIDTH + THREAT_2_RANGE) + SCREEN_WIDTH ;
		posY = GROUND - 18;
	}
	else if (type == ON_GROUND_THREAT_2) //the stone
	{
		posX = (rand() % (SCREEN_WIDTH + THREAT_3_RANGE))*5 + SCREEN_WIDTH ;
		posY = GROUND + 5 ;
	}
	ThreatTexture = nullptr;
}

Threat::~Threat() //Deallocates memory
{
	posX = 0;
	posY = 0;
	Width = 0;
	Height = 0;
	type = 0;
	if (ThreatTexture != nullptr)
	{
		ThreatTexture = nullptr;
		SDL_DestroyTexture(ThreatTexture) ;
	}
}

void Threat::LoadFromFile(std::string path, SDL_Renderer* gRenderer) //loading the image of threat at specified path
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
	ThreatTexture = newTexture; //return success
}

void Threat::Move(const int &acceleration , int type) //get the speed of game threat
{
	if(type == ON_GROUND_THREAT_2 || type == ON_GROUND_THREAT_1)
	{
		posX += -(THREAT_SPEED + acceleration); //update position x
	}
	else if(type == IN_AIR_THREAT_1)
	{
		posX += -(THREAT_SPEED + acceleration*2); //update position x
	}
	if (posX + MAX_THREAT_WIDTH < 0) //when the threat touches the screen to the left
	{
		if(type == IN_AIR_THREAT_1)
		{
			posX = rand() % (SCREEN_WIDTH + THREAT_1_RANGE) + SCREEN_WIDTH;
			posY = GROUND ;
		}
		else if (type == ON_GROUND_THREAT_1)
		{
			posX = rand() % (SCREEN_WIDTH + THREAT_2_RANGE) + SCREEN_WIDTH ;
			posY = GROUND - 18;
		}
		else if (type == ON_GROUND_THREAT_2)
		{
			posX = (rand() % (SCREEN_WIDTH + THREAT_3_RANGE))*5 + SCREEN_WIDTH ;
		    posY = GROUND + 5 ;
		}
	}
}

void Threat::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip) //Shows the threat on the screen
{
	SDL_Rect renderQuad = { posX, posY, Width, Height }; //Set rendering space and render to screen
	if (currentClip != nullptr) //Set clip rendering dimensions
	{
		renderQuad.w = currentClip->w;
		renderQuad.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, ThreatTexture, currentClip, &renderQuad); //Render to screen
}

int Threat::GetType() //get the type of threat
{
	if (type == IN_AIR_THREAT_1)
	{
		return IN_AIR_THREAT_1;
	}
	else if(type == ON_GROUND_THREAT_1)
	{
		return ON_GROUND_THREAT_1;
	}
	else
	{
		return ON_GROUND_THREAT_2 ;
	}
}

int Threat::GetSpeed(const int &acceleration) //get the speed of game threat
{
	return THREAT_SPEED + acceleration;
}

int Threat::GetPosX() // get the position(x) of the threat
{
	return posX;
}

int Threat::GetPosY() // get the position(y) of the threat
{
	return posY;
}

int Threat::GetWidth() //get the width of the threat
{
	return Width;
}

int Threat::GetHeight() //get the height of the threat
{
	return Height;
}

void Threat::Disappear() //game threats disappear when colliding with the character
{
	posX = 0 - posX ;
}