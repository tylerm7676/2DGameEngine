#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "gameData.h"
#include "engine.h"
#include "smartSprite.h"
#include "player.h"
#include "collisionStrategy.h"

Engine::~Engine()
{
  delete player;
  for (SmartSprite* ss : smartSprites)
    delete ss;
  delete collisionStrategy;
  std::cout << "terminating program..." << std::endl;
}

Engine::Engine() :
  rc(RenderContext::getInstance()),
  io(IoMod::getInstance()),
  clock(Clock::getInstance()),
  hudMain(HudMain::getInstance()),
  healthBar(HealthBar::getInstance()),
  hudObjPool(HudObjPool::getInstance()),
  gameOver(GameOver::getInstance()),
  viewport(Viewport::getInstance()),
  sound(SDL_Sound::getInstance()),
  renderer(rc.getRenderer()),
  world("back", GameData::getInstance().getXmlInt("back/factor")),
  player(new Player("Cowboy")),
  smartSprites(),
  collisionStrategy(new PerPixelCollisionStrategy),
  menuEngine(),
  numZombies(GameData::getInstance().getXmlInt("wave1/total")
    + GameData::getInstance().getXmlInt("wave2/total")
    + GameData::getInstance().getXmlInt("wave3/total")
    + GameData::getInstance().getXmlInt("wave4/total")
    + GameData::getInstance().getXmlInt("wave5/total")
    + GameData::getInstance().getXmlInt("wave6/total")
    + GameData::getInstance().getXmlInt("wave7/total")
    + GameData::getInstance().getXmlInt("wave8/total")
    + GameData::getInstance().getXmlInt("wave9/total")
    + GameData::getInstance().getXmlInt("wave10/total")),
  waveNum(0),
  wave1(GameData::getInstance().getXmlInt("wave1/total")),
  wave2(GameData::getInstance().getXmlInt("wave2/total")),
  wave3(GameData::getInstance().getXmlInt("wave3/total")),
  wave4(GameData::getInstance().getXmlInt("wave4/total")),
  wave5(GameData::getInstance().getXmlInt("wave5/total")),
  wave6(GameData::getInstance().getXmlInt("wave6/total")),
  wave7(GameData::getInstance().getXmlInt("wave7/total")),
  wave8(GameData::getInstance().getXmlInt("wave8/total")),
  wave9(GameData::getInstance().getXmlInt("wave9/total")),
  wave10(GameData::getInstance().getXmlInt("wave10/total")),
  result(0)
  //lights()
  {
    menuEngine.play(waveNum);
    waveNum++;
    smartSprites.reserve(numZombies);
    for(int i = 0; i < wave1; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
    Viewport::getInstance().setObjectToTrack(player);
    std::cout << "loading complete!" << std::endl;
  }

void Engine::draw()
{
  world.draw();
  for(const SmartSprite* s : smartSprites)
    s->draw();
  player->draw();
  //lights.draw();
  viewport.draw();
  hudMain.draw();
  hudObjPool.draw(smartSprites.size(), waveNum, player->getBulletsRemain(),
    player->getBulletsClip(), player->getMoney(), player->getPoints());
  healthBar.draw(player->getWeapon());
  if(player->getLivesLeft() <= 0)
  {
    hudMain.setVisibility(false);
    healthBar.setVisibility(false);
    hudObjPool.setVisibility(false);
    gameOver.setVisibility(true);
    gameOver.draw(false);
  }
  else if(smartSprites.size() <= 0 && waveNum == 1)
  {
    waveNum++;
    result = menuEngine.play(waveNum, player);
    if(result == 0)
      std::cout << "Nothing\n";
    if(result == 1)
      std::cout << "Purchase Pistol Ammo\n";
    if(result == 2)
      std::cout << "Purchase Shotgun\n";
    for(int i = 0; i < wave2; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 2)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave3; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 3)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave4; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 4)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave5; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 5)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave6; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 6)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave7; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 7)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave8; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 8)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave9; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 9)
  {
    waveNum++;
    menuEngine.play(waveNum);
    for(int i = 0; i < wave10; i++)
    {
      smartSprites.push_back(new SmartSprite("Zombie", player));
      smartSprites.back()->randomizeVelocity();
      smartSprites.back()->randomizePosition();
      player->attach(smartSprites[i]);
    }
  }
  else if(smartSprites.size() <= 0 && waveNum == 10)
  {
    hudMain.setVisibility(false);
    healthBar.setVisibility(false);
    hudObjPool.setVisibility(false);
    gameOver.setVisibility(true);
    gameOver.draw(true);
  }
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks)
{
  checkForCollisions();
  player->update(ticks);
  for(SmartSprite* s : smartSprites)
    s->update(ticks);
  world.update();
  //lights.update();
  viewport.update();
}

