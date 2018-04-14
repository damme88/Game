
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "common_function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDHT_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();
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
private:
  int x_val_;
  int y_val_;
  std::vector<BulletObject*> p_bullet_list;
};

#endif