#include "ThreatsAds.h"
#include "GBMonster.h"
#include "TBoom.h"
#include "FlyMonster.h"

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
            if (obj_threat->GetType() == ThreatsObject::TH_GB_MONSTER)
            {
                GBMonster* pObject = static_cast<GBMonster*>(obj_threat);
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
    MakeGBMonster(screen);
    MakeGBTortoise(screen);
    MakeCrowMonster(screen);
#ifndef NO_BOOM
    pEx_ = new ExplosionObject();
    pEx_->LoadImg("img//exp5.png", screen);
    pEx_->set_clips();
#endif
}

void ThreatsAds::MakeGBMonster(SDL_Renderer* screen)
{
    UINT gbNum = sizeof(gbMonsterList) / sizeof(gbMonsterList[0]);
    if (gbNum > 0)
    {
        GBMonster* pGBList = new GBMonster[gbNum];
        for (int i = 0; i < gbNum; i++)
        {
            GBMonster* pGBMonster = (pGBList + i);
            if (pGBMonster != NULL)
            {
                pGBMonster->Init(GBMonster::GB_BASE, true, gbMonsterList[i], 4, screen);
                pThreatsNormal_.push_back(pGBMonster);
            }
        }
    }
}

void ThreatsAds::MakeGBTortoise(SDL_Renderer* screen)
{
    UINT gbNum = sizeof(gbTortoiseList) / sizeof(gbTortoiseList[0]);
    if (gbNum > 0)
    {
        GBMonster* pGBList = new GBMonster[gbNum];
        for (int i = 0; i < gbNum; i++)
        {
            GBMonster* pGBTortoise = (pGBList + i);
            if (pGBTortoise != NULL)
            {
                pGBTortoise->Init(GBMonster::GB_TORTOISE, true, gbTortoiseList[i], 4, screen);
                pThreatsNormal_.push_back(pGBTortoise);
            }
        }
    }
}

void ThreatsAds::MakeCrowMonster(SDL_Renderer* screen)
{
    UINT gbNum = sizeof(gbCrowListX) / sizeof(gbCrowListX[0]);
    if (gbNum > 0)
    {
        FlyMonster* pCrowList = new FlyMonster[gbNum];
        for (int i = 0; i < gbNum; i++)
        {
            FlyMonster* pCrow = (pCrowList + i);
            if (pCrow != NULL)
            {
                pCrow->Init(FlyMonster::FL_CROW, true, gbCrowListX[i], gbCrowListY[i], screen);
                pCrow->set_x_val(-5);
                pThreatsNormal_.push_back(pCrow);
            }
        }
    }
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
        if (obj_threat->GetType() == ThreatsObject::TH_GB_MONSTER)
        {
            GBMonster* pObject = static_cast<GBMonster*>(obj_threat);
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
        else if (obj_threat->GetType() == ThreatsObject::TH_FLY_MONSTER)
        {
            FlyMonster* pFlyObj = static_cast<FlyMonster*>(obj_threat);
            pFlyObj->DoPlayer();
            pFlyObj->Show(screen);
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

                        if (pThreat2->GetType() == ThreatsObject::TH_GB_MONSTER)
                        {
                            GBMonster* pGoombas = static_cast<GBMonster*>(pThreat2);
                            if (pGoombas != NULL)
                            {
                                ;// pGoombas->SetIsChange(true);
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