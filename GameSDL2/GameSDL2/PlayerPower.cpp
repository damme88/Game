#include "PlayerPower.h"
#include "Music.h"


ImgTextObj::ImgTextObj()
{
    m_font = NULL;
    m_count = 0;
    m_text.setColor(TextObject::WHITE_TEXT);
}

ImgTextObj::~ImgTextObj()
{

}

bool ImgTextObj::LoadImg(std::string path, SDL_Renderer* screen)
{
   return BaseObject::LoadImg(path, screen);
}

void ImgTextObj::SetRect(int x, int y)
{
    rect_.x = x;
    rect_.y = y;
}

void ImgTextObj::Show(SDL_Renderer* screen)
{
    std::string sCount = std::to_string(m_count);
    sCount = "X " + sCount;
    m_text.SetText(sCount);
    m_text.loadFromRenderedText(m_font, screen);
    m_text.RenderText(screen, m_xpText, m_ypText);
    Render(screen);
}



PlayerPower::PlayerPower(void)
{

}


PlayerPower::~PlayerPower(void)
{
    
}


bool PlayerPower::Init(SDL_Renderer* screen)
{
    bool bRet = false;
    m_count = 3;
    bRet = LoadImg(gSnamePlayerAlive, screen);
    SetRect(20, 0);
    m_font = TTF_OpenFont(g_NameFont, 30);
    m_xpText = 70;
    m_ypText = 15;
    return bRet;
}

void PlayerPower::Decrease()
{
    m_count--;
}

void PlayerPower::InCrease()
{
    m_count++;
    Music::GetInstance()->PlaySoundGame(Music::POWER_UP);
}

//Player Money

PlayerCoin::PlayerCoin()
{
}

PlayerCoin::~PlayerCoin()
{

}

bool PlayerCoin::Init(SDL_Renderer* screen)
{
    int bRet = false;
    m_font = TTF_OpenFont(g_NameFont, 30);
    m_xpText = SCREEN_WIDTH*0.5 - 260;
    m_ypText = 15;
    SetRect(SCREEN_WIDTH*0.5 - 300, 8);
    bRet = LoadImg(gSnameCoin, screen);
    return bRet;
}

// Weapon
PlayerWeapon::PlayerWeapon()
{
    m_type = WP_NONE;
}

PlayerWeapon::~PlayerWeapon()
{

}

bool PlayerWeapon::Init(SDL_Renderer* screen)
{
    bool bRet = false;
    m_xpText = SCREEN_WIDTH*0.5 - 420;
    m_ypText = 15;
    m_font = TTF_OpenFont(g_NameFont, 30);
    if (m_type == WP_KNI_THRW)
    {
        bRet = LoadImg(gSnameWpKni, screen);
    }
    else if (m_type == WP_VIKING_AXE)
    {
        bRet = LoadImg(gSnameWpViAxe, screen);
    }

    SetRect(SCREEN_WIDTH*0.5 - 450, 8);
    return bRet;
}