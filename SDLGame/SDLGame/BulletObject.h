
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "common_function.h"
#include "BaseObject.h"

#define WIDTH_BULLET_LASER 36
#define HEIGHT_BULLET_LASER 13

#define WIDTH_BULLET_SPHERE 10
#define HEIGHT_BULLET_SPHERE 10

class BulletObject : public BaseObject
{
public:
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

  BulletObject();
  ~BulletObject();
  void HandleInputAction(SDL_Event events, SDL_Rect rect_obj);
  void HandleMove(const int x_boder, const int y_border);
  void HandleMoveRightToLeft(const int& y_limit);

  void set_x_pos(int xp) {x_val_ = xp;}
  void set_y_pos(int yp) {y_val_ = yp;}
  int get_x_pos() {return x_val_;}
  int get_y_pos() {return y_val_;}
  bool get_is_move() {return is_move_;}
  void set_is_move(bool is_move) {is_move_ = is_move;}
  void set_move_type(const unsigned int& mv_type) {move_type_ = mv_type;}
  unsigned int get_move_type() const {return move_type_;}
  void set_type(const unsigned int& bl_type) {bullet_type_ = bl_type;}
  unsigned int get_type() const {return bullet_type_;}
  void SetWidthHeight(const int& with, const int& height) {rect_.w = with; rect_.h = height;}
private:
  int x_val_;
  int y_val_;
  bool is_move_;
  unsigned int bullet_type_;
  int move_type_;
};

#endif //BULLET_OBJECT_H_