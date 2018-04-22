
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "common_function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>


class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  enum BulletDir
  {
    DIR_RIGHT = 20,
    DIR_LEFT = 21,
  };

  void HandleInputAction(SDL_Event events,   Mix_Chunk* bullet_sound[3]);
  void HandleMove();

  void set_x_pos(int xp) {x_val_ = xp;}
  void set_y_pos(int yp) {y_val_ = yp;}
  int get_x_pos() {return x_val_;}
  int get_y_pos() {return y_val_;}
  std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list;}
  void set_bullet_list(std::vector<BulletObject*> bullet_list)
  {
    p_bullet_list = bullet_list;
  }
  void HandleBullet(SDL_Surface* des);
  void RemoveBullet(const int& idx);
  void set_clips();
  void Show(SDL_Surface* des);
  int GetVelocity() const {return velocity_;}
  void set_is_move(const bool& is_move) {is_move_ = is_move;}
  void ImplementJump();
private:
  bool is_move_;
  int x_val_;
  int y_val_;
  std::vector<BulletObject*> p_bullet_list;
  SDL_Rect right_clip_[4];
  SDL_Rect left_clip[4];
  int velocity_;
  int velocity2_;
  bool is_jump_;
  int frame_;
  int status_;
  int bullet_dir_;
};

#endif