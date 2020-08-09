
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ExplosionObject.h"
#include "Music.h"
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
static char sPlayerDeath[] = {"img//player_death.png" };

static char kImgBullet[] = {"img//player_bullet.png"};

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
                         SDL_Renderer* screen); 

  void DoPlayer();
  void CheckToMap();

  void DrawBound(SDL_Renderer* des);
  void HandleBullet(SDL_Renderer* des);
  void RemoveBullet(const int& idx);

  int get_x_pos()       const  { return x_pos_; }
  int get_y_pos()        const { return y_pos_; }
  int GetMoneyCount()    const { return money_count_; };
  int get_frame_width()  const { return width_frame_; }
  int get_frame_height() const { return height_frame_; }
  bool get_is_falling() const { return is_falling_; }
  bool get_is_death() const { return is_death_; }
  int get_alive_time() const { return alive_time_; }
  VT(BulletObject*) get_bullet_list() const;
  SDL_Rect GetRectFrame();

  void setXYPos(const int& xp, const int& yp) { x_pos_ = xp; y_pos_ = yp; }
  void set_is_falling(const bool& is_falling) { is_falling_ = is_falling; }
  void set_is_death(const bool& is_death) { is_death_ = is_death; }
  void set_alive_time(const int& live_time) { alive_time_ = live_time; }
  void SetMoneyCount(const int& money_count) {money_count_ = money_count;}
  void IncreaseMoney();
  void set_bullet_list(VT(BulletObject*) bullet_list);
  void InitExp(SDL_Renderer* des);
  void ResetAlive();
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
  bool is_death_;
  bool fast_run_;

  int frame_;
  int status_;
  int map_x_;
  int map_y_;
  int width_frame_;
  int height_frame_;
  int money_count_;
  int alive_time_;

  float x_val_;
  float y_val_;
  float x_pos_;
  float y_pos_;
};


#endif