#include "gameData.h"
#include "player.h"
#include "smartSprite.h"
#include "sprite.h"
#include "clock.h"

void Player::advanceFrame(Uint32 ticks)
{
  timeSinceLastFrame += ticks;
  timeSinceLastShot += ticks;
  if(pistolIsReloading)
  {
    timeSinceLastPistolReload += ticks;
    if(timeSinceLastPistolReload > pistolReloadInterval)
      reload();
  }
  if(shotgunIsReloading)
  {
    timeSinceLastShotgunReload += ticks;
    if(timeSinceLastShotgunReload > shotgunReloadInterval)
      reload();
  }
  if(assaultRifleIsReloading)
  {
    timeSinceLastAssaultRifleReload += ticks;
    if(timeSinceLastAssaultRifleReload > assaultRifleReloadInterval)
      reload();
  }
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
  if (getY() < getminBoundY())
    setVelocityY(0);
  if (getY() > getmaxBoundY() - getScaledHeight())
    setVelocityY(0);
  if ( getX() < getminBoundX())
    setVelocityX(0);
  if ( getX() > getmaxBoundX() - getScaledWidth())
    setVelocityX(0);
}

void Player::reload()
{
  sound[3];
  if(pistol && pistolAmmoTotal > 0)
  {
    if((pistolAmmoTotal + pistolAmmoInClip) < pistolClip)
    {
      pistolAmmoInClip += pistolAmmoTotal;
      pistolAmmoTotal = 0;
      timeSinceLastPistolReload = 0;
      pistolIsReloading = false;
      return;
    }
    else
    {
      pistolAmmoTotal -= (pistolClip - pistolAmmoInClip);
      pistolAmmoInClip = pistolClip;
      timeSinceLastPistolReload = 0;
      pistolIsReloading = false;
      return;
    }
  }
  if(shotgun && shotgunAmmoTotal > 0)
  {
    if((shotgunAmmoTotal + shotgunAmmoInClip) < shotgunClip)
    {
      shotgunAmmoInClip += shotgunAmmoTotal;
      shotgunAmmoTotal = 0;
      timeSinceLastShotgunReload = 0;
      shotgunIsReloading = false;
      return;
    }
    else
    {
      shotgunAmmoTotal -= (shotgunClip - shotgunAmmoInClip);
      shotgunAmmoInClip = shotgunClip;
      timeSinceLastShotgunReload = 0;
      shotgunIsReloading = false;
      return;
    }
  }
  if(assaultRifle && assaultRifleAmmoTotal > 0)
  {
    if((assaultRifleAmmoTotal + assaultRifleAmmoInClip) < assaultRifleClip)
    {
      assaultRifleAmmoInClip += assaultRifleAmmoTotal;
      assaultRifleAmmoTotal = 0;
      timeSinceLastAssaultRifleReload = 0;
      assaultRifleIsReloading = false;
      return;
    }
    else
    {
      assaultRifleAmmoTotal -= (assaultRifleClip - assaultRifleAmmoInClip);
      assaultRifleAmmoInClip = assaultRifleClip;
      timeSinceLastAssaultRifleReload = 0;
      assaultRifleIsReloading = false;
      return;
    }
  }
}

void Player::setReload()
{
  if(pistol && !pistolIsReloading && pistolAmmoInClip < pistolClip && pistolAmmoTotal > 0)
    pistolIsReloading = true;
  if(shotgun && !shotgunIsReloading && shotgunAmmoInClip < shotgunClip && shotgunAmmoTotal > 0)
    shotgunIsReloading = true;
  if(assaultRifle && !assaultRifleIsReloading && assaultRifleAmmoInClip < assaultRifleClip && assaultRifleAmmoTotal > 0)
    assaultRifleIsReloading = true;
}

