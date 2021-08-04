#include "Music.h"


Music* Music::instance_ = NULL;

Music::Music()
{
    music_state_ = MS_STOP;
}


Music::~Music()
{

}

Music* Music::GetInstance()
{
    if (instance_ == NULL)
    {
        instance_ = new Music();
    }

    return instance_;
}

bool Music::Init()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == PT_FAILED)
    {
        return false;
    }

    gChunkBullet    = Mix_LoadWAV(gSMainFire);
    gChunkMainDeath = Mix_LoadWAV(gSMainDeath);
    gChunkBulletCol = Mix_LoadWAV(gSBulletCol);
    gChunkCoin      = Mix_LoadWAV(gSCoinUp);
    gChunkJump      = Mix_LoadWAV(gSJump);
    gChunkGameOver  = Mix_LoadWAV(gSGameOver);
    gChunkGoombassHaha = Mix_LoadWAV(gSGoombassSoundHaha);
    gChunkPause = Mix_LoadWAV(gSGamePause);
    gChunkBoom = Mix_LoadWAV(gSExpBoom);
    gChunkMushroom = Mix_LoadWAV(gSMushroom);
    gChunkMushroomMeat = Mix_LoadWAV(gSMushroomMeat);
    gChunkBlockDes = Mix_LoadWAV(gSBlocklDes);

    g_music = Mix_LoadMUS("sound//overworld.wav");
    if (gChunkBullet == NULL || gChunkMainDeath == NULL || 
        gChunkCoin == NULL || gChunkBulletCol == NULL || 
        gChunkJump == NULL || gChunkGoombassHaha == NULL ||
        gChunkPause == NULL || gChunkBoom == NULL ||
        gChunkMushroom == NULL || gChunkMushroomMeat == NULL ||
        gChunkBlockDes == NULL)
    {
        return false;
    }

    if (g_music == NULL)
    {
        return false;
    }

    return true;
}

int Music::PlaySoundGame(int soundType)
{
    return 0;
    int ret = 0;
    if (soundType == FIRE_SOUND)
    {
        ret = Mix_PlayChannel(-1, gChunkBullet, 0);
    }
    else if (soundType == POWER_UP)
    {
        ;// Mix_PlayChannel(-1, gc, 0);
    }
    else if (soundType == EXP_SOUND)
    {
        Mix_PlayChannel(-1, gChunkBulletCol, 0);
    }
    else if (soundType == DEATH_SOUND)
    {
        Mix_PlayChannel(-1, gChunkMainDeath, 0);
    }
    else if (soundType == COIN_INCREASING)
    {
        Mix_PlayChannel(-1, gChunkCoin, 0);
    }
    else if (soundType == JUMP_SOUND)
    {
        ;// Mix_PlayChannel(-1, gChunkJump, 0);
    }
    else if (soundType == GAMEOVER_SOUND)
    {
        Mix_PlayChannel(-1, gChunkGameOver, 0);
    }
    else if (soundType == GOOM_BASS_HAHA)
    {
        Mix_PlayChannel(-1, gChunkGoombassHaha, 0);
    }
    else if (soundType == GAME_PAUSE)
    {
        Mix_PlayChannel(-1, gChunkPause, 0);
    }
    else if (soundType == EXP_BOOM)
    {
        Mix_PlayChannel(-1, gChunkBoom, 0);
    }
    else if (soundType == MUSHROM_SHOW)
    {
        Mix_PlayChannel(-1, gChunkMushroom, 0);
    }
    else if (soundType == MUSHROOM_MEAT)
    {
        Mix_PlayChannel(-1, gChunkMushroomMeat, 0);
    }
    else if (soundType == BLOCK_DEBRIS)
    {
        Mix_PlayChannel(-1, gChunkBlockDes, 0);
    }
    return ret;
}

int Music::PlayMusic()
{
#if 0
    if (music_state_ == MS_STOP)
    {
        if (Mix_PlayMusic(g_music, -1) == PT_FAILED)
        {
            return PT_FAILED;
        }
        music_state_ = MS_PLAY;
    }
#endif
    return 0;
}

void Music::StopMusic()
{
    if (music_state_ != MS_STOP)
    {
        Mix_HaltMusic();
        music_state_ = MS_STOP;
    }
}

void Music::PauseMusic()
{
    if (music_state_ != MS_PAUSE)
    {
        Mix_PauseMusic();
        music_state_ = MS_PAUSE;
    }
    else
    {
        Mix_ResumeMusic();
        music_state_ = MS_PLAY;
    }
}