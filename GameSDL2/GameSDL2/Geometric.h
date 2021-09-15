
#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_
#include <SDL.h>
#include <cmath>

#define K_EPXILON_2  0.01
#define K_EPXILON_3  0.001
#define K_EPXILON_4  0.0001
#define K_EPXILON_5  0.00001
#define K_EPXILON_6  0.000001

typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height)
    {
        left_ = left; top_ = top;
        width_ = width;
        height_ = height;
    }
    int left_;
    int top_;
    int width_;
    int height_;
};

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b)
    {
        red_ = r;
        green_ = g;
        blue_ = b;
    }

    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

class TPoint
{
public:
    TPoint();
    TPoint(int xx, int yy);
    TPoint(const TPoint& pt);
    ~TPoint();
    int x;
    int y;

    TPoint& operator =(const TPoint& pt)
    {
        this->x = pt.x;
        this->y = pt.y;
        return *this;
    }

    float GetDistance(const TPoint& pt);
};


class TVec2D
{
public:
    TVec2D();
    TVec2D(int xx, int yy);
    TVec2D(const TVec2D& pt);
    ~TVec2D();
    int x;
    int y;

    TVec2D& operator =(TVec2D& pt)
    {
        this->x = pt.x;
        this->y = pt.y;
    }

    const TVec2D& operator -(const TVec2D& pt)
    {
        TVec2D vDir;
        vDir.x = this->x - pt.x;
        vDir.y = this->y - pt.y;
        return vDir;
    }
};

class TLine
{
public:
    TLine();
    TLine(const TPoint& p1, const TPoint& p2);
    ~TLine();
    void SetPoint(const TPoint& pt1, const TPoint& pt2);
    TPoint GetMidPoint();
    float GetLength();
    TVec2D GetDirVector();
    int CheckRelPoint(const TPoint& pt);
private:
    TPoint p1;
    TPoint p2;
};

class TTriangle
{
public:
    TTriangle();
    ~TTriangle();
    void SetPoint(const TPoint& pt1, const TPoint& pt2, const TPoint& pt3);
    float GetArea();
private:
    TPoint m_points[3];
    int m_num;
};

class TRect
{
public:
    TRect();
    ~TRect();
    int CheckRelPoint(const TPoint& pt);
    float GetArea();
    void SetPoint(const TPoint& pt1, const TPoint& pt2, const TPoint& pt3, const TPoint& pt4);
    void SetPoint(TPoint ptArr[], int np);
    void MakeRect(const SDL_Rect& rect);
private:
    TPoint m_points[4];
    int m_num;
};


class Gemometric
{
public:
   static void RenderRectange(const GeometricFormat& geo_size, const ColorData& color, SDL_Renderer* screen);
   static void RenderOutline(const GeometricFormat& geo_size, const ColorData& color, SDL_Renderer* screen);
};


#endif