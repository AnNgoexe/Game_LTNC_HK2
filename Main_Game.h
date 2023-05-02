#include "Game_Logic.h"
#include "Button_Process.h"
#include "Frame_Ground_Process.h"

SDL_Window* gWindow = nullptr; //The window we'll be rendering to
SDL_Renderer* gRenderer = nullptr; //The window renderer
TTF_Font* gFont = nullptr; //Globally used font

SDL_Rect gPlayButton[BUTTON_TOTAL]; //Mouse button sprites (play button)
SDL_Rect gExitButton[BUTTON_TOTAL]; //Mouse button sprites (exit button)
SDL_Rect gBackButton[BUTTON_TOTAL]; //Mouse button sprites (back button)
SDL_Rect gPauseButton[BUTTON_TOTAL]; //Mouse button sprites (pause button)
SDL_Rect gHelpButton[BUTTON_TOTAL]; //Mouse button sprites (help button)
SDL_Rect gContinueButton[BUTTON_TOTAL]; //Mouse button sprites (continue button)

SDL_Rect gCharacterClips[CHARACTER_RUNNING_FRAMES]; //running animation
SDL_Rect gAwardClips[AWARD_ROTATING_FRAMES]; //rotating animation
SDL_Rect gThreatClips[THREAT_FLYING_FRAMES]; //flying animation

LTexture gPlayButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gHelpButtonTexture;
LTexture gContinueButtonTexture;
LTexture gCharacterTexture;

LTexture gMenuTexture; // menu scene textures
LTexture gInstructionTexture; // instruction scene textures
LTexture gBackgroundTexture; //background scene textures
LTexture gGroundTexture; // ground scene textures
LTexture gLoseTexture[TOTAL_ENDING]; // lose scene textures

std::string ENDING[TOTAL_ENDING] = 
{
	"Image/background/Losegame1.png",
	"Image/background/Losegame2.png",
	"Image/background/Losegame3.png",
	"Image/background/Losegame4.png",
	"Image/background/Losegame5.png",
};

LTexture gText1Texture; 
LTexture gText2Texture;
LTexture gText3Texture;
LTexture gRoadTexture;
LTexture gScoreTexture;
LTexture gLifeTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);

Character character; //the character of the game

Mix_Music* gMusic = nullptr; //The music that will be played
Mix_Music* gMenuMusic = nullptr; //The music that will be played
Mix_Music* gEndMusic = nullptr ; //The music that will be played
Mix_Chunk* gClick = nullptr; //The sound effects that will be used
Mix_Chunk* gJump = nullptr; //The sound effects that will be used
Mix_Chunk* gLose = nullptr; //The sound effects that will be used
Mix_Chunk* gCongrats = nullptr; //The sound effects that will be used
Mix_Chunk* gCollision = nullptr; //The sound effects that will be used

SDL_Color textColor = { 255, 55, 40 };

bool Init()  //Starts up SDL and creates window
{
	bool Init = true;  //Initialization flag
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //Initialize SDL
	{
		Init = false;
		std::cout << "Can not initialize SDL." << std::endl;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) //Set texture filtering to linear
		{
			Init = false;
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}
		gWindow = SDL_CreateWindow("Running dinasour on the beach", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //Create window
		if (gWindow == NULL)
		{
			Init = false;
			std::cout << "Can not create window" << std::endl ;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Create vsynced renderer for window
			if (gRenderer == NULL)
			{
				Init = false;
				std::cout << "Can not create renderer" << std::endl ;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //Initialize renderer color
				int imgFlags = IMG_INIT_PNG; //Initialize PNG loading
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					Init = false;
					std::cout << "Can not initialize SDL_image" << std::endl ;
				}
				if (TTF_Init() == -1) //Initialize true type font
				{
					Init = false;
					std::cout << "SDL_ttf could not initialize!" << std::endl;					
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) //Initialize SDL_mixer
				{
					Init = false;
					std::cout << "SDL_mixer could not initialize!" << std::endl;					
				}
			}
		}
	}
	return Init;
}

