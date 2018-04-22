
#include "common_function.h"
#include "MainObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "ImpTimer.h"
#include "Explosion.h"


// Text and menu
TTF_Font* g_font = NULL;

bool Init() 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return false;

  Uint32 flag = SDL_SWSURFACE;
  //if (MessageBox(NULL, L"Would you like FullScreen", L"Info", MB_YESNO|MB_ICONINFORMATION) == IDYES) 
  //{
  //  flag = SDL_SWSURFACE | SDL_FULLSCREEN;
  //}

  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, flag);
  if (g_screen == NULL)
  {
    return false;
  }

  if (TTF_Init() == FAILED)
  {
    return false;
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == FAILED) 
  {
    return false;
  }

  g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main1);
  g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main2);
  g_sound_explosion = Mix_LoadWAV(g_name_audio_ex_main);
  g_sound_ex_main = Mix_LoadWAV(g_name_audio_ex_threats);

  if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_explosion == NULL)
  {
    return false;
  }


  g_font = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 40);
  if (g_font == NULL)
  {
    return false;
  }

  //Set the window caption
  SDL_WM_SetCaption(g_string_caption, NULL );

  return true;
}


int main(int arc, char* argv[])
{
  int bkgn_x = 0;
  int bkgn_y = 0;

  bool is_quit = false;
  if (Init() == false)
    return 0;

  ImpTimer fps;
  g_bkground = SDLCommonFunc::LoadImage(g_name_background);
  if (g_bkground == NULL)
  {
    return 0;
  }

  MainObject walk_object;
  walk_object.SetRect(POS_X_START_MAIN_OBJECT, POS_Y_TART_MAIN_OBJECT);

  bool ret = walk_object.LoadImg(g_name_main);
  if (!ret) return 0;

  walk_object.set_clips();

  ExplosionObject exp_threats;
  ExplosionObject exp_main;

  ret = exp_threats.LoadImg(g_name_explosion_threat);
  exp_threats.set_clips();
  if (!ret) return 0;

  ret = exp_main.LoadImg(g_name_explosion_main);
  exp_main.set_clips();
  if (!ret) return 0;

  ThreatsObject* p_threat = new ThreatsObject(); //[NUM_THREATS];
  if (p_threat)
  {
      int randVal = SDLCommonFunc::MakeRandomPostY();
      p_threat->SetRect(SCREEN_WIDTH - randVal, POS_Y_TART_THREAT_OBJECT);
      p_threat->set_is_alive(true);
      p_threat->LoadImg(g_name_threats);
      BulletObject* p_bullet = new BulletObject();
      p_threat->InitBullet(p_bullet);
  }

  int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font);
  if (ret_menu == 1) 
    is_quit = true;

  int num_live = 0;
  while (!is_quit) 
  {
    fps.start();
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT) 
      {
        is_quit = true;
        break;
      }
      walk_object.HandleInputAction(g_even, g_sound_bullet);
    }

    //Run background Screen
    SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, bkgn_y);

    // Show and move plane object
    walk_object.HandleMove();
    walk_object.Show(g_screen);
    walk_object.ImplementJump();
    walk_object.HandleBullet(g_screen);

    int x_rect = walk_object.GetRect().x;
    if (x_rect > SCREEN_WIDTH*0.35)
    {
      if (abs(bkgn_x) >= WIDHT_BKGROUND - SCREEN_WIDTH)
      {
         walk_object.set_is_move(true);
         p_threat->set_x_pos(0);
      }
      else
      {
        int vecloty = walk_object.GetVelocity();
        if (vecloty != 0)
        {
          bkgn_x -= vecloty;
          p_threat->set_x_pos(SPEED_MAIN_OBJECT);
          walk_object.set_is_move(false);
        }
        else
        {
           p_threat->set_x_pos(0);
        }
      }
    }
    else
    {
       p_threat->set_x_pos(0);
    }
    
    if (p_threat)
    {
      if (p_threat->get_is_alive())
      {
          p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
          p_threat->Show(g_screen);
          //p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

          //COLLISION THREAT BULLET -> MAIN OBJECT
          bool is_col1 = false;
          std::vector<BulletObject*> bullet_list = p_threat->get_bullet_list();
          for (int am = 0; am < bullet_list.size(); am++)
          {
            BulletObject* p_bullet = bullet_list.at(am);
            if (p_bullet)
            {
              is_col1 = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), walk_object.GetRect());
              if (is_col1 == true)
              {
                p_threat->ResetBullet(p_bullet);
                break;
              }
            }
          }

          //COLLISION THREAT-> MAIN OBJECT
          bool is_col2 = SDLCommonFunc::CheckCollision(walk_object.GetRect(), p_threat->GetRect());
          if (is_col1 || is_col2)
          {
            p_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
            walk_object.set_is_move(true);
            for (int ex = 0; ex < 4; ex++)
            {
              int x_pos = (walk_object.GetRect().x + walk_object.GetRect().w*0.5) - EXPLOSION_WIDTH*0.5;
              int y_pos = (walk_object.GetRect().y + walk_object.GetRect().h*0.5) - EXPLOSION_HEIGHT*0.5;

              exp_main.set_frame(ex);
              exp_main.SetRect(x_pos, y_pos);
              exp_main.Show(g_screen);

              if (SDL_Flip(g_screen) == -1)
              {
                delete  p_threat;
                SDLCommonFunc::CleanUp();
                SDL_Quit();
                return 0;
              }
            }

            Mix_PlayChannel(-1, g_sound_ex_main, 0);
            num_live++;
            if (num_live <= 3)
            {
              SDL_Delay(1000);
              walk_object.SetRect(POS_X_START_MAIN_OBJECT, POS_Y_TART_MAIN_OBJECT);
              continue;
            }
            else
            {
              if(MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
              {
                delete  p_threat;
                SDLCommonFunc::CleanUp();
                SDL_Quit();
                return 0;
              }
            }
          }

          //COLLISION THREAT -> Main Bullet
          std::vector<BulletObject*> bullet_arr = walk_object.get_bullet_list();
          for (int am = 0; am < bullet_arr.size(); am++)
          {
            BulletObject* p_bullet = bullet_arr.at(am);
            if (p_bullet)
            {
              bool is_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
              if (is_col)
              {
                for (int ex = 0; ex < 4; ex++)
                {
                  int x_pos = p_bullet->GetRect().x - EXPLOSION_WIDTH*0.5;
                  int y_pos = p_bullet->GetRect().y - EXPLOSION_HEIGHT*0.5;

                  exp_threats.set_frame(ex);
                  exp_threats.SetRect(x_pos, y_pos);
                  exp_threats.Show(g_screen);
                }

                 p_threat->Reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                 walk_object.RemoveBullet(am);
                 Mix_PlayChannel(-1, g_sound_explosion, 0);
              }
            }
          }
      }
    }

    if (SDL_Flip(g_screen) == -1)
    {
      SDLCommonFunc::CleanUp();
      SDL_Quit();
      return 0;
    }
    //Cap the frame rate
    int val1 = fps.get_ticks();
    if(fps.get_ticks() < 1000/FRAMES_PER_SECOND)
    {
      SDL_Delay((1000/FRAMES_PER_SECOND ) - fps.get_ticks());
    }
  }

  SDLCommonFunc::CleanUp();
  SDL_Quit();
  return 1;
}