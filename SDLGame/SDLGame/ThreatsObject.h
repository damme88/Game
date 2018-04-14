
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "common_function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDHT_THREAT 80;
#define HEIGHT_THREAT 40;

class ThreatsObject : public BaseObject
{
public:

  ThreatsObject();
  ~ThreatsObject();
  void HandleInputAction(SDL_Event events, SDL_Rect rect_obj);
  void HandleMove(const int x_boder, const int y_border);

  void set_x_pos(int xp) {x_val_ = xp;}
  void set_y_pos(int yp) {y_val_ = yp;}
  int get_x_pos() {return x_val_;}
  int get_y_pos() {return y_val_;}
  bool get_is_alive() {return is_alive_;}
  void set_is_alive(bool is_alive) {is_alive_ = is_alive;}

  void InitBullet(BulletObject* p_bullet);
  void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);
  void Reset(const int x_boder, const int y_border);

  std::vector<BulletObject*> get_bullet_list() const {return bullet_list_;}
  void set_bullet_list(const std::vector<BulletObject*>& am_list) {bullet_list_ = am_list;}

  void RemoveBullet(const int& idx); 
  void ResetBullet(BulletObject* p_bullet);
private:
  int x_val_;
  int y_val_;
  bool is_alive_;
  bool is_stop_bullet_;

  std::vector<BulletObject*> bullet_list_;
};

#endif //THREATS_OBJECT_H_