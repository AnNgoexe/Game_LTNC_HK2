#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "Game_Button.h"
#include "Game_Threat.h"
#include "Game_Character.h"
#include "LTexture.h"
#include "Game_Award.h"

//increase the speed and road of the character depending on time
void Update_Speed_Road (int& time, int& speed, int& road) ;  

//generate game threats
void Generate_Threat(Threat& threat1, Threat& threat2, Threat& threat3, SDL_Rect gThreatClips[THREAT_FLYING_FRAMES], SDL_Renderer* gRenderer); 

//check whether there is a collision between character and game threat
bool Check_Colission(int& life, Character character, SDL_Rect* character_clip, Threat threat, SDL_Rect* threat_clip = nullptr);

//Update and show player's life on the screen
void Draw_Player_Result(LTexture gRoadTexture, LTexture gScoreTexture, LTexture gLifeTexture, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont, int& road, int& score, int& life) ;

//choose whether the player wants to play again or not
void DrawEndGameSelection(LTexture gLoseTexture,SDL_Event e, SDL_Renderer *gRenderer, bool &Play_Again);

//generate award
void GenerateAward(Award& award1, Award& award2, Award& award3, SDL_Rect gAwardClips[AWARD_ROTATING_FRAMES], SDL_Renderer* gRenderer); 

//check whether the character receives awards
bool CheckReceive(int& score, int&life, Mix_Chunk *gCongrats, Character character, SDL_Rect* character_clip, Award award, SDL_Rect* award_clip = nullptr);

#endif 