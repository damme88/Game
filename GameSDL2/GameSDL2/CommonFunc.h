
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

//#define MACRO
#define VT(T) std::vector<T>

static  SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;

static SDL_Event g_event;

static char sRectKey[] = { "img//sman_rect.png" };
static char sTriangleKey[] = { "img//sman_triangle.png" };
static char sCircleKey[] = { "img//sman_circle.png" };
static char sXKey[] = { "img//sman_x.png" };


static char sRightControl[] = { "img//sman_right_ctrl.png" };
static char sLeftControl[] = { "img//sman_left_ctrl.png" };
static char sUpControl[] = { "img//sman_up_ctrl.png" };
static char sDownControl[] = { "img//sman_down_ctrl.png" };

static char g_name_threat_left[] = { "img//thread1_left.png" };
static char g_name_threat_right[] = { "img//thread1_right.png" };

static char g_threat_bullet[] = { "img//bullet_threat.png" };
static char g_plane_bullet[] = { "img//plane_bullet.png" };


static char g_name_money[] = { "img//sman_coin_num.png" };

static char g_name_main_alive[] = {"img//sman_live.png"};


const int COLOR_KEY_R = 125;
const int COLOR_KEY_G = 125;
const int COLOR_KEY_B = 125;

const int RENDER_DRAW_COLOR = 0XFF;

#define GRAVITY_SPEED       1.0
#define MAX_FALL_SPEED      15

#define PT_FAILED -1
#define PT_SUCCESS 0

#define TILE_SIZE 64
#define BLANK_TILE "0"

#define MAX_MAP_X 200
#define MAX_MAP_Y 10

//Screen
const int FRAMES_PER_SECOND = 25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 2;

//ground pos

const int GROUND_POS = SCREEN_HEIGHT - 4*TILE_SIZE;

typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height) 
    { 
        left_ = left; top_ = top; 
        width_ = width; 
        height_ = height;
    }
    int left_;
    int top_;
    int width_;
    int height_;
};

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b) 
    {
        red_ = r;
        green_ = g; 
        blue_ = b;
    }

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

namespace SDLCommonFunc
{
  int GetMax(const int& a, const int& b);
  int GetMin(const int& a, const int& b);
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
  bool CheckInsideMapX(UINT x1, UINT x2);
  bool CheckInsideMapY(UINT y1, UINT y2);
  bool CheckInsideMap(UINT x, UINT y);
  std::vector<std::string> SplitBySpace(const std::string& sData);
}

#endif