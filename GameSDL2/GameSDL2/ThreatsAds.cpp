#include "ThreatsAds.h"
#include "Goombas.h"

ThreatsAds::ThreatsAds()
{

}


ThreatsAds::~ThreatsAds()
{

}

void ThreatsAds::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        ThreatsObject* obj_threat = pThreatsNormal_.at(i);
        if (obj_threat != NULL)
        {
            obj_threat->HandleInputAction(events, screen);
        }

    }
}

void ThreatsAds::BuildThreats(SDL_Renderer* screen)
{
    Goombas* pGoombass = new Goombas[3];
    for (int i = 0; i < 3; i++)
    {
        Goombas* pObj = (pGoombass + i);
        if (pObj != NULL)
        {
            pObj->set_is_clip(true);
            pObj->LoadImg(static_img_name, screen);
            pObj->set_xpos(15*64 + i*100);
            pObj->set_ypos(GROUND_POS - pObj->get_height_frame());
            pThreatsNormal_.push_back(pObj);
        }
    }
}


void ThreatsAds::Render(SDL_Renderer* screen)
{
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        ThreatsObject* obj_threat = pThreatsNormal_.at(i);
        Goombas* pObject = static_cast<Goombas*>(obj_threat);
        if (pObject->get_is_alive() == true)
        {
            pObject->DoPlayer();
            pObject->Show(screen);
        }
        else
        {
            obj_threat->Free();
            pThreatsNormal_.erase(pThreatsNormal_.begin() + i);
        }
    }
}


bool ThreatsAds::CheckCollision(SDL_Renderer* screen, const SDL_Rect& rect_object, const bool& isDel/*true*/)
{
    bool bRet = false;
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        ThreatsObject* pThreat = pThreatsNormal_.at(i);
        if (pThreat)
        {
            SDL_Rect rect = pThreat->GetRectFrame();
            bool bCollision = SDLCommonFunc::CheckCollision(rect_object, rect);

            if (bCollision)
            {
                if (isDel == true)
                {
                    pThreatsNormal_.erase(pThreatsNormal_.begin() + i);
                }

                bRet = true;
                break;
            }
        }
    }

    return bRet;
}

void ThreatsAds::Free()
{
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        pThreatsNormal_.erase(pThreatsNormal_.begin() + i);
    }

    pThreatsNormal_.clear();
}