
#include "game_map.h"
#include <fstream>

GameMap* GameMap::instance_ = NULL;

GameMap::GameMap()
{
    game_map_ = new Map();
}

GameMap::~GameMap()
{
    delete game_map_;
}

void GameMap::LoadMap(char* name)
{
    int nCount = MAX_MAP_X*TILE_SIZE;
    std::fstream fsFile;
    fsFile.open(name, std::ios::in);
    if (fsFile.is_open() == true)
    {
        int idx_row = 0;  // run vertical based on height
        int idx_col = 0;  // run horizontal based on width
        while (!fsFile.eof())
        {
            char* contentLine = new char[nCount];
            fsFile.getline(contentLine, nCount);
            std::string str(contentLine);
            std::vector<std::string> tile_list = SplitBySpace(str);
            delete[] contentLine;
            VT(BlockMap*) xTemp;
            for (int i = 0; i < tile_list.size(); ++i)
            {
                std::string strTile = tile_list.at(i);
                BlockMap* pBlock = new BlockMap();
                int cx = idx_row*TILE_SIZE;
                int cy = idx_col*TILE_SIZE;
                //if (val > 0)
                //{
                    pBlock->setType(strTile);
                    pBlock->setYIdx(cy);
                    pBlock->setXIdx(cx);
                //}
                xTemp.push_back(pBlock);
                idx_row++;
            }
            game_map_->AddList(xTemp);
        }
        idx_row = 0;
        idx_col++;
    }

    fsFile.close();
#if 0
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fp == NULL)
    {
        return;
    }

    for (int y = 0; y < MAX_MAP_Y; y++)
    {
        VT(BlockMap*) xTemp;
        for (int x = 0; x < MAX_MAP_X; x++)
        {
            BlockMap* pBlock = new BlockMap();
            int val = 0;
            fscanf_s(fp, "%d", &val);
            if (val > 0)
            {
                pBlock->setType(val);
                pBlock->setYIdx(y);
                pBlock->setXIdx(x);
            }
            xTemp.push_back(pBlock);
        }
        game_map_->AddList(xTemp);
    }
    //fclose(fp);
#endif
    game_map_->SetMaxX(MAX_MAP_X*TILE_SIZE);
    game_map_->SetMaxY(MAX_MAP_Y*TILE_SIZE);

    game_map_->SetFileMap((std::string)name);
}

std::vector<std::string> GameMap::SplitBySpace(std::string str)
{
    std::vector<std::string> list;
    std::string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            list.push_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }

    return list;
}

void GameMap::LoadMapTiles(SDL_Renderer* screen)
{
    char* filename = NULL;
    for (int y = 0; y < MAX_MAP_Y; y++)
    {
        for (int x = 0; x < MAX_MAP_X; x++)
        {
            BlockMap* pBlock = game_map_->GetTile()[y][x];
            if (pBlock != NULL)
            {
                std::string type = game_map_->GetTile()[y][x]->getType();
                std::string str = "map/" + type + ".png";
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
                    game_map_->GetTile()[y][x]->setTile(pTile);
                }
            }
        }
    }

    BlockMap* pBlock = game_map_->GetTile()[6][7];
    pBlock->SetHasMushroom(true);

}

void GameMap::DrawMap(SDL_Renderer* des)
{
    int map_x = 0;
    int x1 = 0;
    int x2 = 0;

    int map_y = 0;
    int y1 = 0;
    int y2 = 0;

    // map_x la vi tri tile hien tai
    map_x = game_map_->getStartX() / TILE_SIZE;

    // gia tri x1 la gia tri con thua sau phep chia
    x1 = (game_map_->getStartX() % TILE_SIZE);

    if (x1 == 0)
    {
        // neu phep chia co so du bang 0, nghia la start_x = nguyen lan TILE
        x2 = x1 + SCREEN_WIDTH;
    }
    else
    {
        // Neu phep co du > 0 thi cong them 1 TILE SIZE
        x2 = x1 + SCREEN_WIDTH + TILE_SIZE;
    }

    map_y = game_map_->getStartY() / TILE_SIZE;
    y1 = (game_map_->getStartY() % TILE_SIZE);

    if (y1 == 0)
    {
        y2 = y1 + SCREEN_HEIGHT;
    }
    else
    {
        y2 = y1 + SCREEN_HEIGHT + TILE_SIZE;
    }

    //gia tri am la de cac tile size hien thi khuat 1 phan ve ben trai, 
    // vi player di chuyen ve ben phai
    for (int y_pos = -y1; y_pos < y2; y_pos += TILE_SIZE)
    {
        map_x = game_map_->getStartX() / TILE_SIZE;
        for (int x_pos = -x1; x_pos < x2; x_pos += TILE_SIZE)
        {
            BlockMap* pBlock = game_map_->GetTile()[map_y][map_x];
            if (pBlock != NULL && pBlock->GetTile() != NULL)
            {
                pBlock->setXpMap(x_pos);
                pBlock->setYpMap(y_pos);
                pBlock->Update();
                pBlock->Render(des);
            }
            map_x++;
        }
        map_y++;
    }
}

bool GameMap::ChecTileMoney(const std::string& tile)
{
    if (tile == STATE_MONEY ||
        tile == STATE_MONEY)
    {
        return true;
    }
    return false;
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