
//Copyright: Phattrienphanmem123az.com
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "BaseObject.h"

//#define USE_AUDIO


static  SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;

static SDL_Event g_event;
static Mix_Music* g_music = NULL;
static Mix_Chunk* g_sound_bullet[3];
static Mix_Chunk* g_sound_explosion = NULL;
static Mix_Chunk* g_sound_ex_main = NULL;

static char g_name_audio_bullet_main1[] = {"sound//Fire.wav"};
static char g_name_audio_bullet_main2[] = {"sound//Laser.wav"};
static char g_name_audio_ex_main[]      = {"sound//Explosion+1.wav"};
static char g_name_audio_ex_threats[]   = {"sound//Bomb1.wav"};

static char g_name_threat_left[] = { "img//thread1_left.png" };
static char g_name_threat_right[] = { "img//thread1_right.png" };

static char g_threat_bullet[] = { "img//bullet_threat.png" };
static char g_plane_bullet[] = { "img//plane_bullet.png" };

static char g_name_sound_increase[] = { "sound//two_beep_.wav" };
static char g_name_money[] = { "img//money_img.png" };

static char g_name_main_alive[] = {"img//player_pw.png"};


const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0XFF;

#define PT_FAILED -1
#define PT_SUCCESS 0

#define TILE_SIZE 64
#define BLANK_TILE 0

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 19
#define  STATE_MONEY2 24

//Screen
const int FRAMES_PER_SECOND = 20;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 2;

typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height) {left_ = left; top_ = top; width_ = width; height_ = height;}
    int left_;
    int top_;
    int width_;
    int height_;
};

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b) {red_ = r, green_ = g, blue_ = b;}
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

typedef struct Input
{
  int left_;
  int right_;
  int up_;
  int down_;
  int jump_;
} Input;

typedef struct Map
{
  int start_x_;
  int start_y_;
  int max_x_;
  int max_y_;
  int tile[MAX_MAP_Y][MAX_MAP_X];
  char* file_name_;
} Map;

namespace SDLCommonFunc
{
  int GetMax(const int& a, const int& b);
  int GetMin(const int& a, const int& b);
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
  int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font);
}

#endif