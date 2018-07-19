
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#define FAILED -1
#define SUCCESS 0

const int FRAMES_PER_SECOND = 25;

// Screen
const int WIDHT_BKGROUND = 4800;
const int HEIGH_BKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 2;

//Main Object
const int POS_X_START_MAIN_OBJECT = 100;
const int POS_Y_TART_MAIN_OBJECT = 200;
const int SPEED_MAIN_OBJECT = 20;

//Threats
const int NUM_THREATS = 3;
const int VAL_OFFSET_START_POST_THREAT = 400;
const int SPEED_THREAT = 5;

//Bullet Object
const int SPEED_BULLET_MAIN_OBJECT = 40;
const int SPEED_BULLET_THREATS_OBJECT = 20;

static  SDL_Surface *g_screen = NULL;
static  SDL_Surface *g_bkground = NULL;
static  SDL_Event g_even;

//Audio
static Mix_Chunk* g_sound_bullet[3];
static Mix_Chunk* g_sound_explosion = NULL;
static Mix_Chunk* g_sound_ex_main = NULL;

//Name Main
static char g_name_main[]               = {"pl0.png"};
static char g_name_main1[]              = {"pl1.png"};
static char g_name_explosion_main[]     = {"exp_main.png"};
static char g_name_bullet_main_1[]      = {"laser.png"};
static char g_name_bullet_main_2[]      = {"sphere.png"};
static char g_name_audio_bullet_main1[] = {"Laser.wav"};
static char g_name_audio_bullet_main2[] = {"Fire1.wav"};
static char g_name_audio_ex_main[]      = {"Explosion+1.wav"};

//Name Threats
static char g_name_threats[]            = {"af2.png"};
static char g_name_bullet_threats[]     = {"sphere2.png"};
static char g_name_explosion_threat[]   = {"exp.png"};
static char g_name_audio_ex_threats[]   = {"Bomb1.wav"};

//Name Background
static char g_name_background[]         = {"bk10.png"};
static char g_string_caption[]          = {"Demo GAME C++ SDL Phat trien phan mem 123AZ"};

namespace SDLCommonFunc
{
  SDL_Surface* LoadImage(std::string file_path);
  void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
  void ApplySurface2(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL) ;
  void CleanUp();
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& other_object); 
  int MakeRandomPostY();
  int ShowMenu(SDL_Surface* g_screen, TTF_Font* font);
  void TestFuncion();
  int TestFunctionGame();
  void TestFunc2();
  void TestFunction3();
}

#endif//