#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "sprite.h"
#include "gameData.h"
#include "player.h"
#include "clock.h"

int SmartSprite::randomPos = 1;

void SmartSprite::advanceFrame(Uint32 ticks)
{
  setTimeSinceLastFrame(getTimeSinceLastFrame() + ticks);
  if(timeSinceLastFrame > frameInterval)
  {
    if(isTwoWay())
    {
      if(getVelocityX() > 0)
        currentFrame = (currentFrame+1) % leftFrames;
      if(getVelocityX() < 0)
        currentFrame = leftFrames + (currentFrame+1) % rightFrames;
      if(getVelocityY() < 0)
        currentFrame = leftFrames + rightFrames + (currentFrame+1) % upFrames;
      if(getVelocityY() > 0)
        currentFrame = leftFrames + rightFrames + upFrames + (currentFrame+1) % downFrames;
      timeSinceLastFrame = 0;
    }
    else
      setCurrentFrame((getCurrentFrame()+1) % getNumFrames());
    setTimeSinceLastFrame(0);
  }
  setPosition(getPosition() + (getVelocity() * static_cast<float>(ticks) * 0.001));
  if(getY() < getminBoundY())
    setVelocityY(std::abs(getVelocityY()));
  if(getY() > getmaxBoundY() - getScaledHeight())
    setVelocityY(-std::abs(getVelocityY()));
  if(getX() < getminBoundX())
    setVelocityX(std::abs(getVelocityX()));
  if(getX() > getmaxBoundX() - getScaledWidth())
    setVelocityX(-std::abs(getVelocityX()));
}

SmartSprite::SmartSprite(const std::string& name, const Player* p) :
  Drawable(name),
  currentMode(ATTACK),
  playerPos(p->getPosition()),
  playerWidth(p->getScaledWidth()),
  playerHeight(p->getScaledHeight()),
  safeDistance(GameData::getInstance().getXmlFloat(name+"/safeDistance")),
  collided(false),
  colliding(false),
  explosion(nullptr),
  explosionStartTime(-1),
  imageWidth(GameData::getInstance().getXmlInt(name+"/imageWidth")),
  imageHeight(GameData::getInstance().getXmlInt(name+"/imageHeight")),
  scale(GameData::getInstance().getXmlInt(name+"/scale")),
  lives(GameData::getInstance().getXmlInt(name+"/lives")),
  boss(false),
  sound() {}

void SmartSprite::randomizeVelocity()
{
  float vx = getVelocityX();
  float vy = getVelocityY();
  float newvx = GameData::getInstance().getRandFloat(vx, vx+70);
  float newvy = GameData::getInstance().getRandFloat(vy, vy+70);
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  setVelocity(Vector2f(newvx, newvy));
  //setVelocity(getVelocity());
}

void SmartSprite::randomizePosition()
{
  if(randomPos == 1)
  {
    setPosition(Vector2f(-300, 540));
    randomPos++;
    return;
  }
  if(randomPos == 2)
  {
    setPosition(Vector2f(960, -300));
    randomPos++;
    return;
  }
  if(randomPos == 3)
  {
    setPosition(Vector2f(1920, 540));
    randomPos++;
    return;
  }
  if(randomPos == 4)
  {
    setPosition(Vector2f(960, 1380));
    randomPos++;
    return;
  }
  if(randomPos == 5)
  {
    setPosition(Vector2f(-300, -300));
    randomPos++;
    return;
  }
  if(randomPos == 6)
  {
    setPosition(Vector2f(2220, -300));
    randomPos++;
    return;
  }
  if(randomPos == 7)
  {
    setPosition(Vector2f(2220, 1380));
    randomPos++;
    return;
  }
  if(randomPos == 8)
  {
    setPosition(Vector2f(-300, 1380));
    randomPos = 1;
    return;
  }
}

void SmartSprite::draw() const
{
  if(colliding)
    explosion->draw();
  else
    getImage()->draw(getX(), getY(), getScale());
}

void SmartSprite::update(Uint32 ticks)
{
  if(colliding)
  {
    explosion->update(ticks);
    if((Clock::getInstance().getSeconds() - explosionStartTime) >= 0.75)
    {
      colliding = false;
      delete explosion;
      explosion = NULL;
    }
    return;
  }
  else
  {
    advanceFrame(ticks);
    float x = getX() + getImage()->getWidth()/2;
    float y = getY() + getImage()->getHeight()/2;
    float ex = getPlayerPos()[0] + getPlayerWidth()/2;
    float ey = getPlayerPos()[1] + getPlayerHeight()/2;
    float distanceToEnemy = hypot((x-ex), (y-ey));

    if(currentMode == EVADE)
    {
      if(distanceToEnemy > safeDistance)
      currentMode = ATTACK;
      else
      {
        if(x < ex)
          moveLeft();
        if(x > ex)
          moveRight();
        if(y < ey)
          moveUp();
        if(y > ey)
          moveDown();
      }
    }
    else if(currentMode == ATTACK)
    {
      if(getX()-imageWidth+imageWidth*scale > getPlayerPos()[0])
        setVelocityX(-std::abs(getVelocityX()));
      if(getX()-imageWidth+imageWidth*scale < getPlayerPos()[0])
        setVelocityX(std::abs(getVelocityX()));
      if(getY()-imageHeight+imageHeight*scale > getPlayerPos()[1])
        setVelocityY(-std::abs(getVelocityY()));
      if(getY()-imageHeight+imageHeight*scale < getPlayerPos()[1])
        setVelocityY(std::abs(getVelocityY()));
    }
  }
}

void SmartSprite::collide()
{
  sound[0];
  collided = true;
  colliding = true;
  setVelocityX(0);
  setVelocityY(0);
  if(boss)
  {
    explosion = new Sprite("Explosion");
    explosion->setPosition(getPosition());
    explosion->setVelocityX(0);
    explosion->setVelocityY(0);
  }
  else
  {
    explosion = new Sprite("Explosion");
    explosion->setPosition(getPosition());
    explosion->setVelocityX(0);
    explosion->setVelocityY(0);
    setPosition(Vector2f(-100, -100));
    setVelocity(Vector2f(0, 0));
  }
  explosionStartTime = Clock::getInstance().getSeconds();
}
