#include <SDL_image.h>
#include <sstream>
#include <string>
#include <algorithm>
#include "hudObjPool.h"
#include "gameData.h"
#include "ioMod.h"

HudObjPool& HudObjPool::getInstance()
{
  static HudObjPool instance;
  return instance;
}

HudObjPool::HudObjPool() :
  width(GameData::getInstance().getXmlInt("hudObjPool/width")),
  height(GameData::getInstance().getXmlInt("hudObjPool/height")),
  pos(Vector2f(GameData::getInstance().getXmlInt("hudObjPool/position/x"),
               GameData::getInstance().getXmlInt("hudObjPool/position/y"))),
  visible(false),
  backgroundColor({
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/a")}),
  outlineColor({
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/outlineColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/outlineColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/outlineColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("hudObjPool/outlineColor/a")}) {}

void HudObjPool::draw(int numZombiesLeft, int wave)
{
  if (isVisible())
  {
    SDL_Rect r;
    r.x = pos[0];
    r.y = pos[1];
    r.w = width;
    r.h = height;

    SDL_Renderer* renderer = IoMod::getInstance().getRenderer();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g,
      backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g,
      outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &r);

    std::string textToWrite;
    textToWrite += "        OBJECT POOL";
    textToWrite += "\n Wave: " + std::to_string(wave);
    textToWrite += "\n Zombies Remaining: " + std::to_string(numZombiesLeft);

    IoMod::getInstance().writeTextWrapped(textToWrite, pos[0]+5, pos[1]+5,
      width);
  }
}
