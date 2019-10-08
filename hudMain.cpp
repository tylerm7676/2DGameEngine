#include <SDL_image.h>
#include <sstream>
#include <string>
#include <algorithm>
#include "hudMain.h"
#include "gameData.h"
#include "ioMod.h"

HudMain& HudMain::getInstance()
{
  static HudMain instance;
  return instance;
}

HudMain::HudMain() :
  width(GameData::getInstance().getXmlInt("hudMain/width")),
  height(GameData::getInstance().getXmlInt("hudMain/height")),
  pos(Vector2f(GameData::getInstance().getXmlInt("hudMain/position/x"),
               GameData::getInstance().getXmlInt("hudMain/position/y"))),
  visible(false),
  backgroundColor({
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/a")}),
  outlineColor({
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/a")}) {}

void HudMain::draw()
{
  if(isVisible())
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
    textToWrite += "        CONTROLS";
    textToWrite += "\nWASD to move";
    textToWrite += "\nSPACE to shoot";
    textToWrite += "\nP to pause";
    textToWrite += "\nF1 to toggle HUDs";
    textToWrite += "\nM to toggle music";
    textToWrite += "\nR to Reload";
    textToWrite += "\nG to toggle God Mode";

    IoMod::getInstance().writeTextWrapped(textToWrite, pos[0]+5, pos[1]+5, width);
  }
}
