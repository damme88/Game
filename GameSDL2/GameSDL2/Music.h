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

static char gSMainFire[] = { "sound//fireball.wav"};
static char gSMainDeath[] = { "sound//death.wav"};
static char gSBulletCol[] = { "sound//blockhit.wav"};
static char gSCoinUp[] = {"sound//coin.wav"};
static char gSJump[] = {"sound//jump.wav"};
static char gSGameOver[] = {"sound//gameover.wav"};

class Music
{
public:
    Music();
    ~Music();

    enum SoundType
    {
        FIRE_SOUND = 0,
        POWER_UP = 1,
        EXP_SOUND = 2,
        DEATH_SOUND = 3,
        COIN_INCREASING = 4,
        JUMP_SOUND = 5,
        GAMEOVER_SOUND = 6,
    };

    static Music* GetInstance();
    bool Init();
    int PlaySoundGame(int soundType);
    int PlayMusic();
private:
    static Music* instance_;
};

#endif

