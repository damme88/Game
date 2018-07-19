
#include "common_function.h"


int SDLCommonFunc::ShowMenu(SDL_Surface* g_screen, TTF_Font* font) 
{
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
  pos[0].x = (g_screen->clip_rect.w/2) - (menu[0]->clip_rect.w/2);
  pos[0].y = (g_screen->clip_rect.h/2) - (menu[0]->clip_rect.h);
  pos[1].x = (g_screen->clip_rect.w/2) - (menu[0]->clip_rect.w/2);
  pos[1].y = (g_screen->clip_rect.h/2) + (menu[0]->clip_rect.h);

  SDL_FillRect(g_screen, &g_screen->clip_rect, SDL_MapRGB(g_screen->format, 0x00, 0x00, 0x00));
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
      SDL_BlitSurface(menu[i], NULL, g_screen, &pos[i]);
    }

    SDL_Flip(g_screen);
    if (1000/30 > (SDL_GetTicks() -time))
      SDL_Delay(1000/30 - (SDL_GetTicks() - time));
  }
}



int SDLCommonFunc::MakeRandomPostY()
{
  int ran_y = rand();
  ran_y = ran_y%400;
  if (ran_y > SCREEN_HEIGHT - 200)
  {
    ran_y = SCREEN_HEIGHT*0.5;
  }
  return ran_y;
}

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
  SDL_Surface *load_image = NULL;
  SDL_Surface *optimize_image = NULL;

  load_image = IMG_Load(file_path.c_str());
  if (load_image != NULL) 
  {
    optimize_image = SDL_DisplayFormat(load_image);
    SDL_FreeSurface(load_image);

    if (optimize_image != NULL) 
    {
      UINT32 color_key = SDL_MapRGB(optimize_image->format, 167, 175, 180);
      SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
    }
  }

  return optimize_image;
}

void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y) 
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(src, NULL, des, &offset);
}

void SDLCommonFunc::ApplySurface2(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) 
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(source, clip, destination, &offset);
}


bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) 
{
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
  
  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}



void SDLCommonFunc::CleanUp() 
{
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
  Mix_FreeChunk(g_sound_bullet[0]);
  Mix_FreeChunk(g_sound_bullet[1]);
  Mix_FreeChunk(g_sound_explosion);
  Mix_FreeChunk(g_sound_ex_main);
}

void SDLCommonFunc::TestFuncion()
{
  int a = 9;
  int b = 10;
}

int SDLCommonFunc::TestFunctionGame()
{
  int a = 5;
  int b = 7;
  int c = 8;
  return 1;
}

void SDLCommonFunc::TestFunction3()
{
  float a = 0.0;
  float b= 1.0;
}