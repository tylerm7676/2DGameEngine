#include <cmath>
#include <random>
#include <functional>
#include "sprite.h"
#include "gameData.h"
#include "renderContext.h"
#include <time.h>

void Sprite::randomizeVelocity()
{
  float vx = getVelocityX();
  float vy = getVelocityY();
  float newvx = GameData::getInstance().getRandFloat(vx-50, vx+50);
  float newvy = GameData::getInstance().getRandFloat(vy-50, vy+50);
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  setVelocity(Vector2f(newvx, newvy));
}

void Sprite::randomizePosition()
{
  float px = getX();
  float py = getY();
  float newpx = GameData::getInstance().getRandFloat(px-50, px+50);
  float newpy = GameData::getInstance().getRandFloat(py-50, py+50);
  newpx *= [](){ if(rand()%2) return -1; else return 1; }();
  newpy *= [](){ if(rand()%2) return -1; else return 1; }();
  setPosition(Vector2f(newpx, newpy));
}

void Sprite::update(Uint32 ticks)
{
  setTimeSinceLastFrame(getTimeSinceLastFrame() + ticks);
  if(getTimeSinceLastFrame() > getFrameInterval())
  {
    if(isTwoWay())
    {
      if (getVelocityX() >= 0)
        setCurrentFrame(((getCurrentFrame()+1) % (getNumFrames()/2)));
      else
        setCurrentFrame((getNumFrames()/2) + ((getCurrentFrame()+1) % (getNumFrames()/2)));
    }
    else
      setCurrentFrame((getCurrentFrame()+1) % getNumFrames());
    setTimeSinceLastFrame(0);
  }
  setPosition(getPosition() + (getVelocity() * static_cast<float>(ticks) * 0.001));
  if (getY() < getminBoundY())
    setVelocityY(std::abs(getVelocityY()));
  if (getY() > getmaxBoundY() - getScaledHeight())
    setVelocityY(-std::abs(getVelocityY()));
  if ( getX() < getminBoundX())
    setVelocityX(std::abs(getVelocityX()));
  if ( getX() > getmaxBoundX() - getScaledWidth())
    setVelocityX(-std::abs(getVelocityX()));
}

void Sprite::collide()
{
  std::cout << "dumbSprite " << getName() << " collided" << std::endl;
}