Player::Player(const std::string& name) :
  Drawable(name),
  facing(RIGHT),
  observers(),
  collision(false),
  collided(false),
  colliding(false),
  velocity(getVelocity()),
  slowDownFactor(GameData::getInstance().getXmlFloat(name+"/slowDownFactor")),
  explosion(nullptr),
  explosionStartTime(-1),
  projectileName(GameData::getInstance().getXmlStr(name+"/projectileName")),
  activeProjectiles(),
  freeProjectiles(),
  numLives(GameData::getInstance().getXmlInt(name+"/lives")),
  livesLeft(GameData::getInstance().getXmlInt(name+"/lives")),
  minSpeed(GameData::getInstance().getXmlInt(projectileName+"/minSpeed")),
  pistolInterval(GameData::getInstance().getXmlInt(projectileName+"/pistolInterval")),
  shotgunInterval(GameData::getInstance().getXmlInt(projectileName+"/shotgunInterval")),
  assaultRifleInterval(GameData::getInstance().getXmlInt(projectileName+"/assaultRifleInterval")),
  pistolReloadInterval(GameData::getInstance().getXmlInt(projectileName+"/pistolReloadInterval")),
  shotgunReloadInterval(GameData::getInstance().getXmlInt(projectileName+"/shotgunReloadInterval")),
  assaultRifleReloadInterval(GameData::getInstance().getXmlInt(projectileName+"/assaultRifleReloadInterval")),
  timeSinceLastShot(0),
  timeSinceLastPistolReload(0),
  timeSinceLastShotgunReload(0),
  timeSinceLastAssaultRifleReload(0),
  pistol(true),
  shotgun(false),
  assaultRifle(false),
  pistolAmmoInClip(7),
  pistolAmmoTotal(70),
  pistolClip(GameData::getInstance().getXmlInt(projectileName+"/pistolClip")),
  pistolAmmoCost(GameData::getInstance().getXmlInt(projectileName+"/pistolAmmoCost")),
  pistolAmount(GameData::getInstance().getXmlInt(projectileName+"/pistolAmount")),
  shotgunAmmoInClip(0),
  shotgunAmmoTotal(0),
  shotgunClip(GameData::getInstance().getXmlInt(projectileName+"/shotgunClip")),
  shotgunCost(GameData::getInstance().getXmlInt(projectileName+"/shotgunCost")),
  shotgunAmmoCost(GameData::getInstance().getXmlInt(projectileName+"/shotgunAmmoCost")),
  shotgunAmount(GameData::getInstance().getXmlInt(projectileName+"/shotgunAmount")),
  assaultRifleAmmoInClip(0),
  assaultRifleAmmoTotal(0),
  assaultRifleClip(GameData::getInstance().getXmlInt(projectileName+"/assaultRifleClip")),
  assaultRifleCost(GameData::getInstance().getXmlInt(projectileName+"/assaultRifleCost")),
  assaultRifleAmmoCost(GameData::getInstance().getXmlInt(projectileName+"/assaultRifleAmmoCost")),
  assaultRifleAmount(GameData::getInstance().getXmlInt(projectileName+"/assaultRifleAmount")),
  pistolIsReloading(false),
  shotgunIsReloading(false),
  assaultRifleIsReloading(false),
  shotgunPurchased(false),
  assaultRiflePurchased(false),
  money(0),
  points(0),
  sound()
  {
    setVelocityX(0);
    setVelocityY(0);
  }

void Player::stop()
{
  setVelocity(Vector2f(0, 0));
}

void Player::moveLeft()
{
  if(livesLeft > 0)
  {
    if(getX() > getminBoundX())
      setVelocityX(-velocity[0]);
    facing = LEFT;
  }
}

void Player::moveRight()
{
  if(livesLeft > 0)
  {
    if(getX() < getmaxBoundX() - getScaledWidth())
      setVelocityX(velocity[0]);
    facing = RIGHT;
  }
}

void Player::moveUp()
{
  if(livesLeft > 0)
  {
    if(getY() > getminBoundY())
      setVelocityY(-velocity[1]);
    facing = UP;
  }
}

void Player::moveDown()
{
  if(livesLeft > 0)
  {
    if(getY() < getmaxBoundY() - getScaledHeight())
      setVelocityY(velocity[1]);
    facing = DOWN;
  }
}

