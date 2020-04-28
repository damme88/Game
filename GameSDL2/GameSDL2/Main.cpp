
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "game_map.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "BossObject.h"
#include "ThreatsAds.h"

TTF_Font* g_font = NULL;
TTF_Font* g_font_text = NULL;

//#define USE_THREAT_PLANE
#define USE_THREAT_SPACING
#define USE_THREAT_STATIC

bool LoadBackground();
void close();

BaseObject g_background;

BaseObject g_main_object;
const int WALKING_ANIMATION_FRAME = 4;
SDL_Rect g_sprite_clip[WALKING_ANIMATION_FRAME];
BaseObject g_sprite_texture;

bool InitData()
{
  bool success = true;
  int ret = SDL_Init( SDL_INIT_VIDEO);
  if(ret < 0) return false;


  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  
  //Create window
  g_window = SDL_CreateWindow("SDL 2.0 Game Demo - Phat Trien Phan Mem 123AZ",
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if(g_window == NULL )
  {
      success = false;
  }
  else
  {
      g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
      if (g_screen == NULL)
        success = false;
      else
      {
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) && imgFlags))
          success = false;
      }

      if (TTF_Init() == PT_FAILED)
      {
        success = false;
      }

      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == PT_FAILED) 
      {
        success = false;
      }

      g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main1);
      g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main2);
      g_sound_explosion = Mix_LoadWAV(g_name_audio_ex_main);
      g_sound_ex_main = Mix_LoadWAV(g_name_audio_ex_threats);

      if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_explosion == NULL)
      {
        return false;
      }

      g_font = TTF_OpenFont("font//ARCADE.ttf", 100);
      if (g_font == NULL)
      {
        return false;
      }

      g_font_text = TTF_OpenFont("font//ARCADE.ttf", 30);
      if (g_font_text == NULL)
      {
        return false;
      }
  }

  return success;
}


bool LoadBackground()
{
  bool ret = g_background.LoadImg("img//background.png", g_screen);
  if (ret == false)
  {
    return false;
  }

  return true;
}

void close()
{
  g_background.Free();

  SDL_DestroyRenderer(g_screen);
  g_screen = NULL;

  SDL_DestroyWindow(g_window);
  g_window = NULL;

  IMG_Quit();
  SDL_Quit();
}

