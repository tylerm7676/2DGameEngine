#include <sstream>
#include <string>
#include "healthBar.h"
#include "renderContext.h"
#include "ioMod.h"

HealthBar& HealthBar::getInstance()
{
  static HealthBar instance;
  return instance;
}

HealthBar::HealthBar() :
  barPos(Vector2f(GameData::getInstance().getXmlInt("healthBar/barPosition/x"),
  GameData::getInstance().getXmlInt("healthBar/barPosition/y"))),
  pos(Vector2f(GameData::getInstance().getXmlInt("healthBar/position/x"),
    GameData::getInstance().getXmlInt("healthBar/position/y"))),
  visible(false),
  renderer(RenderContext::getInstance().getRenderer()),
  width(GameData::getInstance().getXmlInt("healthBar/width")),
  height(GameData::getInstance().getXmlInt("healthBar/height")),
  barWidth(GameData::getInstance().getXmlInt("healthBar/barWidth")),
  barHeight(GameData::getInstance().getXmlInt("healthBar/barHeight")),
  barColor({(Uint8)GameData::getInstance().getXmlInt("healthBar/barColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("healthBar/barColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("healthBar/barColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("healthBar/barColor/a")}),
  backColor({(Uint8)GameData::getInstance().getXmlInt("healthBar/backColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("healthBar/backColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("healthBar/backColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("healthBar/backColor/a")}),
  backgroundColor({
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/backgroundColor/a")}),
  outlineColor({
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/r"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/g"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/b"),
    (Uint8)GameData::getInstance().getXmlInt("hudMain/outlineColor/a")}),
  currentLength(1.0) {}

void HealthBar::draw(bool shotgun) const
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

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, backColor.r, backColor.g, backColor.b,
        backColor.a);
    SDL_Rect barRect = {(int)barPos[0], (int)barPos[1], barWidth,
      barHeight};
    SDL_RenderFillRect(renderer, &barRect);
    SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b,
      barColor.a);
    SDL_Rect healthBarRect = {(int)barPos[0], (int)barPos[1], (int)(currentLength *
      barWidth), barHeight};
    SDL_RenderFillRect(renderer, &healthBarRect);
    SDL_RenderDrawRect(renderer, &barRect);

    std::string textToWrite;
    textToWrite += "                                                     ";
    textToWrite += "Health";
    textToWrite += "\n\n\n                                ";
    textToWrite += "Q or E to cycle weapons: ";
    if(shotgun)
      textToWrite += "Shotgun";
    else
      textToWrite += "Pistol";
    IoMod::getInstance().writeTextWrapped(textToWrite, pos[0]+5, pos[1]+10, width);
  }
}
