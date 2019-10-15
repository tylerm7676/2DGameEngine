#include <sstream>
#include "buyMenu.h"

BuyMenu::BuyMenu(SDL_Renderer* rend) :
  renderer(rend),
  gdata(GameData::getInstance()),
  hudFrame({gdata.getXmlInt("BuyMenu/loc/x"),
            gdata.getXmlInt("BuyMenu/loc/y"),
            gdata.getXmlInt("BuyMenu/width"),
            gdata.getXmlInt("BuyMenu/height")}),
  backColor({(Uint8)gdata.getXmlInt("BuyMenu/backColor/r"),
             (Uint8)gdata.getXmlInt("BuyMenu/backColor/g"),
             (Uint8)gdata.getXmlInt("BuyMenu/backColor/b"),
             (Uint8)gdata.getXmlInt("BuyMenu/backColor/a")}),
  menuColor({(Uint8)gdata.getXmlInt("BuyMenu/color/r"),
             (Uint8)gdata.getXmlInt("BuyMenu/color/g"),
             (Uint8)gdata.getXmlInt("BuyMenu/color/b"),
             (Uint8)gdata.getXmlInt("BuyMenu/color/a")}),
  clock(Clock::getInstance()),
  io(IoMod::getInstance()),
  options(),
  optionLoc({gdata.getXmlInt("BuyMenu/optionLoc/x"),
               gdata.getXmlInt("BuyMenu/optionLoc/y")}),
  clicks({Sprite("clickOff"), Sprite("clickOn")}),
  currentClick(0),
  currentOption(0),
  noOfOptions(gdata.getXmlInt("BuyMenu/noOfOptions")),
  spaces(gdata.getXmlInt("BuyMenu/spaces")),
  startClickX(optionLoc[0] - spaces),
  startClickY(optionLoc[1] + spaces),
  clickX(startClickX),
  clickY(startClickY)
  {
    std::stringstream strm;
    for (int i = 0; i < noOfOptions; ++i)
    {
      strm.clear();
      strm.str("");
      strm << i;
      std::string option("BuyMenu/option" + strm.str());
      options.push_back(gdata.getXmlStr(option));
    }
  }

void BuyMenu::incrIcon()
{
  clickY += spaces;
  if(clickY > static_cast<int>(options.size()) * spaces + optionLoc[1])
  {
    clickY = startClickY;
    currentOption = 0;
  }
  else
    ++currentOption;
}

void BuyMenu::decrIcon()
{
  clickY -= spaces;
  if(clickY < spaces+optionLoc[1])
  {
    clickY = startClickY + (noOfOptions-1) * spaces;
    currentOption = options.size() - 1;
  }
  else
    --currentOption;
}

void BuyMenu::drawBackground() const
{
  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // Set the hud background color:
  SDL_SetRenderDrawColor(renderer, backColor.r, backColor.g, backColor.b,
    backColor.a);
  // Draw the filled rectangle:
  SDL_RenderFillRect(renderer, &hudFrame);
  // Set the  color for the Menu outline:
  SDL_Rect menuFrame = {hudFrame.x+50, hudFrame.y+40, hudFrame.w-100,
    hudFrame.h-100};
  SDL_SetRenderDrawColor(renderer, menuColor.r, menuColor.g, menuColor.b,
    menuColor.a);
  SDL_RenderFillRect(renderer, &menuFrame);

}

void BuyMenu::draw() const
{
  drawBackground();
  io.writeText("Buy Weapons", hudFrame.x + 260, hudFrame.y + 125, true);
  int space = spaces;
  for(const std::string& option : options)
  {
    io.writeText(option, optionLoc[0], optionLoc[1] + space);
    space += spaces;
  }
  // We have to draw the clickOn & clickOff relative to the screen,
  // and we don't want to offset by the location of the viewprot:
  clicks[currentClick].getImage()->draw(0, 0, clickX, clickY);
}
