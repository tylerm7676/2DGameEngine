#include <sstream>
#include "menu.h"

Menu::Menu(SDL_Renderer* rend) :
  renderer(rend),
  gdata(GameData::getInstance()),
  hudFrame({gdata.getXmlInt("Menu/loc/x"),
            gdata.getXmlInt("Menu/loc/y"),
            gdata.getXmlInt("Menu/width"),
            gdata.getXmlInt("Menu/height")}),
  backColor({(Uint8)gdata.getXmlInt("Menu/backColor/r"),
             (Uint8)gdata.getXmlInt("Menu/backColor/g"),
             (Uint8)gdata.getXmlInt("Menu/backColor/b"),
             (Uint8)gdata.getXmlInt("Menu/backColor/a")}),
  menuColor({(Uint8)gdata.getXmlInt("Menu/color/r"),
             (Uint8)gdata.getXmlInt("Menu/color/g"),
             (Uint8)gdata.getXmlInt("Menu/color/b"),
             (Uint8)gdata.getXmlInt("Menu/color/a")}),
  clock(Clock::getInstance()),
  io(IoMod::getInstance()),
  options(),
  optionLoc({gdata.getXmlInt("Menu/optionLoc/x"),
               gdata.getXmlInt("Menu/optionLoc/y")}),
  clicks({Sprite("clickOff"), Sprite("clickOn")}),
  currentClick(0),
  currentOption(0),
  noOfOptions(gdata.getXmlInt("Menu/noOfOptions")),
  spaces(gdata.getXmlInt("Menu/spaces")),
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
      std::string option("Menu/option" + strm.str());
      options.push_back(gdata.getXmlStr(option));
    }
  }

void Menu::incrIcon()
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

void Menu::decrIcon()
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

void Menu::drawBackground() const
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

void Menu::getControlEventLoop() const
{
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  drawBackground();
  std::string inNumber = " ";
  std::string msg = "Press return/esc when finished.";
  while(!done)
  {
    // The next loop polls for events, guarding against key bounce:
    while(SDL_PollEvent(&event))
    {
      keystate = SDL_GetKeyboardState(NULL);
      if(event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN)
      {
        if(keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_RETURN])
        {
          done = true;
          break;
        }
      }
      // In this section of the event loop we allow key bounce:
      drawBackground();
      io.writeText("Kill All Zombies to Win!", hudFrame.x + 540, hudFrame.y + 140);
      io.writeText("There are 10 waves of Zombies with increasing difficulty",
        hudFrame.x + 290, hudFrame.y + 240);
      io.writeText(msg, hudFrame.x + 500, hudFrame.y + 280);
      io.writeText(inNumber, hudFrame.x + 620, hudFrame.y + 340);
      io.writeText("Controls:", hudFrame.x + 600, hudFrame.y + 400);
      io.writeText("W: Up, A: Left, S: Down, D: Right, Space: Shoot Weapons, ESC: Pause/Buy Weapons, R: Reload, F1: Toggle HUDs",
      hudFrame.x + 100, hudFrame.y + 440);
      io.writeText("M: Toggle Music, Q or E: Cycle Weapons, Player must be facing a certain direction to shoot in that direction",
      hudFrame.x + 100, hudFrame.y + 480);
      SDL_RenderPresent(renderer);
    }
  }
}

void Menu::getControlMenu() const { getControlEventLoop(); }

void Menu::draw(int wave) const
{
  drawBackground();
  if(wave == 0)
  {
    io.writeText("Zombies Menu", hudFrame.x + 250, hudFrame.y + 125, true);
  }
  else
    io.writeText("Wave " + std::to_string(wave), hudFrame.x + 425, hudFrame.y + 125, true);
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
