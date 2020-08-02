
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ExplosionObject.h"
#include <vector>


#define GRAVITY_SPEED       0.8
#define MAX_FALL_SPEED      16

#define PLAYER_SPEED        8
#define PLAYER_HIGHT_VAL    18
#define PLAYER_FRAMES       4

static char sPlayerMove[] = {"img//player_move.png"};
static char sPlayerJump[] = {"img//player_jump.png"};
static char sPlayerDown[] = {"img//player_down.png" };
static char sPlayerExp[] = { "img//player_exp.png" };
static char kImgBullet[] = {"img//player_bullet.png"};
static char kSoundBeep[] = {"sound//coin.wav"};

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  enum WalkType
  {
     WALK_NONE = 0,
     WALK_RIGHT = 1,
     WALK_LEFT = 2,
  };

  bool LoadImg(std::string path, SDL_Renderer* screen);

  void set_clips();
  void Show(SDL_Renderer* des);
  void HandleInputAction(SDL_Event events, 
                         SDL_Renderer* screen,
                         Mix_Chunk* bullet_sound[3]); 

  void DoPlayer();
  void CheckToMap();

  void DrawBound(SDL_Renderer* des);
  void HandleBullet(SDL_Renderer* des);
  void RemoveBullet(const int& idx);

  int get_x_post()       const { return x_pos_; }
  int get_y_pos()        const { return y_pos_; }
  int GetMoneyCount()    const { return money_count_; };
  int get_frame_width()  const { return width_frame_; }
  int get_frame_height() const { return height_frame_; }

  VT(BulletObject*) get_bullet_list() const;
  SDL_Rect GetRectFrame();

  void set_think_time(const int& think_time) {falling_time_ = think_time;}
  void SetMoneyCount(const int& money_count) {money_count_ = money_count;}
  void IncreaseMoney();
  void set_bullet_list(VT(BulletObject*) bullet_list);
  void InitExp(SDL_Renderer* des);

protected:
  void UpdateImagePlayer(SDL_Renderer* des);

private:

  VT(BulletObject*) p_bullet_list_;
  SDL_Rect frame_clip_[4];
  Input input_type_;
  ExplosionObject exp_;

  bool is_jump_;
  bool on_ground_;
  bool is_falling_;

  int frame_;
  int status_;
  int falling_time_;
  int map_x_;
  int map_y_;
  int width_frame_;
  int height_frame_;
  int money_count_;

  float x_val_;
  float y_val_;
  float x_pos_;
  float y_pos_;
};


#endif