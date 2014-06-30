


/******************************************************************************
* Project Name	: SdlGame
* Purpose				: Study about using SDL Lib to Make Game2D in C++
* Written				: Damme88 (Passion88) 
* Role					: Software -Communication and Electronic Engineering
* Time          : 2014-06-30
* Os and Tool		: Visual studio 2010 (VSC++) and Windows 7 ultimate x86
* CopyRight			: Passion Lab
*******************************************************************************/

#include "Object.h"
#include "Threats.h"
#include "Amo.h"

#define FAILED -1
#define SUCCESS 0
const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kBPP = 32;

// define global variable
SDL_Surface* gScreen = NULL;
SDL_Surface* gBackGround = NULL;
SDL_Surface* gObject = NULL;
SDL_Surface* gThreats = NULL;
SDL_Surface* gAmo = NULL;
SDL_Event gEvent;
Mix_Music* gMusic = NULL;
Mix_Chunk* gMusicAmo = NULL;

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
	SDL_FreeSurface(gThreats);
	SDL_FreeSurface(gObject);
	SDL_FreeSurface(gBackGround);
	Mix_FreeMusic(gMusic);
	Mix_FreeChunk(gMusicAmo);
	Mix_CloseAudio();
	SDL_Quit();
}

void ApplySurface(int x, int y, SDL_Surface* src, SDL_Surface* dest) {
  SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, dest, &offset);
}

int main(int arc, char* argv[]) {
	int bkgn_x = 0;
	int bkgn_y = 0;

	bool is_quit = false;
	ObjectGame object;
	Threats* Threats1 = new Threats(650, 280);
	Threats* Threats2 = new Threats(950, 100);
	Amo *amo = new Amo(object.GetBounding().x + 45, object.GetBounding().y);

	SDL_Rect fraction;
	fraction.x = 200;
	fraction.y = 200;
	fraction.w = 20;
	fraction.h = 50;

	if (!InitSdl())
	{
		return FAILED;
	}
	gBackGround = LoadImages("background.bmp");
	if (gBackGround == NULL)
	{
		return FAILED;
	}

	gMusic = Mix_LoadMUS("Action.mid");
	if (gMusic == NULL)
	{
		return FAILED;
	}

	gMusicAmo = Mix_LoadWAV("Laser.wav");
	if (gMusicAmo == NULL)
	{
		return FAILED;
	}

	gObject = LoadImages("object.bmp");
	if (gObject == NULL) {
		return FAILED;
	}

	gThreats = LoadImages("threats.bmp");
	if (gThreats == NULL) {
		return FAILED;
	}
	gAmo = LoadImages("amo.bmp");
	if (gAmo == NULL) {
		return FAILED;
	}

	while(!is_quit) {
		while(SDL_PollEvent(&gEvent)) {
			if(gEvent.type == SDL_QUIT) {
				is_quit = true;
			}
		   object.HandleAction(gEvent);

			 amo->HandleAction(gEvent, object.GetBounding(), gMusicAmo);
		}

		if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			if( Mix_PlayMusic(gMusic, -1 ) == FAILED )
			{
				return FAILED;
			}
		}

		bkgn_x -= 1;
		if (bkgn_x <= - gBackGround->w)
		{
			bkgn_x = 0;
		}

	  ApplySurface(bkgn_x, bkgn_y, gBackGround, gScreen);
		ApplySurface(bkgn_x + gBackGround->w, bkgn_y, gBackGround, gScreen);

		object.ShowObject(gObject, gScreen);
		object.HandleMove(kScreenWidth, kScreenHeight, fraction);

		Threats1->ShowThreats(gThreats, gScreen);
		Threats2->ShowThreats(gThreats, gScreen);

		Threats1->HandleMove(kScreenWidth, kScreenHeight, fraction);
		Threats2->HandleMove(kScreenWidth, kScreenHeight, fraction);

		if (amo->IsMove()) {
		  amo->Show(gAmo, gScreen);
		  amo->Move(kScreenWidth, kScreenHeight, fraction);
		}

		if ( SDL_Flip(gScreen) == FAILED)
			return FAILED;
	}

	delete Threats1;
	delete Threats2;
	delete amo;
	CleanUp();
  return 0;
}