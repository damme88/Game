#include "ThreatsAds.h"



ThreatsAds::ThreatsAds()
{
}


ThreatsAds::~ThreatsAds()
{

}


void ThreatsAds::BuildThreats(SDL_Renderer* screen)
{
    map_info_ = GameMap::GetInstance()->GetMap();
#ifdef USE_THREAT_PLANE
    ThreatsObject* plane_threat = new ThreatsObject();
    plane_threat->LoadImg(plane_img_name, screen);
    plane_threat->set_is_alive(true);
    plane_threat->set_xpos(SCREEN_WIDTH);
    plane_threat->set_ypos(50);
    plane_threat->set_x_val(3);
    plane_threat->set_type_move(ThreatsObject::MOVING_CONTINOUS);

    list_threats.push_back(plane_threat);
    BulletObject* p_bullet = new BulletObject();
    plane_threat->InitBullet(p_bullet, screen);
    pThreatsNormal_.push_back(plane_threat);
#endif

#ifndef USE_THREAT_SPACING
    ThreatsObject* thread_objs = new ThreatsObject[NUM_SPACE];

    for (int i = 0; i < NUM_SPACE; i++)
    {
        ThreatsObject* thread_obj = (thread_objs + i);
        if (thread_obj != NULL)
        {
            thread_obj->LoadImg(space_img_name, screen);
            thread_obj->InitPlayer();
            thread_obj->set_xpos(500 + i * 500);
            thread_obj->set_ypos(200);
            thread_obj->set_type_move(ThreatsObject::MOVE_IN_SPACE_TH);
            int pos1 = thread_obj->get_x_pos() - 60;
            int pos2 = thread_obj->get_x_pos() + 60;
            thread_obj->SetAnimationPos(pos1, pos2);

            pThreatsNormal_.push_back(thread_obj);
        }
    }

#endif

#ifdef USE_THREAT_STATIC
    ThreatsObject* thread_objs2 = new ThreatsObject[NUM_STATIC];
    for (int i = 0; i < NUM_STATIC; i++)
    {
        ThreatsObject* thread_obj3 = (thread_objs2 + i);
        if (thread_obj3 != NULL)
        {
            thread_obj3->LoadImg(static_img_name, screen);
            thread_obj3->InitPlayer();
            thread_obj3->set_input_left(0);
            thread_obj3->set_xpos(700 + i * 1500);
            thread_obj3->set_ypos(250);

            thread_obj3->set_type_move(ThreatsObject::STATIC_TH);

            BulletObject* p_bullet = new BulletObject();
            thread_obj3->InitBullet(p_bullet, screen);
            thread_obj3->set_is_alive(true);
            pThreatsNormal_.push_back(thread_obj3);
        }
    }
#endif
}


void ThreatsAds::Render(SDL_Renderer* screen)
{
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        ThreatsObject* obj_threat = pThreatsNormal_.at(i);

        obj_threat->SetMapXY(map_info_->getMaxX(), map_info_->getMaxY());
        obj_threat->ImpMoveType(screen);
        obj_threat->DoPlayer(map_info_);
        obj_threat->Show(screen);
        obj_threat->MakeBullet(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}


bool ThreatsAds::CheckCollision(SDL_Renderer* screen, const SDL_Rect& rect_object, const bool& checkBullet /*= false*/)
{
    bool bRet = false;
    for (int i = 0; i < pThreatsNormal_.size(); i++)
    {
        ThreatsObject* pThreat = pThreatsNormal_.at(i);
        if (pThreat)
        {
            bool bBulletCollision = false;
            if (checkBullet)
            {
                std::vector<BulletObject*> bullet_list = pThreat->get_bullet_list();
                for (int b = 0; b < bullet_list.size(); b++)
                {
                    BulletObject* p_bullet = bullet_list.at(b);
                    if (p_bullet)
                    {
                        bBulletCollision = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), rect_object);
                        if (bBulletCollision == true)
                        {
                            pThreat->Reset();
                            break;
                        }
                    }
                }
            }
            
            SDL_Rect rect = pThreat->GetRectFrame();
            bool bCollision = SDLCommonFunc::CheckCollision(rect_object, rect);

            if (bCollision || bBulletCollision)
            {
                if (bCollision)
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