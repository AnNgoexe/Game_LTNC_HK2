#include "Game_Character.h"

Character::Character() //Initializes the variables
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;
	status = RUN ;
}

bool Character::IsOnGround() //check whether the character is on ground or not
{
	if(posY == GROUND) return true;
	else return false ;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump) //Takes key presses and control events 
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //If a key was pressed
	{
		switch (e.key.keysym.sym) //Adjust the velocity
		{
			case SDLK_SPACE: //if press the up button
			{
				if(IsOnGround())
				{
					Mix_PlayChannel(-1, gJump, 0); // play the sound
				    status = JUMP; // adjust the character's position
				}
			}
		}
	}
}

void Character::Move() //move the character up and down
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
	}
}

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture) //Shows the character on the screen
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX() //get the position X of the character
{
	return posX;
}

int Character::GetPosY() //get the position Y of the character
{
	return posY;
}