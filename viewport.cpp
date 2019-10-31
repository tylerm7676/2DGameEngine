#include <sstream>
#include "viewport.h"
#include "ioMod.h"

Viewport& Viewport::getInstance()
{
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() :
  gdata(GameData::getInstance()),
  position(0, 0),
  backgroundWidth(gdata.getXmlInt("back/width")),
  backgroundHeight(gdata.getXmlInt("back/height")),
  viewWidth(gdata.getXmlInt("view/width")),
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL) {}

void Viewport::setObjectToTrack(const Drawable *obj)
{
  objectToTrack = obj;
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {}

void Viewport::update()
{
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();
  position[0] = (x + objWidth/2) - viewWidth/2;
  position[1] = (y + objHeight/2) - viewHeight/2;
  if (position[0] < 0)
    position[0] = 0;
  if (position[1] < 0)
    position[1] = 0;
  if (position[0] > (backgroundWidth - viewWidth))
    position[0] = backgroundWidth - viewWidth;
  if (position[1] > (backgroundHeight - viewHeight))
    position[1] = backgroundHeight - viewHeight;
}
