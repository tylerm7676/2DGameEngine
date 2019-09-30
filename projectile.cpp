#include <cmath>
#include "projectile.h"

void Projectile::update(Uint32 ticks)
{
  timeSinceLastFrame += ticks;
  if(getVelocityX() < 0)
    currentFrame = (currentFrame+1) % leftFrames;
  if(getVelocityX() > 0)
    currentFrame = leftFrames + (currentFrame+1) % rightFrames;
  if(getVelocityY() < 0)
    currentFrame = leftFrames + rightFrames + (currentFrame+1) % upFrames;
  if(getVelocityY() > 0)
    currentFrame = leftFrames + rightFrames + upFrames + (currentFrame+1) % downFrames;
  timeSinceLastFrame = 0;
  setPosition(getPosition() + (getVelocity() * static_cast<float>(ticks) * 0.001));
  distance = (hypot(getX()-startingPos[0], getY()-startingPos[1]));
  if(distance > maxDistance)
    tooFar = true;
}
