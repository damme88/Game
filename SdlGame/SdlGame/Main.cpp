


/******************************************************************************
* Project Name	: SdlGame
* Purpose				: Study about using SDL Lib to Make Game2D in C++
* Written				: Damme88 (Passion88) 
* Role					: Software -Communication and Electronic Engineering
* Time          : 2014-06-30
* Os and Tool		: Visual studio 2010 (VSC++) and Windows 7 ultimate x86
* CopyRight			: Passion Lab
*******************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <Windows.h>
#include <string>

#define FAILED -1
#define SUCCESS 0
const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kBPP = 32;

// define global variable
SDL_Surface* gScreen = NULL;
SDL_Surface* gBackGround = NULL;
SDL_Event gEvent;
Mix_Music* gMusic = NULL;


bool InitSdl() {
  // Init every thing for SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == FAILED)
  {
		return false;
  }
	// Make video mode for screen
	gScreen = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kBPP, SDL_SWSURFACE);
	if (gScreen == NULL)
	{
		return false;
	}

	// Init audio mode
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == FAILED) {
		return false;
	}
	return true;
}


SDL_Surface* LoadImages(const char* image_path) {
		SDL_Surface* load_image = NULL;
		SDL_Surface* optimize_image = NULL;
		load_image = IMG_Load(image_path);
		if (load_image != NULL) {
			optimize_image = SDL_DisplayFormat(load_image);
			if (optimize_image != NULL)
			{
				SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, SDL_MapRGB((optimize_image->format), 0xFF, 0xFF, 0xFFF));
			}
		}
		return optimize_image;
}

void CleanUp() {
	SDL_FreeSurface(gScreen);
	SDL_Quit();
}

void ApplySurface(int x, int y, SDL_Surface* src, SDL_Surface* dest) {
  SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, dest, &offset);
}

int main(int arc, char* argv[]) {
	bool is_quit = false;
	if (!InitSdl())
	{
		return FAILED;
	}
	gBackGround = LoadImages("background.bmp");
	if (gBackGround == NULL)
	{
		return FAILED;
	}

	gMusic = Mix_LoadMUS("backsound.mid");
	if (gMusic == NULL)
	{
		return FAILED;
	}

	while(!is_quit) {
		while(SDL_PollEvent(&gEvent)) {
			if(gEvent.type == SDL_QUIT) {
				is_quit = true;
			}
		}
	  ApplySurface(0, 0, gBackGround, gScreen);

		if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			if( Mix_PlayMusic(gMusic, -1 ) == FAILED )
			{
				return FAILED;
			}
		}

		if ( SDL_Flip(gScreen) == FAILED)
			return 1;
	}
  return 0;
}