bool LoadMedia() 
{
	bool LoadMedia = true; //Loading flag
    
	gMenuMusic = Mix_LoadMUS("Sound_Music/MainMusic.wav"); //loading the main music
	if (gMenuMusic == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load menu music" << std::endl;
	}
	gMusic = Mix_LoadMUS("Sound_Music/BackgroundMusic.wav"); //loading the background music
	if (gMusic == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load background music" << std::endl ;
	}
    gEndMusic = Mix_LoadMUS("Sound_Music/Endgame.wav"); //loading the end game music
	if (gEndMusic == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load end game music" << std::endl ;
	}

	if (!gMenuTexture.LoadFromFile("Image/background/menu.png", gRenderer)) //load menu image (Load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load menu image" << std::endl;
	}
	if (!gInstructionTexture.LoadFromFile("Image/background/instruction.png", gRenderer)) //load instruction image (Load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load instruction image" << std::endl;
	}

    gClick = Mix_LoadWAV("Sound_Music/mouse_click.wav"); //loading the sound of clicking mouse
	if (gClick == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load mouse click sound" << std::endl;
	}
	gJump = Mix_LoadWAV("Sound_Music/jump_sound.wav"); //loading the sound of jumping
	if (gJump == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load jumping sound" << std::endl;
	}
	gCollision = Mix_LoadWAV("Sound_Music/collision_sound.wav"); //loading the sound of collision
	if (gCollision == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load collision sound" << std::endl;
	}
	gCongrats = Mix_LoadWAV("Sound_Music/Congratulation.wav"); //loading the sound of congratulation when you receive award
	if (gCongrats == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load congratulation sound" << std::endl;
	}
	gLose = Mix_LoadWAV("Sound_Music/lose_sound.wav"); //loading the sound when players lose
	if (gLose == nullptr)
	{
		LoadMedia = false;
		std::cout << "Can not load lose sound" << std::endl;
	}

	if (!gPlayButtonTexture.LoadFromFile("Image/button/play_button.png", gRenderer)) //load big play button image (Load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load play button image" << std::endl;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gPlayButton[i].x = 150 * i;
			gPlayButton[i].y = 0;
			gPlayButton[i].w = 150;
			gPlayButton[i].h = 98;
		}
	}
	if (!gHelpButtonTexture.LoadFromFile("Image/button/help_button.png", gRenderer)) // load help button (Load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load help button image" << std::endl;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gHelpButton[i].x = 150 * i;
			gHelpButton[i].y = 0;
			gHelpButton[i].w = 150;
			gHelpButton[i].h = 98;
		}
	}
	if (!gBackButtonTexture.LoadFromFile("Image/button/back_button.png", gRenderer))  //load back button (load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load back button image" << std::endl;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gBackButton[i].x = 100 * i;
			gBackButton[i].y = 0;
			gBackButton[i].w = 100;
			gBackButton[i].h = 78;
		}
	}
	if (!gExitButtonTexture.LoadFromFile("Image/button/exit_button.png", gRenderer)) //load exit button (load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load exit button image" << std::endl;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gExitButton[i].x = 150 * i;
			gExitButton[i].y = 0;
			gExitButton[i].w = 150;
			gExitButton[i].h = 98;
		}
	}
	if (!gPauseButtonTexture.LoadFromFile("Image/button/pause_button.png", gRenderer)) //load pause button (load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load pause button image " << std::endl;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gPauseButton[i].x = 22 * i;
		    gPauseButton[i].y = 0;
			gPauseButton[i].w = 22;
		    gPauseButton[i].h = 34;
		}
	}
	if (!gContinueButtonTexture.LoadFromFile("Image/button/continue_button.png", gRenderer)) //load continue button (load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load continue button image " << std::endl;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gContinueButton[i].x = 22 * i;
			gContinueButton[i].y = 0;
			gContinueButton[i].w = 22;
			gContinueButton[i].h = 34;
		}
	}

	if (!gCharacterTexture.LoadFromFile("Image/character/char.png", gRenderer)) //load character image(Load sprite sheet texture)
	{
		LoadMedia = false;
		std::cout << "Can not load character running image." << std::endl;
	}
	else //Set sprite clips
	{
		gCharacterClips[0].x = 57 * 0;
		gCharacterClips[0].y = 0;
		gCharacterClips[0].w = 57;
		gCharacterClips[0].h = 57;

	    gCharacterClips[1].x = 57 * 1;
		gCharacterClips[1].y = 0;
	    gCharacterClips[1].w = 57;
	    gCharacterClips[1].h = 57;

		gCharacterClips[2].x = 57 * 2;
		gCharacterClips[2].y = 0;
		gCharacterClips[2].w = 57;
		gCharacterClips[2].h = 57;

		gCharacterClips[3].x = 57 * 3;
		gCharacterClips[3].y = 0;
		gCharacterClips[3].w = 57;
		gCharacterClips[3].h = 57;

		gCharacterClips[4].x = 57 * 4;
		gCharacterClips[4].y = 0;
		gCharacterClips[4].w = 57;
		gCharacterClips[4].h = 57;

		gCharacterClips[5].x = 57 * 5;
		gCharacterClips[5].y = 0;
		gCharacterClips[5].w = 57;
		gCharacterClips[5].h = 57;
	}
    if (!gBackgroundTexture.LoadFromFile("Image/background/layer.png", gRenderer)) //load ground image (load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load ground image" << std::endl;
	}

	if (!gGroundTexture.LoadFromFile("Image/background/ground.png", gRenderer)) //load ground image (load sprites)
	{
		LoadMedia = false;
		std::cout << "Can not load ground image" << std::endl;
	}

	for(int i = 0 ; i < TOTAL_ENDING ; i++) //load image when player loses (load sprites)
	{
		if(!gLoseTexture[i].LoadFromFile(ENDING[i],gRenderer))
		{
			LoadMedia = false;
			std::cout << "Can not load lose image." << std::endl;
		}
	}

	gFont = TTF_OpenFont("font/pixel_font.ttf", 30);  //Open the font
	if (gFont == NULL)
	{
		LoadMedia = false;
		std::cout << "Can not load font" << std::endl ;
	}
	else
	{
		if (!gText1Texture.LoadFromRenderedText("Your journey: ", gFont, textColor, gRenderer)) //Render text
	    {
			LoadMedia = false;
			std::cout << "Can not render the first texture - journey " << std::endl;
	    }
		if (!gText2Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer)) //Render text
	    {
			LoadMedia = false;
			std::cout << "Can not render the second texture - score" << std::endl;
	    }
		if (!gText3Texture.LoadFromRenderedText("Your life: ", gFont, textColor, gRenderer)) //Render text
	    {
			LoadMedia = false;
			std::cout << "Can not render the third texture - life" << std::endl;
	    }
	}
	return LoadMedia;
}

