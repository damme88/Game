
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ExplosionObject.h"
#include "Music.h"
#include <vector>

#define PLAYER_SPEED        8
#define PLAYER_HIGHT_VAL    18
#define PLAYER_FRAMES       8

static char sPlayerAttack[] = { "img//sman_attack.png" };
static char sPlayerMove[] = {"img//sman_walk.png"};
static char sPlayerJump[] = {"img//sman_jump.png"};
static char sPlayerDown[] = {"img//player_down.png" };
static char sPlayerExp[] = { "img//player_exp.png" };
static char sPlayerDeath[] = {"img//sman_die.png" };

static char kImgBullet[] = {"img//sman_blast.png"};
static char kImgKni[] = { "img//sman_kn1.png" };

#define EPXILON 2

struct WorldData
{
public:
    enum WStatus
    {
        W_ACTIVE = 0,
        W_FINISHED = 1,
        W_PAUSE = 2,
    };
    UINT wld_number_;
    UINT wld_status_;
};

struct KnifeData
{
public:
    enum KStatus
    {
        W_ACTIVE = 0,
        W_UNACTIVE = 1,
    };

    INT kni_number_;
    UINT kni_status_;
};

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);

    void set_clips();
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events,
        SDL_Renderer* screen);

    void DoPlayer(SDL_Renderer* des);
    void CheckToMap(SDL_Renderer* des);
    void DoRight();
    void DoLeft();
    void DoUp();
    void DoDown();

    void DrawBound(SDL_Renderer* des);
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);

    int get_x_pos()       const { return x_pos_; }
    int get_y_pos()        const { return y_pos_; }
    int GetMoneyCount()    const { return m_CoinCount; };
    int get_frame_width()  const { return width_frame_; }
    int get_frame_height() const { return height_frame_; }
    bool get_is_falling() const { return is_falling_; }
    bool get_is_death() const { return is_death_; }
    int get_alive_time() const { return alive_time_; }
    int get_level_mushroom()const { return level_mushroom_; }
    VT(BulletObject*) get_bullet_list() const;
    SDL_Rect GetRectFrame();

    void setLevelMushroom() { level_mushroom_++; }
    void setXYPos(const int& xp, const int& yp) { x_pos_ = xp; y_pos_ = yp; }
    void set_is_falling(const bool& is_falling) { is_falling_ = is_falling; }
    void set_is_death(const bool& is_death) { is_death_ = is_death; }
    void set_alive_time(const int& live_time) { alive_time_ = live_time; }
    void SetCoinCount(const int& mCoin) { m_CoinCount = mCoin; }
    void DoUpCoin();
    void set_bullet_list(VT(BulletObject*) bullet_list);
    void InitExp(SDL_Renderer* des);
    void ResetAlive();
    void UpdateCtrlState(int ctrl_type, SDL_Renderer* screen);
    BlockMap* GetBlockMap(int y, int x);
    WorldData GetWorldData() const { return m_WorldData; }
    KnifeData GetKniData() { return m_SptKni; }
    void SetWorldData(WorldData wData) { m_WorldData = wData; }
    void SetInfoWorlData(int number, int status);
    bool CheckInputCondition();
    void ReStart();
    void SetInfoKni();
protected:
    void UpdateImagePlayer(SDL_Renderer* des);

private:
    bool m_bAttack;
    VT(BulletObject*) p_bullet_list_;
    SDL_Rect frame_clip_[8];
    Input input_type_;
    bool m_bSlopeMoving;
    //ExplosionObject exp_;
    //bool is_dead_boom_;
    bool is_jump_;
    bool on_ground_;
    bool is_falling_;
    bool is_death_;
    bool fast_run_;
    int level_mushroom_;

    int frame_;
    int status_;
    int start_map_x_;
    int start_map_y_;
    int width_frame_;
    int height_frame_;
    int m_CoinCount;
    int alive_time_;

    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;

    unsigned int iDelay[PLAYER_FRAMES];
    unsigned long passed_time_;
    WorldData m_WorldData;
    KnifeData m_SptKni;
};


#endif