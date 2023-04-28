#include "Game_Logic.h"

//increase the speed and score of the character depending on time
void Update_Speed_Road (int& time,int& speed,int& road) 
{
	if (time == TIME_MAX) speed = speed + acceleration ;
	if (time > TIME_MAX) time = 0 ;
	if (time % 5 == 0) road++ ;
	time++ ;
}

//generate game threats
void Generate_Threat(Threat& threat1, Threat& threat2, Threat& threat3, SDL_Rect gThreatClips[THREAT_FLYING_FRAMES], SDL_Renderer * gRenderer) 
{
	threat1.LoadFromFile("Image/threat/bat.png", gRenderer); //bat - animation
	{
		gThreatClips[0].x = 43 * 3;
		gThreatClips[0].y = 0;
		gThreatClips[0].w = 43;
		gThreatClips[0].h = 30;

		gThreatClips[1].x = 43 * 4;
		gThreatClips[1].y = 0;
		gThreatClips[1].w = 43;
		gThreatClips[1].h = 30;

		gThreatClips[2].x = 43 * 2;
		gThreatClips[2].y = 0;
		gThreatClips[2].w = 43;
		gThreatClips[2].h = 30;

		gThreatClips[3].x = 43;
		gThreatClips[3].y = 0;
		gThreatClips[3].w = 43;
		gThreatClips[3].h = 30;

		gThreatClips[4].x = 0;
		gThreatClips[4].y = 0;
		gThreatClips[4].w = 43;
		gThreatClips[4].h = 30;
	}
	threat2.LoadFromFile("Image/threat/cactus.png", gRenderer); //cactus image
	threat3.LoadFromFile("Image/threat/stone.png", gRenderer); //stone image
}

//check whether there is a collision between character and game threat
bool Check_Colission(int& life, Character character,SDL_Rect* character_clip, Threat threat, SDL_Rect* threat_clip) 
{
    bool collide = false;
	
	int leftA = character.GetPosX();   //position of the character
	int rightA = character.GetPosX() + character_clip->w;
	int topA = character.GetPosY();
	int bottomA = character.GetPosY() + character_clip->h;

	if (threat.GetType() == ON_GROUND_THREAT_1) //collide with the cactus
	{
		int leftB = threat.GetPosX();
		int rightB = threat.GetPosX() + threat_clip->w;
		int topB = threat.GetPosY();
		int bottomB = threat.GetPosY() + threat_clip->h;

		if (rightA - 25 >= leftB && leftA + 25 <= rightB) 
		{
			if (bottomA - 30 >= topB) 
			{
				collide = true;
				life-- ;
			}
		}
	}
	else if (threat.GetType() == ON_GROUND_THREAT_2) //collide with the stone
	{
		int leftC = threat.GetPosX();
		int rightC = threat.GetPosX() + threat_clip->w;
		int topC = threat.GetPosY();
		int bottomC = threat.GetPosY() + threat_clip->h;

		if (rightA - 40 >= leftC && leftA + 40 <= rightC) 
		{
			if (bottomA - 30 >= topC) 
			{
				collide = true;
				life-- ;
			}
		}
	}
	else if (threat.GetType() == IN_AIR_THREAT_1) // collide with the bat
	{
		int leftD = threat.GetPosX() + 35 ;
		int rightD = threat.GetPosX() + threat_clip->w - 35 ;
		int topD = threat.GetPosY() ;
		int bottomD = threat.GetPosY() + threat_clip->h - 15;

		if (rightA >= leftD && leftA <= rightD) 
		{
			if(( topA <= bottomD && topA >= topD ) || ( bottomA <= bottomD && bottomA >= topD ))
			{
				collide = true; 
			    life-- ;
			}
		}
	}
	return collide; //return the result whether collision happens
}

//Update and show player's road, score and life on the screen
void Draw_Player_Result(LTexture gRoadTexture, LTexture gScoreTexture, LTexture gLifeTexture, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont, int& road, int& score, int& life) 
{
	if (gRoadTexture.LoadFromRenderedText(std::to_string(road), gFont, textColor, gRenderer))
	{
		gRoadTexture.Render(ROAD_POSX, ROAD_POSY, gRenderer);
	}
	if (gScoreTexture.LoadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
	if (gLifeTexture.LoadFromRenderedText(std::to_string(life), gFont, textColor, gRenderer))
	{
		gLifeTexture.Render(LIFE_POSX, LIFE_POSY, gRenderer);
	}
}

//choose whether the player wants to play again or not
void DrawEndGameSelection(LTexture gLoseTexture, SDL_Event e, SDL_Renderer *gRenderer, bool &Play_Again)
{
	if (Play_Again) //status of checking playing again
	{
		bool End_Game = false; //status of checking ending game
		while (!End_Game)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e.type == SDL_KEYDOWN) //when pressing the keyboard
				{
					switch (e.key.keysym.sym)
					{
					    case SDLK_SPACE: //if press space
						    End_Game = true;
							Play_Again = true ;
						    break;
					    case SDLK_ESCAPE: //if press esc
						    End_Game = true;
						    Play_Again = false;
						    break;
					}
				}
			}
			gLoseTexture.Render(0,0,gRenderer) ;
			SDL_RenderPresent(gRenderer); //Update screen
		}
	}
}

