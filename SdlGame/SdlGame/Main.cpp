


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
#include "Log.h"

#define FAILED -1
#define SUCCESS 0
const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kBPP = 32;
const int kPlayTime = 60;
const int kFramePerSecond = 20;
const int a = 5;
const int b = 8;
const int c = 9;

// define global variable
SDL_Surface* gScreen = NULL;
SDL_Surface* gBackGround = NULL;
SDL_Surface* gObject = NULL;
SDL_Surface* gObjectDestroy = NULL;
SDL_Surface* gThreats = NULL;
SDL_Surface* gAmo[3];
SDL_Event gEvent;
Mix_Music* gMusic = NULL;
Mix_Chunk* gMusicAmo[3];
Mix_Chunk* gMusicBom = NULL;
TTF_Font* gfont = NULL;
TTF_Font* gFontTime = NULL;
SDL_Surface* gTimeSecond = NULL;
SDL_Surface* gMark = NULL;
SDL_Color gTextColor = {0x00, 0x00, 0x00};
SDL_Color gTextColormark = {0xFF, 0x00, 0x00};
LogInfo::Log gLog;
bool gColobj = false;

SDL_Surface* LoadImages(const char* image_path);

int ShowMenu(SDL_Surface* gscreen, TTF_Font* font) {
	int time = 0;
	int x = 0;
	int y = 0;
	const int kMenuNum = 2;
	const char* labels[kMenuNum] = {"Start Game", "Exit"};
	SDL_Surface* menu [kMenuNum];
	bool selected[kMenuNum] = {0, 0};
	SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};
	menu[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menu[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	SDL_Rect pos[kMenuNum];
	pos[0].x = (gScreen->clip_rect.w/2) - (menu[0]->clip_rect.w/2);
	pos[0].y = (gScreen->clip_rect.h/2) - (menu[0]->clip_rect.h);
	pos[1].x = (gScreen->clip_rect.w/2) - (menu[0]->clip_rect.w/2);
	pos[1].y = (gScreen->clip_rect.h/2) + (menu[0]->clip_rect.h);

	SDL_FillRect(gScreen, &gScreen->clip_rect, SDL_MapRGB(gScreen->format, 0x00, 0x00, 0x00));
	SDL_Event event;
	while(1) {
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				SDL_FreeSurface(menu[0]);
				SDL_FreeSurface(menu[1]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < kMenuNum; ++i)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
							y >= pos[i].y && y <= pos[i].y + pos[i].h) {
						if (!selected[i]) {
							selected[i] = 1;
							SDL_FreeSurface(menu[i]);
							menu[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					} else {
							if (selected[i]) {
								selected[i] = 0;
								SDL_FreeSurface(menu[i]);
								menu[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
							}
					}
				}
				break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					for (int i = 0; i < kMenuNum; ++i) {
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
							y >= pos[i].y && y <= pos[i].y + pos[i].h) {
								SDL_FreeSurface(menu[0]);
								SDL_FreeSurface(menu[1]);
								return i;
						} 
					}
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym = SDLK_ESCAPE) {
						SDL_FreeSurface(menu[0]);
						SDL_FreeSurface(menu[1]);
						return 0;
					}
			}
		}

	for (int i = 0; i < kMenuNum; ++i) {
		SDL_BlitSurface(menu[i], NULL, gScreen, &pos[i]);
	}
	SDL_Flip(gScreen);
	if (1000/30 > (SDL_GetTicks() -time))
		SDL_Delay(1000/30 - (SDL_GetTicks() - time));
	}
}


