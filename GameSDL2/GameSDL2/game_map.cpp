
#include "game_map.h"
#include <fstream>

GameMap* GameMap::instance_ = NULL;

GameMap::GameMap()
{
    game_map_ = new Map();
    game_map_->SetMaxX(MAX_MAP_X*TILE_SIZE);
    game_map_->SetMaxY(MAX_MAP_Y*TILE_SIZE);
}

GameMap::~GameMap()
{
    delete game_map_;
}

void GameMap::LoadMap(char* name)
{
    int tile_size = TILE_SIZE;

    std::fstream fsFile;
    fsFile.open(name, std::ios::in);
    if (fsFile.is_open() == true)
    {
        int ncount = 0;
        int idx_row = 0;  // run vertical based on height
        int idx_col = 0;  // run horizontal based on width

        std::string strData;
        while (std::getline(fsFile, strData))
        {
            int nSize = strData.size();
            if (nSize > 0)
            {
                std::vector<std::string> tile_list = SDLCommonFunc::SplitBySpace(strData);
                VT(BlockMap*) xTemp;
                for (int i = 0; i < tile_list.size(); ++i)
                {
                    std::string strTile = tile_list.at(i);
                    BlockMap* pBlock = new BlockMap();
                    int cx = idx_row*TILE_SIZE;
                    int cy = idx_col*TILE_SIZE;

                    pBlock->setType(strTile);
                    pBlock->setYIdx(cy);
                    pBlock->setXIdx(cx);
                    xTemp.push_back(pBlock);
                    idx_row++;
                }
                game_map_->AddList(xTemp);
                idx_row = 0;
                idx_col++;
            }
        }
    }

    fsFile.close();
    game_map_->SetFileMap((std::string)name);
}

void GameMap::LoadMapTiles(SDL_Renderer* screen)
{
    char* filename = NULL;
    VT(VT(BlockMap*)) dataMapList = game_map_->GetTile();
    int nRow = dataMapList.size();

    for (int y = 0; y < nRow; ++y)
    {
        VT(BlockMap*) dataMaps = dataMapList[y];
        int nCol = dataMaps.size();

        for (int x = 0; x < nCol; ++x)
        {
            BlockMap* pBlock = dataMaps[x];
            if (pBlock != NULL)
            {
                std::string type = pBlock->getType();
                std::string str = "map/" + type + ".bmp";

                filename = const_cast<char*>(str.c_str());
                TileMat* pTile = new TileMat();

                if (type == BLOCK_BIRCK_Q ||
                    type == BLOCK_COIN)
                {
                    pTile->SetIsClip(true);
                }
                bool ret = pTile->LoadImg(filename, screen);
                if (ret)
                {
                    pBlock->setTile(pTile);
                }
            }
        }
    }

#if T_USE_MUSH_ROOM
    BlockMap* pBlock = game_map_->GetTile()[6][7];
    pBlock->SetHasMushroom(true);
#endif

}

void GameMap::DrawMap(SDL_Renderer* des)
{
    int x1 = (game_map_->getStartX() % TILE_SIZE);
    int map_x = game_map_->getStartX() / TILE_SIZE;
    int map_y = game_map_->getStartY() / TILE_SIZE;
    for (int y_pos = 0; y_pos < SCREEN_HEIGHT; y_pos += TILE_SIZE)
    {
        // map theo chieu ngang, screen width chua phai la toan bo map, nen su dung <=
        for (int x_pos = 0; x_pos <= SCREEN_WIDTH; x_pos += TILE_SIZE)
        {
            if (map_x < MAX_MAP_X && map_y < MAX_MAP_Y)
            {
                BlockMap* pBlock = game_map_->GetTile()[map_y][map_x];
                if (pBlock != NULL && pBlock->GetTile() != NULL)
                {
                    // x_pos - x1, render tile lui 1 khoang x1, la phan du cua map da bi keo.
                    pBlock->setXpMap(x_pos - x1);
                    pBlock->setYpMap(y_pos);
                    pBlock->Update();
                    pBlock->Render(des);
                }
                map_x++;
            }
        }
        map_x = game_map_->getStartX() / TILE_SIZE;
        map_y++;
    }
}

bool GameMap::CheckCoinMap(const std::string& tile)
{
    bool bRet = false;
    int nSize = sizeof(CoinMap) / sizeof(CoinMap[0]);
    for (int i = 0; i < nSize; ++i)
    {
        std::string sType = CoinMap[i];
        std::string sInput(tile);
        if (sInput == sType)
        {
            bRet = true;
            break;
        }
    }

    return bRet;
}

bool GameMap::CheckSkipMap(const std::string& tile)
{
    bool bRet = false;
    int nSize = sizeof(SkipMap) / sizeof(SkipMap[0]);
    for (int i = 0; i < nSize; ++i)
    {
        std::string sType = SkipMap[i];
        std::string sInput(tile);
        if (sInput == sType)
        {
            bRet = true;
            break;
        }
    }

    return bRet;
}

bool GameMap::CheckBlank(const std::string& tile)
{
    if (tile == BLANK_TILE)
        return true;
    return false;
}

void GameMap::RenderBlockDe(SDL_Renderer* des)
{
    for (int i = 0; i < m_BlockDeList.size(); ++i)
    {
        BlockDebris* pBlockDe = m_BlockDeList.at(i);
        if (pBlockDe != NULL)
        {
            if (pBlockDe->GetDestroy() == false)
            {
                pBlockDe->Render(des);
            }
            else
            {
                delete pBlockDe;
                pBlockDe = NULL;
                m_BlockDeList.erase(m_BlockDeList.begin() + i);
            }
        }
    }
}