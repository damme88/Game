#include "ThreatsAds.h"
#include "Goombas.h"
#include "TBoom.h"

#define NO_BOOM 

ThreatsAds* ThreatsAds::instance_ = NULL;

ThreatsAds::ThreatsAds()
{
    is_boom_cool_ = false;
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
#ifndef NO_BOOM
            if (obj_threat->GetType() == ThreatsObject::TH_GOOMBAS)
            {
                Goombas* pObject = static_cast<Goombas*>(obj_threat);
                if (pObject->GetIsBoom())
                {
                    pObject->SetIsBoom(false);
                    TBoom* pBom = new TBoom();
                    bool ret = pBom->LoadImg("img//boom_boom64.png", screen);
                    if (ret)
                    {
                        pBom->set_clips();
                        pBom->set_xpos(pObject->get_x_pos());
                        pBom->set_ypos(pObject->get_y_pos());
                        pThreatsNormal_.push_back(pBom);
                    }
                }
            }
#endif
        }
    }
}

void ThreatsAds::BuildThreats(SDL_Renderer* screen)
{
    Goombas* pGoombass = new Goombas[1];
    for (int i = 0; i < 1; i++)
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

#ifndef NO_BOOM
    pEx_ = new ExplosionObject();
    pEx_->LoadImg("img//exp5.png", screen);
    pEx_->set_clips();
#endif
}

void ThreatsAds::AddSecondObject(ThreatsObject* pObj)
{
    if (pObj != NULL)
    {
        Music::GetInstance()->PlaySoundGame(Music::MUSHROM_SHOW);
        pSecondObject_.push_back(pObj);
    }
}


void ThreatsAds::Render(SDL_Renderer* screen)
{
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        ThreatsObject* obj_threat = pThreatsNormal_.at(i);
        if (obj_threat->GetType() == ThreatsObject::TH_GOOMBAS)
        {
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
        else if (obj_threat->GetType() == ThreatsObject::TH_BOOM)
        {
            TBoom* pObject = static_cast<TBoom*>(obj_threat);
            pObject->Show(screen);
        }
    }
}

void ThreatsAds::DrawSecondObject(SDL_Renderer* des)
{
    for (int i = 0; i < pSecondObject_.size(); i++)
    {
        ThreatsObject* obj_threat = pSecondObject_.at(i);
        obj_threat->Show(des);
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
                bRet = true;
            /*    if (pThreat->GetType() == ThreatsObject::TH_BOOM)
                {
                    pThreatsNormal_.erase(pThreatsNormal_.begin() + i);
                    SDL_Rect rect;
                    rect = pThreat->GetRect();
                    pEx_->ImpRender(screen, rect);
                    Music::GetInstance()->PlaySoundGame(Music::EXP_BOOM);
                    is_boom_cool_ = true;
                }
                else
                {*/
                    if (isDel == true)
                    {
                        pThreatsNormal_.erase(pThreatsNormal_.begin() + i);
                    }
                    //Music::GetInstance()->PlaySoundGame(Music::EXP_SOUND);
                //}
                break;
            }
        }
    }

    return bRet;
}

bool ThreatsAds::CheckCollisionSecond(SDL_Renderer* screen, 
                                      const SDL_Rect& rect_object,
                                      const bool& isDel/*true*/)
{
    bool bRet = false;
    for (int i = 0; i < pSecondObject_.size(); i++)
    {
        ThreatsObject* pThreat = pSecondObject_.at(i);
        if (pThreat)
        {
            SDL_Rect rect = pThreat->GetRectFrame();
            bool bCollision = SDLCommonFunc::CheckCollision(rect_object, rect);

            if (bCollision)
            {
                bRet = true;
               
                if (isDel == true)
                {
                    pSecondObject_.erase(pSecondObject_.begin() + i);
                }
                Music::GetInstance()->PlaySoundGame(Music::MUSHROOM_MEAT);
                break;
            }
        }
    }
    return bRet;
}

bool ThreatsAds::CheckCollisionLocal(SDL_Renderer* screen)
{
    bool ret = false;
    for (int i = 0; i < pSecondObject_.size(); i++)
    {
        ThreatsObject* pThreat1 = pSecondObject_.at(i);
        if (pThreat1)
        {
            SDL_Rect rect1 = pThreat1->GetRectFrame();
            for (int i = 0; i < pThreatsNormal_.size(); i++)
            {
                ThreatsObject* pThreat2 = pThreatsNormal_.at(i);
                if (pThreat2)
                {
                    SDL_Rect rect2 = pThreat2->GetRectFrame();
                    bool bCollision = SDLCommonFunc::CheckCollision(rect1, rect2);
                    if (bCollision)
                    {
                        ret = true;
                        pSecondObject_.erase(pSecondObject_.begin() + i);

                        if (pThreat2->GetType() == ThreatsObject::TH_GOOMBAS)
                        {
                            Goombas* pGoombas = static_cast<Goombas*>(pThreat2);
                            if (pGoombas != NULL)
                            {
                                pGoombas->SetIsChange(true);
                                pGoombas->SetIsType(Goombas::GOOM_X5);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    return ret;
}

void ThreatsAds::Free()
{
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        pThreatsNormal_.erase(pThreatsNormal_.begin() + i);
    }

    pThreatsNormal_.clear();
}