Close() 
{
	gMenuTexture.Free(); //Free loaded images
	gInstructionTexture.Free(); 
	gCharacterTexture.Free(); 
	gGroundTexture.Free(); 
	gPlayButtonTexture.Free(); 
	gHelpButtonTexture.Free(); 
	gExitButtonTexture.Free(); 
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free(); 
	gContinueButtonTexture.Free(); 
	gBackgroundTexture.Free();
	for(int i = 0 ; i < TOTAL_ENDING ; i++)
	{
		gLoseTexture[i].Free() ;
	}

	gText1Texture.Free();
	gText2Texture.Free();
	gText3Texture.Free();
	gRoadTexture.Free();
	gLifeTexture.Free();
	gScoreTexture.Free();

	Mix_FreeMusic(gMusic); //Free the music
	Mix_FreeMusic(gEndMusic) ; //Free the music
	Mix_FreeMusic(gMenuMusic); //Free the music

	gMusic = nullptr;
	gEndMusic = nullptr ;
	gMenuMusic = nullptr;

	Mix_FreeChunk(gClick); //Free the sound effect
	Mix_FreeChunk(gLose);  //Free the sound effect
	Mix_FreeChunk(gJump);  //Free the sound effect
	Mix_FreeChunk(gCongrats);  //Free the sound effect
	Mix_FreeChunk(gCollision);  //Free the sound effect

	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;
	gCongrats = nullptr;
	gCollision = nullptr;

	SDL_DestroyRenderer(gRenderer); //Destroy window	
	SDL_DestroyWindow(gWindow); 	
	gRenderer = nullptr;
	gWindow = nullptr;

	IMG_Quit(); //Quit SDL subsystems
	Mix_Quit(); //Quit SDL subsystems 
	SDL_Quit(); //Quit SDL subsystems
}