#pragma once
#ifndef MUSIC_H_
#define MUSIC_H_

#include "CommonFunc.h"

static Mix_Music* g_music = NULL;
static Mix_Chunk* gChunkBullet = NULL;
static Mix_Chunk* gChunkMainDeath = NULL;
static Mix_Chunk* gChunkBulletCol = NULL;
static Mix_Chunk* gChunkCoin = NULL;
static Mix_Chunk* gChunkJump = NULL;
static Mix_Chunk* gChunkGameOver = NULL;
static Mix_Chunk* gChunkGoombassHaha = NULL;
static Mix_Chunk* gChunkPause = NULL;
static Mix_Chunk* gChunkBoom = NULL;
static Mix_Chunk* gChunkMushroom = NULL;
static Mix_Chunk* gChunkMushroomMeat = NULL;
static Mix_Chunk* gChunkBlockDes = NULL;

static char gSMainFire[] = { "sound//fireball.wav"};
static char gSMainDeath[] = { "sound//death.wav"};
static char gSBulletCol[] = { "sound//blockhit.wav"};
static char gSCoinUp[] = {"sound//coin.wav"};
static char gSJump[] = {"sound//jump.wav"};
static char gSGameOver[] = {"sound//gameover.wav"};
static char gSGamePause[] = { "sound//pause.wav" };
static char gSGoombassSoundHaha[] = { "sound//goombas_haha.wav" };
static char gSExpBoom[] = { "sound//Bomb2.wav" };
static char gSMushroom[] = { "sound//mushroomappear.wav" };
static char gSMushroomMeat[] = { "sound//mushroomeat.wav" };
static char gSBlocklDes[] = { "sound//blockbreak.wav" };

class Music
{
public:
    Music();
    ~Music();

    enum SoundType
    {
        FIRE_SOUND  = 0,
        POWER_UP    = 1,
        EXP_SOUND   = 2,
        DEATH_SOUND = 3,
        COIN_INCREASING = 4,
        JUMP_SOUND  = 5,
        GAMEOVER_SOUND = 6,
        GAME_PAUSE  = 7,
        EXP_BOOM    = 8,
        MUSHROM_SHOW = 9,
        MUSHROOM_MEAT = 10,
        BLOCK_DEBRIS = 11,
    };

    enum GoomBassType
    {
        GOOM_BASS_HAHA = 50,
    };

    enum MusicState
    {
        MS_PLAY = 0,
        MS_STOP = 1,
        MS_PAUSE = 2,
    };

    static Music* GetInstance();
    bool Init();
    int PlaySoundGame(int soundType);
    int PlayMusic();
    void StopMusic();
    void PauseMusic();
    int GetMusicState() const { music_state_; };
    void SetMusicState(int state) { music_state_ = state; }

private:
    static Music* instance_;
    int music_state_;
};

#endif

