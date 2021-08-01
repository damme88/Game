
#include "BaseObject.h"

DataImg::DataImg()
{
    m_Color.r = 0;
    m_Color.g = 0;
    m_Color.b = 0;
    m_Color.a = 1;
}

DataImg::~DataImg()
{
    
}

bool DataImg::IsColorKey()
{
    if (m_Color.r == COLOR_KEY_R &&
        m_Color.g == COLOR_KEY_G &&
        m_Color.b == COLOR_KEY_B)
    {
        return true;
    }
    return false;
}

BaseObject::BaseObject()
{
  p_object_ = NULL;
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = 0;
  rect_.h = 0;
  m_Flip = false;
  m_angle_ = false;
  angle_ = 0.0;
}

BaseObject::~BaseObject()
{
  Free();

  if (m_pixelList.size() > 0)
  {
      for (int i = 0; i < m_pixelList.size(); i++)
      {
          VT(DataImg*) xList = m_pixelList.at(i);
          for (int j = 0; j < xList.size(); ++j)
          {
              DataImg*  pData = xList.at(j);
              if (pData != NULL)
              {
                  delete pData;
                  pData = NULL;
              }
          }
      }
      m_pixelList.clear();
  }
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen, const bool& bGetPixel)
{
  //The final texture
  Free();
  SDL_Texture* newTexture = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface != NULL )
  {
    //Color key image
    Uint32 uKey = SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
    SDL_SetColorKey(loadedSurface, SDL_TRUE, uKey);

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface );
    if(newTexture != NULL )
    {
      //Get image dimensions
      rect_.w = loadedSurface->w;
      rect_.h = loadedSurface->h;
    }

    if (bGetPixel == true)
    {
        if (m_pixelList.size() <= 0)
        {
            m_pixelList = GetPixelImg(loadedSurface, loadedSurface->w, loadedSurface->h);
        }
    }
    
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  p_object_ = newTexture;
  return p_object_ != NULL;
}

void BaseObject::Free()
{
  if(p_object_ != NULL)
  {
    SDL_DestroyTexture(p_object_);
    p_object_ = NULL;
    rect_.w = 0;
    rect_.h = 0;
  }
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/)
{
  SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h};
  if (clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  
  if (m_Flip == true)
  {
      SDL_RenderCopyEx(des, p_object_, clip, &renderQuad, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else if (m_angle_ = true)
  {
      SDL_RenderCopyEx(des, p_object_, clip, &renderQuad, angle_, NULL, SDL_FLIP_NONE);
  }
  else
  {
      SDL_RenderCopy(des, p_object_, clip, &renderQuad);
  }
}

void BaseObject::setColor(const Uint8& red, const Uint8& green, const Uint8& blue)
{
  SDL_SetTextureColorMod(p_object_, red, green, blue);
}

void BaseObject::setBlendMode(const SDL_BlendMode& blending)
{
  SDL_SetTextureBlendMode(p_object_, blending);
}

VT(VT(DataImg*)) BaseObject::GetPixelImg(SDL_Surface * pSurface, int width, int height)
{
    VT(VT(DataImg*)) pixelList;
    if (pSurface != NULL && pSurface->format != NULL)
    {
        int bpp = pSurface->format->BytesPerPixel;
        for (int y = 0; y < height; y++)
        {
            VT(DataImg*) xList;
            for (int x = 0; x < width; x++)
            {
                Uint8 *p = (Uint8 *)pSurface->pixels + y * pSurface->pitch + x * bpp;
                Uint32 data = 0;
                if (bpp == 1)
                {
                    data = *p;
                }
                else if (bpp == 2)
                {
                    data = *(Uint16 *)p;
                }
                else if (bpp == 3)
                {
                    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    {
                        data = p[0] << 16 | p[1] << 8 | p[2];
                    }
                    else
                    {
                        data = p[0] | p[1] << 8 | p[2] << 16;
                    }
                }
                else if (bpp == 4)
                {
                    data = *(Uint32 *)p;
                }
                else
                {
                    data = 0;
                }

                SDL_Color rgb;
                rgb.a = 1;
                SDL_GetRGB(data, pSurface->format, &rgb.r, &rgb.g, &rgb.b);
                DataImg* pData = new DataImg();
                pData->m_Color = rgb;
                xList.push_back(pData);
            }
            pixelList.push_back(xList);
        }
    }

    return pixelList;
}

DataImg* BaseObject::GetPixelPos(int x, int y)
{
    DataImg* pDataImg = NULL;
    
    if (y >= 0 && y < m_pixelList.size())
    {
        VT(DataImg*) xList = m_pixelList.at(y);
        if (x >= 0 && x < xList.size())
        {
            pDataImg = xList.at(x);
        }
    }
    
    return pDataImg;
}



void BaseObject::setAlpha(const Uint8& alpha)
{
  SDL_SetTextureAlphaMod(p_object_, alpha);
}