//generate award
void GenerateAward(Award &award1, Award &award2, Award &award3, SDL_Rect gAwardClips[AWARD_ROTATING_FRAMES], SDL_Renderer *gRenderer)
{
	award1.LoadFromFile("Image/award/coin.png", gRenderer); //coin image
	award2.LoadFromFile("Image/award/diamond.png", gRenderer); //diamond- animation
	{
		gAwardClips[0].x = 32 * 0;
		gAwardClips[0].y = 0;
		gAwardClips[0].w = 32;
		gAwardClips[0].h = 60;

		gAwardClips[1].x = 32 * 1;
		gAwardClips[1].y = 0;
		gAwardClips[1].w = 32;
		gAwardClips[1].h = 60;

		gAwardClips[2].x = 32 * 2;
		gAwardClips[2].y = 0;
		gAwardClips[2].w = 32;
		gAwardClips[2].h = 60;

		gAwardClips[3].x = 32 * 3;
		gAwardClips[3].y = 0;
		gAwardClips[3].w = 32;
		gAwardClips[3].h = 60;

		gAwardClips[4].x = 32 * 4;
		gAwardClips[4].y = 0;
		gAwardClips[4].w = 32;
		gAwardClips[4].h = 60;

		gAwardClips[5].x = 32 * 5;
		gAwardClips[5].y = 0;
		gAwardClips[5].w = 32;
		gAwardClips[5].h = 60;

		gAwardClips[6].x = 32 * 6;
		gAwardClips[6].y = 0;
		gAwardClips[6].w = 32;
		gAwardClips[6].h = 60;

		gAwardClips[7].x = 32 * 7;
		gAwardClips[7].y = 0;
		gAwardClips[7].w = 32;
		gAwardClips[7].h = 60;
	}
	award3.LoadFromFile("Image/award/heart.png", gRenderer); //heart image
}

//check whether the character receives awards
bool CheckReceive(int& score, int& life, Mix_Chunk *gCongrats, Character character, SDL_Rect* character_clip, Award award, SDL_Rect* award_clip)
{
	bool receive = false;
	
	int leftA = character.GetPosX();   //position of the character
	int rightA = character.GetPosX() + character_clip->w;
	int topA = character.GetPosY();
	int bottomA = character.GetPosY() + character_clip->h;

	if (award.GetType() == AWARD_1) //touch the coin
	{
		int leftB = award.GetPosX();
		int rightB = award.GetPosX() + award_clip->w;
		int topB = award.GetPosY();
		int bottomB = award.GetPosY() + award_clip->h;

		if (rightA - 25 >= leftB && leftA + 25 <= rightB ) 
		{
		 	if(( topA <= bottomB && topA >= topB ) || ( bottomA <= bottomB && bottomA >= topB ))
			{
				receive = true ;
				score = score + 10;
				Mix_PlayChannel(-1,gCongrats,0) ;
			}
		}
	}
	else if (award.GetType() == AWARD_2) //touch the diamond
	{
		int leftC = award.GetPosX();
		int rightC = award.GetPosX() + award_clip->w;
		int topC = award.GetPosY();
		int bottomC = award.GetPosY() + award_clip->h;

		if (rightA - 25 >= leftC && leftA + 25 <= rightC) 
		{
			if(( topA <= bottomC && topA >= topC ) || ( bottomA <= bottomC && bottomA >= topC ))
			{
				receive = true ;
				score = score + 20;
				Mix_PlayChannel(-1,gCongrats,0) ;
			}
		}
	}
	else if (award.GetType() == AWARD_3) // touch the heart
	{
		int leftD = award.GetPosX() ;
		int rightD = award.GetPosX() + award_clip->w ;
		int topD = award.GetPosY();
		int bottomD = award.GetPosY() + award_clip->h ;

		if (rightA - 25 >= leftD && leftA + 25 <= rightD) 
		{
			if(( topA <= bottomD && topA >= topD ) || ( bottomA <= bottomD && bottomA >= topD ))
			{
				receive = true ;
				if(life<2) life++ ;
				Mix_PlayChannel(-1,gCongrats,0) ;
			}
		}
	}
	return receive; //return the result whether the character receives awards
}