void Player::draw() const
{
  if(colliding)
    explosion->draw();
  else
    getImage()->draw(getX(), getY(), getScale());
  for(const Projectile* projectile : activeProjectiles)
    projectile->draw();
}

void Player::update(Uint32 ticks)
{
  if(livesLeft <= 0)
    setY(-30000);
  if(collided && colliding)
  {
    explosion->update(ticks);
    activeProjectiles.clear();
    if((Clock::getInstance().getSeconds() - explosionStartTime) >= 0.01)
    {
      colliding = false;
      delete explosion;
      explosion = NULL;
    }
    return;
  }
  else
    advanceFrame(ticks);

  auto it = activeProjectiles.begin();
  while (it != activeProjectiles.end())
  {
    (*it)->update(ticks);
    if((*it)->isTooFar())
    {
      freeProjectiles.push_back(*it);
      it = activeProjectiles.erase(it);
    }
    it++;
  }
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while (ptr != observers.end())
  {
    (*ptr)->setPlayerPos(getPosition());
    ++ptr;
  }
  stop();
}

void Player::collide()
{
  sound[0];
  auto it = observers.begin();
  while(it != observers.end())
  {
    (*it)->switchMode();
    ++it;
  }
  collided = true;
  colliding = true;
  explosion = new Sprite("Explosion");
  explosion->setPosition(getPosition());
  explosion->setVelocityX(0);
  explosion->setVelocityY(0);
  explosionStartTime = Clock::getInstance().getSeconds();
}

void Player::attach(SmartSprite* o) { observers.push_back(o); }

void Player::detach(SmartSprite* o)
{
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while (ptr != observers.end())
  {
    if (*ptr == o)
    {
      ptr = observers.erase(ptr);
      money += 8;
      points += 8;
      return;
    }
    ++ptr;
  }

}