void Engine::checkForCollisions()
{
  auto it = smartSprites.begin();
  while(it != smartSprites.end())
  {
    if(!(player->getActiveProjectiles().empty()))
    {
      for(auto proj : player->getActiveProjectiles())
      {
        if (collisionStrategy->execute(*proj, **it))
        {
          (*it)->collide();
          proj->collide();
        }
      }
    }
    if ((collisionStrategy->execute(*player, **it)) && !(player->isColliding()))
      player->collide();
    if (player->hasCollided() && !(player->isColliding()))
    {
      player->loseLife();
      healthBar.setCurrentLength(healthBar.getCurrentLength() -
        (1.0 / player->getNumLives()));
      player->setCollided(false);
    }
    if((*it)->hasCollided() && (!((*it)->isColliding())))
    {
      SmartSprite* hitSmartSprite = *it;
      hitSmartSprite->loseLife();
      hitSmartSprite->setCollided(false);
      //hitSmartSprite->randomizeVelocity();
      hitSmartSprite->setVelocity(Vector2f(80, 80));
      if(hitSmartSprite->getNumLives() <= 0)
      {
        player->detach(hitSmartSprite);
        it = smartSprites.erase(it);
        delete hitSmartSprite;
      }
    }
    else
      ++it;
  }
}

bool Engine::play()
{
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  hudMain.setVisibility(true);
  healthBar.setVisibility(true);
  hudObjPool.setVisibility(true);
  while (!done)
  {
    while (SDL_PollEvent(&event))
    {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN)
      {
        if(keystate[SDL_SCANCODE_ESCAPE])
        {
          done = true;
          break;
        }
        if(keystate[SDL_SCANCODE_P])
        {
          if (clock.isPaused())
            clock.unpause();
          else
            clock.pause();
          sound.toggleMusic();
        }
        if(keystate[SDL_SCANCODE_F1])
        {
          hudMain.setVisibility(!hudMain.isVisible());
          healthBar.setVisibility(!healthBar.isVisible());
          hudObjPool.setVisibility(!hudObjPool.isVisible());
        }
        if(keystate[SDL_SCANCODE_SPACE])
          player->shoot();
        if(keystate[SDL_SCANCODE_Q])
          player->cycleLeft();
        if(keystate[SDL_SCANCODE_E])
          player->cycleRight();
        if(keystate[SDL_SCANCODE_R])
          player->setReload();
        if(keystate[SDL_SCANCODE_M])
          sound.toggleMusic();
        if(keystate[SDL_SCANCODE_X])
        {
          healthBar.reset();
          healthBar.setVisibility(false);
          clock.unpause();
          return true;
        }
        if(keystate[SDL_SCANCODE_G])
          player->toggleGodMode();
      }
    }
    ticks = clock.getElapsedTicks();
    keystate = SDL_GetKeyboardState(NULL);
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D])
        static_cast<Player*>(player)->moveLeft();
      if (keystate[SDL_SCANCODE_D] && !keystate[SDL_SCANCODE_A])
        static_cast<Player*>(player)->moveRight();
      if (keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S])
        static_cast<Player*>(player)->moveUp();
      if (keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_W])
        static_cast<Player*>(player)->moveDown();
      draw();
      update(ticks);
    }
  }
  return false;
}
