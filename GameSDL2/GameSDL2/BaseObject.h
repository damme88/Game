
#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include "CommonFunc.h"

#define VT(T) std::vector<T>

class DataImg
{
public:
    DataImg();
    ~DataImg();
    SDL_Color m_Color;
    bool IsColorKey();
};


class BaseObject
{
public:
  BaseObject();
  ~BaseObject();
  virtual bool LoadImg(std::string path, SDL_Renderer* screen, const bool& bGetPixel = true);
  void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
  
  void Free();
  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;};
  void setColor(const Uint8& red, const Uint8& green, const Uint8& blue);
  void setAlpha(const Uint8& alpha);
  void setBlendMode(const SDL_BlendMode& blending);
  void SetIsFlip(const bool& flip) { m_Flip = flip; }
  void SetAngle(float angle) { angle_ = angle; }
  bool GetFlip() const { return m_Flip; }
  void SetIsAngle() { m_angle_ = true; }
  SDL_Rect GetRect() const { return rect_; }
  SDL_Texture* GetObject() { return p_object_; }
  VT(VT(DataImg*)) GetPixelImg(SDL_Surface* pSurface, int width, int height);
  DataImg* GetPixelPos(int x, int y);
protected:
  VT(VT(DataImg*)) m_pixelList;
  float angle_;
  SDL_Texture* p_object_;
  SDL_Rect rect_;
  bool m_Flip;
  bool m_angle_;
};


#endif