#include "LTexture.h"

LTexture::LTexture() //Initialize variables
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() //Deallocates memory
{
	Free();
}

void LTexture::Free() //Free texture if it exists
{
	if (mTexture != NULL)
	{
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) //Modulate texture rgb
{ 
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ) //Set blending function
{
	SDL_SetTextureBlendMode( mTexture, blending );
}
void LTexture::setAlpha( Uint8 alpha ) //Modulate texture alpha
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

bool LTexture::LoadFromRenderedText(std::string textureText,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer) //Creates image from font string
{
	Free(); //Get rid of preexisting texture
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor); //Render text surface
	if (textSurface == NULL) 
	{
		std::cout << "Unable to render text surface!" << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface); //Create texture from surface pixels
		if (mTexture == NULL) 
		{
			std::cout << "Unable to create texture from rendered text!" << std::endl;
		}
		else
		{
			mWidth = textSurface->w; //Get image dimensions
			mHeight = textSurface->h; //Get image dimensions
		}
		SDL_FreeSurface(textSurface); //Get rid of old surface
	}
	return mTexture != NULL; //Return success
}

bool LTexture::LoadFromFile(std::string path, SDL_Renderer *gRenderer)  //Loads image at specified path
{
	Free(); //Get rid of preexisting texture
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
			mWidth = loadedSurface->w; //Get image dimensions
			mHeight = loadedSurface->h; //Get image dimensions
		}
		SDL_FreeSurface(loadedSurface); //Get rid of old loaded surface
	}
	mTexture = newTexture; //return success
	return mTexture != nullptr;
}

void LTexture::Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip) //Renders texture at given point
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight }; //Set rendering space and render to screen
	if (clip != nullptr) //Set clip rendering dimensions
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::GetWidth() //Gets image dimensions
{
	return mWidth;
}

int LTexture::GetHeight() //Gets image dimensions
{
	return mHeight;
}