bool InitSdl() {
  // Init every thing for SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == FAILED)
	{
		gLog.WriteLog("Init Sdl Failed");
		return false;
  }
		gLog.WriteLog("Init Sdl Success");
	// Make video mode for screen
	Uint32 flag = SDL_SWSURFACE;
	if (MessageBox(NULL, "Would you like FullScreen", "Info", MB_YESNO|MB_ICONINFORMATION) == IDYES) {
		flag = SDL_SWSURFACE | SDL_FULLSCREEN;
	}
	gScreen = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kBPP, flag);
	if (gScreen == NULL)
	{
		gLog.WriteLog("Init video mode failed");
		return false;
	}
	gLog.WriteLog("Init video mode success");

	if (TTF_Init() == FAILED)
	{
			gLog.WriteLog("Init font TTF failed");
		 return FAILED;
	}
	gLog.WriteLog("Init font TTF Success");

	// Init audio mode
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == FAILED) {
		gLog.WriteLog("Setup audio Failed");
		return false;
	}
  gLog.WriteLog("setup audio Success");

	SDL_WM_SetCaption("Mighty Aircraft", NULL);

	SDL_Surface* icon;
	icon = LoadImages("icon.bmp");
	SDL_WM_SetIcon(icon, NULL);

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
	SDL_FreeSurface(gTimeSecond);
	Mix_FreeMusic(gMusic);
	Mix_FreeChunk(gMusicAmo[0]);
	Mix_FreeChunk(gMusicAmo[1]);
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
	Uint32 start = 0;
	Uint32 sub_time = 0;
	bool is_running = true;
	int mark = 0;
	int bkgn_x = 0;
	int bkgn_y = 0;
	bool is_quit = false;
	ObjectGame object;
	Threats* Threats1 = new Threats(650, 280);
	Threats* Threats2 = new Threats(950, 100);
	Amo *amo = new Amo(object.GetBounding().x + 45, object.GetBounding().y);
	Timer times;

	if (!InitSdl())
	{
		return FAILED;
	}
	gBackGround = LoadImages("background.bmp");
	if (gBackGround == NULL)
	{
		gLog.WriteLog("Load Background failed");
		return FAILED;
	}
	gLog.WriteLog("Load Background Success");

	gMusic = Mix_LoadMUS("Action.mid");
	if (gMusic == NULL)
	{
		gLog.WriteLog("Load Music menu failed");
		return FAILED;
	}
	gLog.WriteLog("Load Music menu success");


	gMusicAmo[0] = Mix_LoadWAV("Laser.wav");
	gMusicAmo[1] = Mix_LoadWAV("Fire1.wav");
	gMusicBom = Mix_LoadWAV("bomb-03.wav");
	if (gMusicAmo[0] == NULL || gMusicAmo[1] == NULL || gMusicBom == NULL)
	{
		gLog.WriteLog("Load Amo Music failed");
		return FAILED;
	}
	gLog.WriteLog("Load Amo Music success");


	gObject = LoadImages("object.bmp");
	gObjectDestroy = LoadImages("destroy.bmp");
	if (gObject == NULL || gObjectDestroy == NULL) {
		gLog.WriteLog("Load Object image failed");
		return FAILED;
	}
	gLog.WriteLog("Load Object image success");


	gThreats = LoadImages("threats.bmp");
	if (gThreats == NULL) {
		gLog.WriteLog("Load threats image failed");
		return FAILED;
	}
	gLog.WriteLog("Load threats image success");

	gAmo[0] = LoadImages("amo_laser.bmp");
	gAmo[1] = LoadImages("amo_sphere.bmp");
	//gAmo[2] = LoadImages("amo_lightning.bmp");
	if (gAmo[0] == NULL || gAmo[1] == NULL) {
		gLog.WriteLog("Load amo image failed");
		return FAILED;
	}
  gLog.WriteLog("Load amo image success");


	gfont = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 40);
	gFontTime = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 20);
	if (gfont == NULL || gFontTime == NULL)
	{
	  gLog.WriteLog("Load font failed");
		return FAILED;
	}


	gLog.WriteLog("Load font image success");

	int ret = ShowMenu(gScreen, gfont);
	if (ret == 1) 
		is_quit = true;
	while(!is_quit) {
		times.Start();
		while(SDL_PollEvent(&gEvent)) {
			switch (gEvent.type) {
			case SDL_QUIT:
				mark = 0;
				is_quit = true;
				break;
			case SDL_KEYDOWN:
				switch(gEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE: {
						mark = 0;
						int i = ShowMenu(gScreen, gfont);
						if (i == 0)
							is_quit = false;
						else {
							delete Threats1;
							delete Threats2;
							delete amo;
							CleanUp();
							return 0;
						}
					}
					break;
				case SDLK_s: 
					if (is_running) {
						is_running = false;
					} else {
						is_running = true;
						start = (SDL_GetTicks()/1000) - sub_time;
					}
					break;
				}
				break;
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

		bkgn_x -= 2;
		if (bkgn_x <= - gBackGround->w)
		{
			bkgn_x = 0;
		}

	  ApplySurface(bkgn_x, bkgn_y, gBackGround, gScreen);
		ApplySurface(bkgn_x + gBackGround->w, bkgn_y, gBackGround, gScreen);

		if (gColobj == false) {
			object.ShowObject(gObject, gScreen);
		} else {
			if( Mix_PlayChannel( -1, gMusicBom, 0 ) == -1 )
				return FAILED;
			object.ShowObject(gObjectDestroy, gScreen);
			if ( SDL_Flip(gScreen) == FAILED)
				return FAILED;
			SDL_Delay(4000);
			if (MessageBox(NULL, "Game Over", "Info", MB_OK|MB_ICONSTOP) == IDOK) {
				delete Threats1;
				delete Threats2;
				delete amo;
				CleanUp();
				return 0;
			}
		}

		if (amo->IsMove()) {
			switch (amo->GetAmoType()) {
			case Amo::AmoType::LASER:
				amo->Show(gAmo[0], gScreen);
				break;
			case Amo::AmoType::SPHERE:
				amo->Show(gAmo[1], gScreen);
					break;
			default:
				amo->Show(gAmo[0], gScreen);
					break;
			}
		  amo->Move(kScreenWidth, kScreenHeight);
		}

		object.HandleMove(kScreenWidth, kScreenHeight);

		if (Threats1->IsCollison() == false) {
			Threats1->ShowThreats(gThreats, gScreen);
			Threats1->HandleMove(kScreenWidth, kScreenHeight, amo->GetBounding(), object.GetBounding(), gColobj);
		} else {
				mark++;
				Threats1->SetIsCollision(false);
				Threats1->SetPosAgain(kScreenWidth, kScreenHeight);
		}

		if (Threats2->IsCollison() == false) {
			Threats2->ShowThreats(gThreats, gScreen);
			Threats2->HandleMove(kScreenWidth, kScreenHeight, amo->GetBounding(), object.GetBounding(), gColobj);
		} else {
			mark++;
			Threats2->SetIsCollision(false);
			Threats2->SetPosAgain(kScreenWidth, kScreenHeight);
		}

		// Show time 
		std::stringstream timestr;
		if (is_running) {
			sub_time = (SDL_GetTicks()/1000) - start;
		}
		timestr << "Time: " << kPlayTime - sub_time;

		if (kPlayTime - sub_time < 15) {
			gTextColor.r = 0xFF;
			gTextColor.g = 0x00;
			gTextColor.b = 0x00;
		}

		if (kPlayTime - sub_time <= 0) {
			is_running = false;
			if (MessageBox(NULL, "Time has been finished, Game Over", "Info", MB_OK|MB_ICONSTOP) == IDOK) {
				is_quit = true;
			}
		}

		gTimeSecond = TTF_RenderText_Solid(gFontTime, timestr.str().c_str(), gTextColor);
		ApplySurface(500, 10, gTimeSecond, gScreen);

		char str[10];
		itoa(mark, str, 10);
		std::string strMark("Mark : ");
		strMark += (std::string)str;
		gMark = TTF_RenderText_Solid(gFontTime, strMark.c_str(), gTextColormark);
		ApplySurface(20, 10, gMark, gScreen);

		if ( SDL_Flip(gScreen) == FAILED)
			return FAILED;

		if (times.GetTick() < 300/kFramePerSecond) {
			SDL_Delay((300/kFramePerSecond) - times.GetTick());
		}
	}

	delete Threats1;
	delete Threats2;
	delete amo;
	CleanUp();
  return 0;
}