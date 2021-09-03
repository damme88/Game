
#ifndef PLAYER_POWER_H_
#define  PLAYER_POWER_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "TextObject.h"

static char gSnameCoin[] = { "img//sman_icon_coin_num.png" };
static char gSnamePlayerAlive[] = { "img//sman_icon_live.png" };
static char gSnameWpKni[] = { "img//sman_icon_kni.png" };
static char gSnameWpViAxe[] = { "img//sman_icon_vi_axe.png" };

class ImgTextObj : BaseObject
{
public:
    ImgTextObj();
    ~ImgTextObj();
    void SetCount(const int& count) { m_count = count; }
    void Show(SDL_Renderer* screen);
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void SetRect(int x, int y);
protected:
    TTF_Font* m_font;
    TextObject m_text;
    int m_xpText;
    int m_ypText;
    INT m_count;
};

class PlayerPower : public ImgTextObj
{
public:
    PlayerPower(void);
    ~PlayerPower(void);
    bool Init(SDL_Renderer* screen);
    void InCrease();
    void Decrease();
private:
};


class PlayerCoin : public ImgTextObj
{
public:
    PlayerCoin(void);
    ~PlayerCoin(void);
    bool Init(SDL_Renderer* screen);
};


class PlayerWeapon : public ImgTextObj
{
public:
    PlayerWeapon(void);
    ~PlayerWeapon(void);
    bool Init(SDL_Renderer* screen);;
    void SetType(const int& type) { m_type = type; }
    enum WeaponType
    {
        WP_NONE = 30,
        WP_KNI_THRW,
        WP_VIKING_AXE,
    };
private:
    int m_type;
};

#endif
