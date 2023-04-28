#include "Main_Game.h"
int main(int argc, char* argv[])
{
    std::vector<int>Score_Level ;
    Score_Level.push_back(SCORE_MAX_1) ;
    Score_Level.push_back(SCORE_MAX_2) ;
    Score_Level.push_back(SCORE_MAX_3) ;
    Score_Level.push_back(SCORE_MAX_4) ;
    Score_Level.push_back(SCORE_MAX_5) ;

	if (!Init()) 
	{
		std::cout << "Failed to initialize!" << std::endl; //Start up SDL and create window
	}
	else
	{
		if (!LoadMedia()) std::cout << "Failed to load media!" << std::endl; //Load media
		else
		{
			bool QuitMenu = false ;
			bool Play = false ;
			bool QuitGame = false ; 
			SDL_Event e; //Event handler
			Mix_PlayMusic(gMenuMusic, -1); //Play the music
			while (!QuitMenu) //While application is running (still on menu page)
			{
				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite]; //upload play button
				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite]; //upload help button
				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite]; //upload exit button

                gMenuTexture.Render(0, 0, gRenderer); //upload menu image
                PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);
                HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);
				ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer); //update screen

				while (SDL_PollEvent(&e) != 0) //Handle events on queue
				{
					if (e.type == SDL_QUIT) 
					{
						QuitMenu = true;
					}
					HandlePlayButton(&e, PlayButton, QuitMenu, Play, gClick); //process with play button
					HandleHelpButton(&e, gBackButton, HelpButton, BackButton,gInstructionTexture, gBackButtonTexture, gRenderer, gClick); //process with help button
					HandleExitButton(&e, ExitButton, QuitGame, gClick); //process with exit button
					if (QuitGame == true) 
					{
						return 0;
					}
				}
			}

			while (Play) //still play ?
			{
				srand(time(NULL));

			    bool LoseGame = false ;
				bool Game_State = true ;
				bool Receive = false ;
				int time = 0 ;
				int road = 0 ;
				int score = 0 ;
				int life = 2;
				int acceleration = 1;
				int frame_Character = 0;
				int frame_Threat = 0;
				int frame_Award = 0;
				
				SDL_Event e; //event handler
				
				Mix_PlayMusic(gMusic, -1); //play the music

				Threat threat1(IN_AIR_THREAT_1);  //the bat
                Threat threat2(ON_GROUND_THREAT_1);    //the cactus
                Threat threat3(ON_GROUND_THREAT_2 ) ;   //the stone

                Award award1(AWARD_1); //the coin
                Award award2(AWARD_2); //the diamond
                Award award3(AWARD_3); //the heart
                
				Generate_Threat(threat1, threat2, threat3, gThreatClips, gRenderer); //generate game threats
				int OffsetSpeed_Ground = BASE_OFFSET_SPEED;		
				int Speed_BackGround = BASE_OFFSET_SPEED;

				while (!LoseGame)
				{
					if (Game_State)
					{
						GenerateAward(award1, award2, award3, gAwardClips, gRenderer); //generate award
						Update_Speed_Road(time, acceleration, road); //update the speed and score
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								LoseGame = true;
								Play = false;
							}
							HandlePauseButton(&e, gRenderer, gContinueButton, PauseButton, ContinueButton, gContinueButtonTexture, Game_State, gClick);
							character.HandleEvent(e, gJump); //the character jumps
						}
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						Render_Scrolling_BackGround(Speed_BackGround,acceleration, gBackgroundTexture, gRenderer);
						Render_Scrolling_Ground(OffsetSpeed_Ground, acceleration, gGroundTexture, gRenderer); //upload and create animation of the ground

						character.Move(); //move the character
						SDL_Rect* currentClip_Character = nullptr;
						if (character.OnGround()) //process the animation when the character is on ground or in the air
						{
							currentClip_Character = &gCharacterClips[frame_Character / CHARACTER_RUNNING_FRAMES];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}
						else
						{
							currentClip_Character = &gCharacterClips[0];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}

                        SDL_Rect* currentClip_Threat = &gThreatClips[frame_Threat / THREAT_FLYING_FRAMES]; //upload the animation of the image of the bat
						threat1.Render(gRenderer, currentClip_Threat);
						threat1.Move(acceleration , IN_AIR_THREAT_1);
                        
						threat2.Render(gRenderer);
						threat2.Move(acceleration, ON_GROUND_THREAT_1); //movement of cactus
			
						threat3.Render(gRenderer) ;
						threat3.Move(acceleration , ON_GROUND_THREAT_2); //movement of the stone

                        award1.Render(gRenderer) ;
                        award1.Move(acceleration , AWARD_1); //movement of coin
                        
						SDL_Rect* currentClip_Award = &gAwardClips[frame_Award / AWARD_ROTATING_FRAMES]; //upload the animation of the image of the diamond
						award2.Render(gRenderer, currentClip_Award) ;
						award2.Move(acceleration , AWARD_2);

                        if(time > TIME_MAX - 500)
						{
							award3.Render(gRenderer) ;
						    award3.Move(acceleration , AWARD_3); //movement of heart
						}

						SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite]; //process with pause button if clicked
						PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);

                        gText1Texture.Render(TEXT1_POSX, TEXT1_POSY, gRenderer); //draw text and road
						gText2Texture.Render(TEXT2_POSX, TEXT2_POSY, gRenderer); //draw text and score
						gText3Texture.Render(TEXT3_POSX, TEXT3_POSY, gRenderer); //draw text and life
						Draw_Player_Result(gRoadTexture,gScoreTexture, gLifeTexture,textColor,gRenderer,gFont,road,score,life) ;
				       
						if (Check_Colission(life, character,currentClip_Character,threat1,currentClip_Threat)) //check collision
						{
							Mix_PauseMusic();
							if(life!=0)
							{
								threat1.Disappear() ;
								Mix_PlayChannel(-1,gCollision,0) ;
								Mix_ResumeMusic();
							}
							else
							{
							    Mix_PlayChannel(-1, gLose, 0);
								Mix_PlayMusic(gEndMusic,-1) ;
							    LoseGame = true;
							}
						}

						if (Check_Colission(life, character,currentClip_Character,threat2,currentClip_Threat)) //check collision
						{
							Mix_PauseMusic();
							if(life!=0)
							{
								threat2.Disappear() ;
								Mix_PlayChannel(-1,gCollision,0) ;
								Mix_ResumeMusic();
							}
							else
							{
							    Mix_PlayChannel(-1, gLose, 0);
								Mix_PlayMusic(gEndMusic,-1) ;
							    LoseGame = true;
							}
						}

						if (Check_Colission(life, character,currentClip_Character,threat3,currentClip_Threat)) //check collision
						{
							Mix_PauseMusic();
							if(life!=0)
							{
								threat3.Disappear() ;
								Mix_PlayChannel(-1,gCollision,0) ;
								Mix_ResumeMusic();
							}
							else
							{
							    Mix_PlayChannel(-1, gLose, 0);
								Mix_PlayMusic(gEndMusic,-1) ;
							    LoseGame = true;
							}
						}

                        if(CheckReceive(score,life,gCongrats,character,currentClip_Character,award1,currentClip_Award)) //check receive awards
						{
							award1.Award_Reset();
						}
						if(CheckReceive(score,life,gCongrats,character,currentClip_Character,award2,currentClip_Award)) //check receive awards
						{
							award2.Award_Reset();
						}
						if(CheckReceive(score,life,gCongrats,character,currentClip_Character,award3,currentClip_Award)) //check receive awards
						{
							award3.Award_Reset();
						}
						
                        Control_Char_Frame(frame_Character); //control the animation of the character
						Control_Threat_Frame(frame_Threat); //control the animation of the threat
						Control_Award_Frame(frame_Award); //control the animation of the award
						SDL_RenderPresent(gRenderer); //update the screen
					}
				}
				for(int i = TOTAL_ENDING - 1 ; i >= 0 ; i--)
				{
					if(score >= Score_Level[i])
					{
						DrawEndGameSelection(gLoseTexture[i], e, gRenderer, Play) ;
						break ;
					}
				}
				if (!Play) //if stop playing then erase game threat image
				{
					threat1.~Threat();
					threat2.~Threat();
					threat3.~Threat();

					award1.~Award();
					award2.~Award();
					award3.~Award();
				}
			}
		}
	}
	Close(); //Free resources and close SDL
	return 0;
}