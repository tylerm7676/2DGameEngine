#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "sprite.h"
#include "gameData.h"
#include "buyMenuEngine.h"
#include "renderContext.h"

BuyMenuEngine::~BuyMenuEngine() {}

BuyMenuEngine::BuyMenuEngine() :
  clock( Clock::getInstance() ),
  renderer( RenderContext::getInstance().getRenderer() ),
  menu(renderer),
  optionChoice(-1),
  result(0) {}

void BuyMenuEngine::draw() const
{
  menu.draw();
  SDL_RenderPresent(renderer);
}

void BuyMenuEngine::update(Uint32) {}

int BuyMenuEngine::play(Player* player)
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
        if(keystate[SDL_SCANCODE_DOWN]) menu.incrIcon();
        if(keystate[SDL_SCANCODE_UP]) menu.decrIcon();
        if(keystate[SDL_SCANCODE_RETURN])
        {
          menu.lightOn();
          optionChoice = menu.getOptionNo();
          if(optionChoice == 0)
          {
            result = 1;
            done = true;
            break;
          }
          if(optionChoice == 1)
          {
            result = 2;
            done = true;
            break;
          }
          if(optionChoice == 2)
          {
            result = 3;
          }
        }
      }
      keystate = SDL_GetKeyboardState(NULL);
      if(event.type == SDL_KEYUP)
        menu.lightOff();
    }
    // In this section of the event loop we allow key bounce:
    draw();
  }
  return result;
}
