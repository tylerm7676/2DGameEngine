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
  optionChoice(-1) {}

void BuyMenuEngine::draw(Player* player) const
{
  menu.draw(player);
  SDL_RenderPresent(renderer);
}

void BuyMenuEngine::update(Uint32) {}

void BuyMenuEngine::play(Player* player)
{
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  bool result;
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
          {
            result = player->purchasePistolAmmo();
            if(!result)
            {
              std::cout << "Ammo not purchased\n";
            }
            else
            {
              std::cout << "Ammo purchased\n";
            }
          }
          if(optionChoice == 1)
          {
            result = player->purchaseShotgun();
            if(!result)
            {
              std::cout << "Shotgun not purchased\n";
            }
            else
            {
              std::cout << "Shotgun purchased\n";
            }
          }
          if(optionChoice == 2)
          {
            result = player->purchaseShotgunAmmo();
            if(!result)
            {
              std::cout << "Ammo not purchased\n";
            }
            else
            {
              std::cout << "Ammo purchased\n";
            }
          }
          if(optionChoice == 3)
          {
            result = player->purchaseAssaultRifle();
            if(!result)
            {
              std::cout << "Assault Rifle not purchased\n";
            }
            else
            {
              std::cout << "Assault Rifle purchased\n";
            }
          }
          if(optionChoice == 4)
          {
            result = player->purchaseAssaultRifleAmmo();
            if(!result)
            {
              std::cout << "Ammo not purchased\n";
            }
            else
            {
              std::cout << "Ammo purchased\n";
            }
          }
        }
      }
      keystate = SDL_GetKeyboardState(NULL);
      if(event.type == SDL_KEYUP)
        menu.lightOff();
    }
    // In this section of the event loop we allow key bounce:
    draw(player);
  }
}
