

#include "Geometric.h"

TPoint::TPoint()
{
    x = 0;
    y = 0;
}

TPoint::TPoint(int xx, int yy)
{
    x = xx;
    y = yy;
}

TPoint::TPoint(const TPoint& pt)
{
    x = pt.x;
    y = pt.y;
}

TPoint::~TPoint()
{

}

float TPoint::GetDistance(const TPoint& pt)
{
    int val1 = (pt.x - this->x)*(pt.x - this->x);
    int val2 = (pt.y - this->y)*(pt.y - this->y);
    float ret = sqrt(val1 + val2);
    return ret;
}


TVec2D::TVec2D()
{
    x = 0;
    y = 0;
}

TVec2D::TVec2D(int xx, int yy)
{
    x = xx;
    y = yy;
}

TVec2D::TVec2D(const TVec2D& pt)
{
    x = pt.x;
    y = pt.y;
}

TVec2D::~TVec2D()
{

}

////////////////////////////////////////////////////////////////////////

TLine::TLine() 
{

}

TLine::~TLine()
{

}

TLine::TLine(const TPoint& pt1, const TPoint& pt2)
{
    p1 = pt1;
    p2 = pt2;
}

void TLine::SetPoint(const TPoint& pt1, const TPoint& pt2)
{
    p1 = pt1;
    p2 = pt2;
}


TPoint TLine::GetMidPoint()
{
    TPoint pt;
    pt.x = (p1.x + p2.x)*0.5;
    pt.y = (p1.y + p2.y)*0.5;
    return pt;
}


float TLine::GetLength()
{
    float ret = p1.GetDistance(p2);
    return ret;
}


TVec2D TLine::GetDirVector()
{
    TVec2D v1(p1.x, p1.y);
    TVec2D v2(p2.x, p2.y);

    TVec2D vDir = v2 - v1;

    int xp = vDir.x;
    int yp = vDir.y;

    float d = sqrt(xp*xp + yp*yp);

    vDir.x = xp / d;
    vDir.y = yp / d;

    return vDir;
}

/****************************************
// Check relation ship line and point
// Return:  0 => on line without duplicate p1,p2
            1 => duplicate with p1 or p2
            2 => not on line
            -1 => exception (no define)
****************************************/
int TLine::CheckRelPoint(const TPoint& pt)
{
    int ret = -1;

    // Check duplicate
    if (abs(pt.x - p1.x) < K_EPXILON_4 &&
        abs(pt.y - p2.y) < K_EPXILON_4)
    {
        ret = 1;
        return ret;
    }
    if (abs(pt.x - p2.x) < K_EPXILON_4 &&
        abs(pt.y - p2.y) < K_EPXILON_4)
    {
        ret = 1;
        return ret;
    }

    // Check on line
    float length = this->GetLength();
    float d1 = p1.GetDistance(pt);
    float d2 = p2.GetDistance(pt);
    float dSum = d1 + d2;
    if (abs(length - dSum) < K_EPXILON_4)
    {
        ret = 0;
    }
    else
    {
        ret = 2;
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////


TTriangle::TTriangle()
{
    m_num = 3;
}

TTriangle::~TTriangle()
{
 
}

void TTriangle::SetPoint(const TPoint& pt1, const TPoint& pt2, const TPoint& pt3)
{
    m_num = 3;
    m_points[0] = pt1;
    m_points[1] = pt2;
    m_points[2] = pt3;
}
float TTriangle::GetArea()
{
    double area = 0.0;
    int j = m_num - 1;
    for (int i = 0; i < m_num; i++)
    {
        area += (m_points[j].x + m_points[i].x) * (m_points[j].y - m_points[i].y);
        j = i;
    }
    return abs(area / 2.0);
}


///////////////////////////////////////////////////////////////////////////

TRect::TRect()
{
    m_num = 4;

}

TRect::~TRect()
{

}

void TRect::MakeRect(const SDL_Rect& rect)
{
    TPoint pp1(rect.x, rect.y);
    TPoint pp2(rect.x, rect.y + rect.h);
    TPoint pp3(rect.x + rect.w, rect.y + rect.h);
    TPoint pp4(rect.x + rect.w, rect.y);

    m_num = 4;
    m_points[0] = pp1;
    m_points[1] = pp2;
    m_points[2] = pp3;
    m_points[3] = pp4;

}

float TRect::GetArea()
{
    double area = 0.0;
    int j = m_num - 1;
    for (int i = 0; i < m_num; i++) 
    {
        area += (m_points[j].x + m_points[i].x) * (m_points[j].y - m_points[i].y);
        j = i;
    }
    return abs(area / 2.0);
}

/****************************************
// Check relation ship rect and point
// Return:  0 => inside
            1 => in boder
            2 => outside
****************************************/
int TRect::CheckRelPoint(const TPoint& pt)
{
    int iRet = -1;

    // Check on lines of rect
    for (int i = 0; i < m_num; i++)
    {
        int j = (i + 1) % m_num;

        TLine pline(m_points[i], m_points[j]);
        int ret = pline.CheckRelPoint(pt);
        if (ret == 0 || ret == 1) // on line
        {
            iRet = 1; // on border
            return iRet;
        }
    }

    float sumAreaTriangle = 0.0;
    for (int i = 0; i < m_num; i++)
    {
        int j = (i + 1) % m_num;
        TPoint p1 = m_points[i];
        TPoint p2 = m_points[j];
        TPoint p3 = pt;
        TTriangle triObj;
        triObj.SetPoint(p1, p2, p3);
        sumAreaTriangle += triObj.GetArea();
    }

    float areaRect = this->GetArea();
    if (abs(areaRect - sumAreaTriangle) < K_EPXILON_4)
    {
        iRet = 0; // INSIDE
    }
    else
    {
        iRet = 2; // OUTSIDE
    }

    // Check Inside or outside
    return iRet;
}

void TRect::SetPoint(const TPoint& pt1, const TPoint& pt2, const TPoint& pt3, const TPoint& pt4)
{
    m_points[0] = pt1;
    m_points[1] = pt2;
    m_points[2] = pt3;
    m_points[3] = pt4;
}

void TRect::SetPoint(TPoint ptArr[], int np)
{
    if (np == 4)
    {
        m_points[0] = ptArr[0];
        m_points[1] = ptArr[1];
        m_points[2] = ptArr[2];
        m_points[3] = ptArr[3];
    }
}


/////////////////////////////////////////////////////////////////////////

void Gemometric::RenderRectange(const GeometricFormat& geo_size, const ColorData& color, SDL_Renderer* screen)
{
    SDL_Rect fillRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(screen, color.red_, color.green_, color.blue_, 0xFF);        
    SDL_RenderFillRect(screen, &fillRect );
}

void Gemometric::RenderOutline(const GeometricFormat& geo_size, const ColorData& color, SDL_Renderer* screen)
{
    SDL_Rect outlineRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(screen, color.red_, color.green_, color.blue_, 0xFF);
    SDL_RenderDrawRect(screen, &outlineRect );
}