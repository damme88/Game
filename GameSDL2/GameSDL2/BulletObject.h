

#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "ExplosionObject.h"
#include "game_map.h"

class BulletObject : public BaseObject
{
public:
  BulletObject();
  ~BulletObject();


  enum BulletDir
  {
    DIR_RIGHT = 20,
    DIR_LEFT = 21,
    DIR_UP = 22,
    DIR_UP_LEFT = 23,
    DIR_UP_RIGHT = 24,
    DIR_DOWN_LEFT = 25,
    DIR_DOWN_RIGHT = 26,
    DIR_DOWN = 27,
  };

  enum BulletType
  {
    NONE,
    LASER,
    SPHERE
  };

  enum MoveType
  {
    LINE_TYPE = 10,
    SIN_TYPE = 11
  };

  void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x, map_y_ = map_y; };
  void HandelMove(const int& x_border, const int& y_border);
  void set_x_val(const int& x_val) {x_val_ = x_val;}
  void set_y_val(const int& y_val) {y_val_ = y_val;}
  void set_xy_pos(const int& xp, const int& yp) { x_pos_ = xp, y_pos_ = yp; }
  int get_x_val() const {return x_val_;}
  int get_y_val() const {return y_val_;}
  void set_is_move(const bool& is_move) {is_move_ = is_move;} 
  bool get_is_move()const {return is_move_;}
  void set_dir_bullet(const int& dir_type) {bullet_dir_ = dir_type;}
  bool CheckToMap();
  BulletObject* Clone();
  void Show(SDL_Renderer* des);
private:

  int x_pos_;
  int y_pos_;
  int x_val_;
  int y_val_;
  bool is_move_;
  int bullet_dir_;
  int move_type_;
  int map_x_;
  int map_y_;

};

#endif