
#include <sstream> 
#include "CommonFunc.h"

int SDLCommonFunc::GetMax(const int& a, const int& b)
{
    return (a > b) ? a : b;
}

int SDLCommonFunc::GetMin(const int& a, const int& b)
{
    return (a < b) ? a : b;
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (top_a == top_b && bottom_a == bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (top_a == top_b && bottom_a == bottom_b)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

bool SDLCommonFunc::CheckInsideMapX(UINT x1, UINT x2)
{
    if (x1 >= 0 && x1 < MAX_MAP_X && x2 >= 0 && x2 < MAX_MAP_X)
        return true;
    return false;
}

bool SDLCommonFunc::CheckInsideMapY(UINT y1, UINT y2)
{
    if (y1 >= 0 && y1 < MAX_MAP_Y && y2 >= 0 && y2 < MAX_MAP_Y)
    {
        return true;
    }
    return false;
}

bool SDLCommonFunc::CheckInsideMap(UINT x, UINT y)
{
    if (x >= 0 && x < MAX_MAP_X && y >= 0 && y < MAX_MAP_Y)
        return true;
    return false;
}

std::vector<std::string>SDLCommonFunc::SplitBySpace(const std::string& sData)
{
    std::vector<std::string> retList;
    std::stringstream ss(sData);
    std::string sRet;
    while (std::getline(ss, sRet, ' '))
    {
        retList.push_back(sRet);
    }

    return retList;
}
