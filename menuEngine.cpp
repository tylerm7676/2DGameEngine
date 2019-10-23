#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "sprite.h"
#include "gameData.h"
#include "menuEngine.h"
#include "renderContext.h"

MenuEngine::~MenuEngine() {}

MenuEngine::MenuEngine() :
  clock(Clock::getInstance()),
  renderer(RenderContext::getInstance().getRenderer()),
  menu(renderer),
  buyMenuEngine(),
  optionChoice(-1) {}

void MenuEngine::draw(int wave) const
{
  menu.draw(wave);
  SDL_RenderPresent(renderer);
}

void MenuEngine::update(Uint32) {}

void MenuEngine::play(int wave, Player* player)
{
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  while(!done)
  {
    // The next loop polls for events, guarding against key bounce:
    while(SDL_PollEvent(&event))
    {
      keystate = SDL_GetKeyboardState(NULL);
      if(event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN)
      {
        if(keystate[SDL_SCANCODE_ESCAPE])
        {
          done = true;
          break;
        }
        if(keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
          menu.incrIcon();
        if(keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
          menu.decrIcon();
        if(keystate[SDL_SCANCODE_RETURN])
        {
          menu.lightOn();
          optionChoice = menu.getOptionNo();
          if(optionChoice == 0)
            done = true;
          if(optionChoice == 1)
          {
            buyMenuEngine.play(player);
          }
          if(optionChoice == 2)
            menu.getControlMenu();
        }
      }
      keystate = SDL_GetKeyboardState(NULL);
      if(event.type == SDL_KEYUP)
        menu.lightOff();
    }
    // In this section of the event loop we allow key bounce:
    draw(wave);
  }
}
