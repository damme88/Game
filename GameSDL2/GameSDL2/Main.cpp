
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
#include "MenuGame.h"
#include "OptionObject.h"
#include "EndObject.h"

TTF_Font* g_font_text = NULL;

//#define USE_THREAT_PLANE
#define USE_THREAT_SPACING
#define USE_THREAT_STATIC

void DoNextWorld(SDL_Renderer* screen);
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
  g_window = SDL_CreateWindow("Sman",
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

      if (Music::GetInstance()->Init() == false)
      {
          success = false;
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
  bool ret = g_background.LoadImg("img//background.png", g_screen, false);
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

void DoNextWorld(SDL_Renderer* screen)
{
    GameMap* game_map = GameMap::GetInstance();
    if (game_map != NULL)
    {
        game_map->DoNextWorldMap();
        game_map->ResetMap();
        game_map->LoadMap();
        game_map->LoadMapTiles(screen);
    }
}


int main( int argc, char* args[] )
{
  if (InitData() == false)
  {
    return PT_FAILED;
  }

    ImpTimer fps;

   if(!LoadBackground())
   {
     return PT_FAILED;
   }

  GameMap* game_map = GameMap::GetInstance();
  game_map->LoadMap();
  game_map->LoadMapTiles(g_screen);

  OptionObject option_control;
  bool ret_option = option_control.Init(g_screen);

   MainObject p_player;
   p_player.LoadImg(sPlayerMove, g_screen);
   //p_player.InitExp(g_screen);

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

   ThreatsAds* pThreatsAd = ThreatsAds::GetInstance();
   pThreatsAd->BuildMonster(g_screen);

   EndObject wDoor;
   wDoor.LoadImg("img//sman_open_new_world.png", g_screen);
   wDoor.SetPosTile(197, 8);

   ////Init Boss Object
   //BossObject bossObject;
   //bossObject.LoadImg("img//boss_object.png", g_screen);
   //int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
   //bossObject.set_xpos(xPosBoss);
   //bossObject.set_ypos(10);

   ExplosionObject exp_threats;

   bool ret = exp_threats.LoadImg("img//exp3.png", g_screen);
   if (!ret) return PT_FAILED;

   bool quit = false;

   int ret_menu = MenuGame::GetInstance()->StartMenu(g_screen);
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
         else if (g_event.type == SDL_KEYDOWN)
         {
             if (g_event.key.keysym.sym == SDLK_ESCAPE)
             {
                 Music::GetInstance()->PauseMusic();
                 Music::GetInstance()->PlaySoundGame(Music::GAME_PAUSE);
                 int ret = MenuGame::GetInstance()->PauseMenu(g_screen);
                 if (ret == 0)
                 {
                     break;
                 }
                 else
                 {
                     quit = true;
                 }
             }
         }

         option_control.HandleInputAction(g_event, g_screen);
         p_player.HandleInputAction(g_event, g_screen);
         ThreatsAds::GetInstance()->HandleInputAction(g_event, g_screen);
      }


      if (Music::GetInstance()->PlayMusic() == PT_FAILED)
      {
          return PT_FAILED;
      }

       SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
       SDL_RenderClear(g_screen);
       g_background.Render(g_screen, NULL);

       //pThreatsAd->DrawSecondObject(g_screen);

       game_map->DrawMap(g_screen);

       int playerPosX = p_player.get_x_pos();
       int plPosY = p_player.get_y_pos();

       int doorPosX = wDoor.GetXPos();
       int doorPosY = wDoor.GetYPos();

       if (doorPosX - playerPosX <= TILE_SIZE && 
           plPosY > doorPosY)
       {
           wDoor.SetStatus(EndObject::DOOR_OPENING);
           UINT dWidth = wDoor.GetWidthFrame();
           int pPos1 = doorPosX + dWidth*0.2;
           int pPos2 = doorPosX + dWidth*0.6;

           if (playerPosX > pPos1 && playerPosX < pPos2)
           {
               WorldData wData = p_player.GetWorldData();
               wData.wld_number_++;
               wData.wld_status_ = WorldData::W_FINISHED;
               p_player.SetWorldData(wData);
               DoNextWorld(g_screen);
               p_player.ReStart();
               pThreatsAd->Free();
               pThreatsAd->BuildMonster(g_screen);
               int ret = MenuGame::GetInstance()->EndWorldScreen(g_screen);
               if (ret == 0)
               {
                   continue;
               }
               else
               {
                   break;
               }
           }
       }
       wDoor.Show(g_screen);


       //DRAW OPTION CONTROL
       //option_control.Show(g_screen);
       //int type_ctrl = option_control.GetTypeCtrl();

       //Draw Geometric
       GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 40);
       ColorData color_data(36, 36, 36);
       Gemometric::RenderRectange(rectange_size, color_data, g_screen);

       GeometricFormat outlie_size(1, 1, SCREEN_WIDTH-1, 38);
       ColorData color_data1(255, 255, 255);
       Gemometric::RenderOutline(outlie_size, color_data1, g_screen);

       player_power.Show(g_screen);
       player_money.Show(g_screen);

       pThreatsAd->Render(g_screen);

       p_player.DoPlayer(g_screen);
       p_player.Show(g_screen);
       p_player.HandleBullet(g_screen);
#ifdef USING_OPTION_MOBILE
       p_player.UpdateCtrlState(type_ctrl, g_screen);
#endif
       bool bRet = ThreatsAds::GetInstance()->CheckCollision(g_screen, p_player.GetRectFrame(), false);
       if (bRet == true)
       {
           if (p_player.get_is_death() == false)
           {
               Music::GetInstance()->PauseMusic();
               Music::GetInstance()->PlaySoundGame(Music::DEATH_SOUND);
               p_player.set_is_death(true);
               p_player.set_alive_time(100);
               //if (pThreatAds.GetBoolCol() == true)
               //{
               //    p_player.SetBoomDeadth(true);
               //}
           }
       }

       bool bDie = false;
       if (p_player.get_is_falling() == true)
       {
           bDie = true;
       }

       if (bDie == true)
       {
           if (p_player.get_alive_time() <= 0)
           {
               num_die++;
               if (num_die <= 3)
               {
                   p_player.ResetAlive();
                   player_power.Decrease();
                   player_power.Render(g_screen);
                   continue;
               }
               else
               {
                   Music::GetInstance()->PlaySoundGame(Music::GAMEOVER_SOUND);
                   SDL_Delay(3000);
                   if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                   {
                       ThreatsAds::GetInstance()->Free();
                       close();
                       SDL_Quit();
                       return 0;
                   }
               }
           }
       }

       bool ret2 = ThreatsAds::GetInstance()->CheckCollisionSecond(g_screen, p_player.GetRectFrame(), true);
       if (ret2 == true)
       {
           p_player.setLevelMushroom();
       }

       ThreatsAds::GetInstance()->CheckCollisionLocal(g_screen);

       //COLLISION THREAT -> Main Bullet
       std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
       for (int am = 0; am < bullet_arr.size(); am++)
       {
         BulletObject* p_bullet = bullet_arr.at(am);
         if (p_bullet)
         {
            bool bRet = ThreatsAds::GetInstance()->CheckCollision(g_screen, p_bullet->GetRect());
            if (bRet)
            {
                SDL_Rect rc_pos;
                rc_pos.x = p_bullet->GetRect().x;
                rc_pos.y = p_bullet->GetRect().y + 25;
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
           p_player.SetCoinCount(reVal);

           player_power.InCrease();
           player_power.Render(g_screen);
       }

       //game_map->RenderBlockDe(g_screen);

       //Update screen
       SDL_RenderPresent(g_screen);

       //Cap the frame rate
       int val1 = fps.get_ticks();
       if(fps.get_ticks() < 1000/FRAMES_PER_SECOND)
       {
         SDL_Delay((1000/FRAMES_PER_SECOND ) - fps.get_ticks());
       }
  }

  game_map->DestroyInst();
  ThreatsAds::GetInstance()->DestroyInstance();

  close();
  return 0;
}