#include <SDL_image.h>
#include "ioMod.h"
#include "gameData.h"
#include "renderContext.h"

IoMod& IoMod::getInstance()
{
  static IoMod instance;
  return instance;
}

IoMod::~IoMod()
{
  TTF_CloseFont(font);
  TTF_Quit();
}

IoMod::IoMod() : init(TTF_Init()),
  renderer( RenderContext::getInstance().getRenderer() ),
  font(TTF_OpenFont(GameData::getInstance().getXmlStr("font/file").c_str(),
                    GameData::getInstance().getXmlInt("font/size"))),
  bigFont(TTF_OpenFont(GameData::getInstance().getXmlStr("bigFont/file").c_str(),
                    GameData::getInstance().getXmlInt("bigFont/size"))),
  textColor({0xff, 0, 0, 0})
  {
    if(init == -1)
      throw std::string("error: Couldn't init font");
    if(font == NULL)
      throw std::string("error: font not found");
    textColor.r = GameData::getInstance().getXmlInt("font/red");
    textColor.g = GameData::getInstance().getXmlInt("font/green");
    textColor.b = GameData::getInstance().getXmlInt("font/blue");
    textColor.a = GameData::getInstance().getXmlInt("font/alpha");
  }

SDL_Texture* IoMod::readTexture(const std::string& filename)
{
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename.c_str());
  if(texture == NULL)
    throw std::string("Couldn't load ") + filename;
  return texture;
}

SDL_Surface* IoMod::readSurface(const std::string& filename)
{
  SDL_Surface *surface = IMG_Load(filename.c_str());
  if(!surface)
    throw std::string("Couldn't load ") + filename;
  return surface;
}

void IoMod::writeText(const std::string& msg, int x, int y) const
{
  SDL_Surface* surface = TTF_RenderText_Solid(font, msg.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeText(const std::string& msg, int x, int y,
  bool isBig) const
{
  if(!isBig)
    return;
  SDL_Surface* surface = TTF_RenderText_Solid(bigFont, msg.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeText(const std::string& msg, int x, int y,
  const SDL_Color& color) const
{
  SDL_Surface* surface = TTF_RenderText_Solid(font, msg.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextBold(const std::string& msg, int x, int y) const
{
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended(font, msg.c_str(), textColor);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextBold(const std::string& msg, int x, int y,
  SDL_Color& color) const
{
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended(font, msg.c_str(), color);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrapped(const std::string& msg, int x, int y,
  int wrapWidth) const
{
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, msg.c_str(),
    textColor, wrapWidth);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrapped(const std::string& msg, int x, int y,
  int wrapWidth, SDL_Color& color) const
{
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, msg.c_str(),
    color, wrapWidth);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrappedBold(const std::string& msg, int x, int y,
  int wrapWidth) const
{
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, msg.c_str(),
    textColor, wrapWidth);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrappedBold(const std::string& msg, int x, int y,
  int wrapWidth, SDL_Color& color) const
{
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, msg.c_str(),
    color, wrapWidth);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
  SDL_DestroyTexture(texture);
}