int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if (InitData() == false)
  {
    return PT_FAILED;
  }

  g_music = Mix_LoadMUS("sound//Action.mid");
  if (g_music == NULL)
  {
    return 0;
  }
    ImpTimer fps;

   if(!LoadBackground())
   {
     return PT_FAILED;
   }

  GameMap* game_map = GameMap::GetInstance();

  game_map->LoadMap("map//map.dat");
  game_map->LoadMapTiles(g_screen);


   MainObject p_player;
   p_player.LoadImg(g_name_main_right, g_screen);
   p_player.InitExp(g_screen);

   PlayerPower player_power;
   player_power.Init(g_screen);


   PlayerMoney player_money;
   player_money.Init(g_screen);
   player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);

   TextObject time_game;
   time_game.setColor(TextObject::WHITE_TEXT);

   TextObject mark_game;
   mark_game.setColor(TextObject::WHITE_TEXT);

   TextObject money_count;
   money_count.setColor(TextObject::WHITE_TEXT);

   ThreatsAds pThreatAds;
   pThreatAds.BuildThreats(g_screen);

   //Init Boss Object
   BossObject bossObject;
   bossObject.LoadImg("img//boss_object.png", g_screen);
   int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
   bossObject.set_xpos(xPosBoss);
   bossObject.set_ypos(10);

   ExplosionObject exp_threats;
   ExplosionObject exp_main;

   bool ret = exp_threats.LoadImg("img//exp3.png", g_screen);
   if (!ret) return PT_FAILED;


   ret = exp_main.LoadImg("img//exp3.png", g_screen);
   if (!ret) return 0;

   bool quit = false;

   int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font);
   if (ret_menu == 1) 
     quit = true;


   unsigned int mark_value = 0;
   int num_die = 0;
   while(!quit)
   {
     fps.start();
      while( SDL_PollEvent(&g_event) != 0 )
      {
         if(g_event.type == SDL_QUIT )
         {
           quit = true;
         }

         p_player.HandleInputAction(g_event, g_screen, g_sound_bullet);
      }

#ifdef USE_AUDIO
      if( Mix_PlayingMusic() == 0 )
      {
        //Play the music
        if( Mix_PlayMusic(g_music, -1 ) == PT_FAILED )
        {
          return PT_FAILED;
        }
      }
#endif

       SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
       SDL_RenderClear(g_screen);

       g_background.Render(g_screen, NULL);

       //Map ga_map = game_map->GetMap();

       p_player.HandleBullet(g_screen);
       p_player.DoPlayer();
       p_player.Show(g_screen);
       game_map->DrawMap(g_screen);


       //Draw Geometric
       GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 40);
       ColorData color_data(36, 36, 36);
       Gemometric::RenderRectange(rectange_size, color_data, g_screen);

       GeometricFormat outlie_size(1, 1, SCREEN_WIDTH-1, 38);
       ColorData color_data1(255, 255, 255);
       Gemometric::RenderOutline(outlie_size, color_data1, g_screen);


       player_power.Show(g_screen);
       player_money.Show(g_screen);

       pThreatAds.Render(g_screen);
       bool bRet = pThreatAds.CheckCollision(g_screen, p_player.GetRectFrame(), true);
       if (bRet == true)
       {
           SDL_Rect rect_pos;
           rect_pos.x = p_player.GetRect().x;
           rect_pos.y = p_player.GetRect().y;
           rect_pos.w = p_player.get_frame_width();
           rect_pos.h = p_player.get_frame_height();
           exp_main.ImpRender(g_screen, rect_pos);


           num_die++;
           if (num_die <= 3)
           {
               p_player.SetRect(0, 0);
               p_player.set_think_time(60);
               SDL_Delay(1000);
               player_power.Decrease();
               player_power.Render(g_screen);
               continue;
           }
           else
           {
               if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
               {
                   pThreatAds.Free();
                   close();
                   SDL_Quit();
                   return 0;
               }
           }
       }

       //COLLISION THREAT -> Main Bullet
       std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
       for (int am = 0; am < bullet_arr.size(); am++)
       {
         BulletObject* p_bullet = bullet_arr.at(am);
         if (p_bullet)
         {
            bool bRet = pThreatAds.CheckCollision(g_screen, p_bullet->GetRect());
            if (bRet)
            {
                SDL_Rect rc_pos;
                rc_pos.x = p_bullet->GetRect().x;
                rc_pos.y = p_bullet->GetRect().y;
                rc_pos.w = p_bullet->GetRect().w;
                rc_pos.h = p_bullet->GetRect().h;
                exp_threats.ImpRender(g_screen, rc_pos);

                mark_value++;
                p_player.RemoveBullet(am);
            }
         }
       }

       //Show time for game
       std::string str_time = "Time: ";
       Uint32 time_val = SDL_GetTicks()/1000;
       Uint32 val_time = 300 - time_val;

       if (val_time <= 0)
       {
           if(MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
           {
               quit = true;
               break;
           }
       }
       else
       {
           std::string str_val = std::to_string(val_time);
           str_time += str_val;

           time_game.SetText(str_time);
           time_game.loadFromRenderedText(g_font_text, g_screen);
           time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
       }

       //Show mark value to screen
       std::string val_str_mark = std::to_string(mark_value);
       std::string strMark("Mark: ");
       strMark += val_str_mark;

       mark_game.SetText(strMark);
       mark_game.loadFromRenderedText(g_font_text, g_screen);
       mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

       int money_val = p_player.GetMoneyCount();
       std::string money_count_str = std::to_string(money_val);
       money_count.SetText(money_count_str);
       money_count.loadFromRenderedText(g_font_text, g_screen);
       money_count.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);


       if (p_player.GetMoneyCount() >= 100)
       {
           int reVal = p_player.GetMoneyCount() - 10;
           p_player.SetMoneyCount(reVal);

           player_power.InCrease();
           player_power.Render(g_screen);
       }


       ////Process Boss
       //int val = MAX_MAP_X*TILE_SIZE - (ga_map.start_x_ + p_player.GetRect().x);
       //if (val <= SCREEN_WIDTH)
       //{
       //    bossObject.SetMapXY(ga_map.start_x_, ga_map.start_y_);
       //    bossObject.DoPlayer(ga_map);
       //    bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
       //    bossObject.Show(g_screen);
       //}
       

       //Update screen
       SDL_RenderPresent(g_screen);


       //Cap the frame rate
       int val1 = fps.get_ticks();
       if(fps.get_ticks() < 1000/FRAMES_PER_SECOND)
       {
         SDL_Delay((1000/FRAMES_PER_SECOND ) - fps.get_ticks());
       }
  }

  pThreatAds.Free();
  close();
  return 0;
}