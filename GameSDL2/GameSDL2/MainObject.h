
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 8
#define PLAYER_HIGHT_VAL 18;

#define STATE_MONEY 4

static char g_name_main_right[] = {"img//player_right.png"};
static char g_name_main_left[]  = {"img//player_left.png"};
static char g_main_jump_left[]   = {"img//jum_left.png"};
static char g_main_jump_right[] = {"img//jum_right.png"};

static char kImgBullet[] = {"img//sphere2.png"};
static char kSoundBeep[] = {"sound//beep.wav"};

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  enum WalkType
  {
    WALK_RIGHT = 0,
    WALK_LEFT = 1,
  };

  void set_clips();
  bool LoadImg(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* des);
  void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[3]); 
  void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;};

  void DoPlayer(Map& g_map);

  void CenterEntityOnMap(Map& g_map);
  void CheckToMap(Map& g_map);

  std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
  void set_bullet_list(std::vector<BulletObject*> bullet_list)
  {
    p_bullet_list_ = bullet_list;
  }

  void HandleBullet(SDL_Renderer* des);
  void RemoveBullet(const int& idx);

  int get_frame_width() const {return width_frame_;}
  int get_frame_height() const {return height_frame_;}
  void set_think_time(const int& think_time) {think_time_ = think_time;}
  SDL_Rect GetRectFrame();
  int GetMoneyCount() const {return money_count_;};
  void SetMoneyCount(const int& money_count) {money_count_ = money_count;}
  void IncreaseMoney();

protected:
  void UpdateLeftRightPlayer(SDL_Renderer* des);
  void UpdateWalkJumpPlayer(SDL_Renderer* des);
private:

  //Bullet list
  std::vector<BulletObject*> p_bullet_list_;

  bool is_jump_;
  int frame_;
  int status_;

  SDL_Rect frame_clip_[8];
  Input input_type_;

  int on_ground_;
  int think_time_;
  int number_of_think_time_;
  int map_x_;
  int map_y_;

  float x_val_;
  float y_val_;
  float x_pos_;
  float y_pos_;

  int width_frame_;
  int height_frame_;

  int money_count_;
};


#endif