void Player::shoot()
{
  if((pistolAmmoInClip <= 0 && pistol) || pistolIsReloading)
    return;
  if((shotgunAmmoInClip <= 0 && shotgun) || shotgunIsReloading)
    return;
  if((assaultRifleAmmoInClip <= 0 && assaultRifle) || assaultRifleIsReloading)
    return;
  if(!collision)
  {
    if(pistol && timeSinceLastShot < pistolInterval)
      return;
    else if(shotgun && timeSinceLastShot < shotgunInterval)
      return;
    else if(assaultRifle && timeSinceLastShot < assaultRifleInterval)
      return;
    if(shotgun)
      sound[2];
    else
      sound[1];
    float x = getScaledWidth();
    float y = getScaledHeight()/2;
    if(freeProjectiles.size() < 3)
    {
      if(shotgun)
      {
        shotgunAmmoInClip--;
        Projectile *p1 = new Projectile(projectileName);
        Projectile *p2 = new Projectile(projectileName);
        Projectile *p3 = new Projectile(projectileName);
        if (getVelocityX() > 0 || facing == RIGHT)
        {
          p1->setPosition(getPosition() + Vector2f(3*x/4, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(minSpeed, -125));
          p2->setPosition(getPosition() + Vector2f(3*x/4, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(minSpeed, 0));
          p3->setPosition(getPosition() + Vector2f(3*x/4, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(minSpeed, 125));
        }
        if (getVelocityX() < 0 || facing == LEFT)
        {
          p1->setPosition(getPosition() + Vector2f(-x/4, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(-minSpeed, -125));
          p2->setPosition(getPosition() + Vector2f(-x/4, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(-minSpeed, 0));
          p3->setPosition(getPosition() + Vector2f(-x/4, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(-minSpeed, 125));
        }
        if(getVelocityY() > 0 || facing == DOWN)
        {
          p1->setPosition(getPosition()+ Vector2f(x/3, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(-125, minSpeed));
          p2->setPosition(getPosition()+ Vector2f(x/3, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(0, minSpeed));
          p3->setPosition(getPosition()+ Vector2f(x/3, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(125, minSpeed));
        }
        if(getVelocityY() > 0 || facing == UP)
        {
          p1->setPosition(getPosition()+Vector2f(x/3, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(-125, -minSpeed));
          p2->setPosition(getPosition()+Vector2f(x/3, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(0, -minSpeed));
          p3->setPosition(getPosition()+Vector2f(x/3, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(125, -minSpeed));
        }
        activeProjectiles.push_back(p1);
        activeProjectiles.push_back(p2);
        activeProjectiles.push_back(p3);
      }
      else
      {
        if(pistol)
          pistolAmmoInClip--;
        else
          assaultRifleAmmoInClip--;
        Projectile *p = new Projectile(projectileName);
        if (getVelocityX() > 0 || facing == RIGHT)
        {
          p->setPosition(getPosition() + Vector2f(3*x/4, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(minSpeed, 0));
        }
        if (getVelocityX() < 0 || facing == LEFT)
        {
          p->setPosition(getPosition() + Vector2f(-x/4, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(-minSpeed, 0));
        }
        if(getVelocityY() > 0 || facing == DOWN)
        {
          p->setPosition(getPosition()+ Vector2f(x/3, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(0, minSpeed));
        }
        if(getVelocityY() > 0 || facing == UP)
        {
          p->setPosition(getPosition()+Vector2f(x/3, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(0, -minSpeed));
        }
        activeProjectiles.push_back(p);
      }
    }
    else
    {
      if(shotgun)
      {
        shotgunAmmoInClip--;
        Projectile *p1 = new Projectile(projectileName);
        Projectile *p2 = new Projectile(projectileName);
        Projectile *p3 = new Projectile(projectileName);
        if (getVelocityX() > 0 || facing == RIGHT)
        {
          p1->setPosition(getPosition() + Vector2f(3*x/4, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(minSpeed, -125));
          p2->setPosition(getPosition() + Vector2f(3*x/4, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(minSpeed, 0));
          p3->setPosition(getPosition() + Vector2f(3*x/4, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(minSpeed, 125));
        }
        if (getVelocityX() < 0 || facing == LEFT)
        {
          p1->setPosition(getPosition() + Vector2f(-x/4, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(-minSpeed, -125));
          p2->setPosition(getPosition() + Vector2f(-x/4, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(-minSpeed, 0));
          p3->setPosition(getPosition() + Vector2f(-x/4, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(-minSpeed, 125));
        }
        if(getVelocityY() > 0 || facing == DOWN)
        {
          p1->setPosition(getPosition()+ Vector2f(x/3, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(-125, minSpeed));
          p2->setPosition(getPosition()+ Vector2f(x/3, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(0, minSpeed));
          p3->setPosition(getPosition()+ Vector2f(x/3, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(125, minSpeed));
        }
        if(getVelocityY() > 0 || facing == UP)
        {
          p1->setPosition(getPosition()+Vector2f(x/3, y));
          p1->setStartingPos(p1->getPosition());
          p1->setVelocity(getVelocity() + Vector2f(-125, -minSpeed));
          p2->setPosition(getPosition()+Vector2f(x/3, y));
          p2->setStartingPos(p2->getPosition());
          p2->setVelocity(getVelocity() + Vector2f(0, -minSpeed));
          p3->setPosition(getPosition()+Vector2f(x/3, y));
          p3->setStartingPos(p3->getPosition());
          p3->setVelocity(getVelocity() + Vector2f(125, -minSpeed));
        }
        activeProjectiles.push_back(p1);
        activeProjectiles.push_back(p2);
        activeProjectiles.push_back(p3);
      }
      else
      {
        if(pistol)
          pistolAmmoInClip--;
        else
          assaultRifleAmmoInClip--;
        Projectile *p = new Projectile(projectileName);
        if (getVelocityX() > 0 || facing == RIGHT)
        {
          p->setPosition(getPosition() + Vector2f(3*x/4, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(minSpeed, 0));
        }
        if (getVelocityX() < 0 || facing == LEFT)
        {
          p->setPosition(getPosition() + Vector2f(-x/4, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(-minSpeed, 0));
        }
        if(getVelocityY() > 0 || facing == DOWN)
        {
          p->setPosition(getPosition()+ Vector2f(x/3, y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(0, minSpeed));
        }
        if(getVelocityY() > 0 || facing == UP)
        {
          p->setPosition(getPosition()+Vector2f(x/3,y));
          p->setStartingPos(p->getPosition());
          p->setVelocity(getVelocity() + Vector2f(0, -minSpeed));
        }
        activeProjectiles.push_back(p);
      }
      timeSinceLastShot = 0;
    }
  }
}

void Player::cycleLeft()
{
  if(pistolIsReloading || shotgunIsReloading || assaultRifleIsReloading)
    return;
  if(pistol && !shotgunPurchased && !assaultRiflePurchased)
    return;
  if(pistol && shotgunPurchased && !assaultRiflePurchased)
  {
    pistol = false;
    shotgun = true;
  }
  else if(pistol && assaultRiflePurchased)
  {
    pistol = false;
    assaultRifle = true;
  }
  else if(shotgun)
  {
    pistol = true;
    shotgun = false;
  }
  else if(assaultRifle && shotgunPurchased)
  {
    shotgun = true;
    assaultRifle = false;
  }
  else if(assaultRifle && !shotgunPurchased)
  {
    pistol = true;
    assaultRifle = false;
  }
}

void Player::cycleRight()
{
  if(pistolIsReloading || shotgunIsReloading || assaultRifleIsReloading)
    return;
  if(pistol && !shotgunPurchased && !assaultRiflePurchased)
    return;
  if(pistol && shotgunPurchased)
  {
    pistol = false;
    shotgun = true;
  }
  else if(pistol && !shotgunPurchased && assaultRiflePurchased)
  {
    pistol = false;
    assaultRifle = true;
  }
  else if(shotgun && assaultRiflePurchased)
  {
    shotgun = false;
    assaultRifle = true;
  }
  else if(shotgun && !assaultRiflePurchased)
  {
    shotgun = false;
    pistol = true;
  }
  else if(assaultRifle)
  {
    pistol = true;
    assaultRifle = false;
  }
}

std::string Player::getWeapon()
{
  if(pistol)
    return "pistol";
  else if(shotgun)
    return "shotgun";
  else if(assaultRifle)
    return "assaultRifle";
  return " ";
}

int Player::getAmmoInClip()
{
  if(pistol)
    return pistolAmmoInClip;
  else if(shotgun)
    return shotgunAmmoInClip;
  else if(assaultRifle)
    return assaultRifleAmmoInClip;
  return 0;
}

int Player::getAmmoTotal()
{
  if(pistol)
    return pistolAmmoTotal;
  else if(shotgun)
    return shotgunAmmoTotal;
  else if(assaultRifle)
    return assaultRifleAmmoTotal;
  return 0;
}

bool Player::purchasePistolAmmo()
{
  if(money >= pistolAmmoCost)
  {
    pistolAmmoTotal += pistolAmount;
    money -= pistolAmmoCost;
    return true;
  }
  return false;
}

bool Player::purchaseShotgun()
{
  if(shotgunPurchased)
    return false;
  if(money >= shotgunCost)
  {
    shotgunAmmoTotal += shotgunAmount;
    money -= shotgunCost;
    shotgunPurchased = true;
    return true;
  }
  return false;
}

bool Player::purchaseShotgunAmmo()
{
  if(!shotgunPurchased)
    return false;
  if(money >= shotgunAmmoCost)
  {
    shotgunAmmoTotal += shotgunAmount;
    money -= shotgunAmmoCost;
    return true;
  }
  return false;
}

bool Player::purchaseAssaultRifle()
{
  if(assaultRiflePurchased)
    return false;
  if(money >= assaultRifleCost)
  {
    assaultRifleAmmoTotal += assaultRifleAmount;
    money -= assaultRifleCost;
    assaultRiflePurchased = true;
    return true;
  }
  return false;
}

bool Player::purchaseAssaultRifleAmmo()
{
  if(!assaultRiflePurchased)
    return false;
  if(money >= assaultRifleAmmoCost)
  {
    assaultRifleAmmoTotal += assaultRifleAmount;
    money -= assaultRifleAmmoCost;
    return true;
  }
  return false;
}
