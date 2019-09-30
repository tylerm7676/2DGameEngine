#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gameData.h"
#include "ioMod.h"

Clock& Clock::getInstance()
{
  static Clock clock;
  return clock;
}

Clock::Clock() :
  started(false),
  paused(false),
  FRAME_CAP_ON(GameData::getInstance().getXmlBool("frameCapOn")),
  PERIOD(GameData::getInstance().getXmlInt("period")),
  frames(0),
  timeAtStart(0),
  timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0)
  {
    startClock();
  }

Clock::Clock(const Clock& c) :
  started(c.started),
  paused(c.paused),
  FRAME_CAP_ON(c.FRAME_CAP_ON),
  PERIOD(c.PERIOD),
  frames(c.frames),
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks)
  {
    startClock();
  }

void Clock::toggleSloMo()
{
  throw( std::string("Slow motion is not implemented yet") );
}

unsigned int Clock::getTicks() const
{
  if(paused)
    return timeAtPause;
  else
    return SDL_GetTicks() - timeAtStart;
}

unsigned int Clock::getElapsedTicks()
{
  if (paused)
    return 0;
  currTicks = getTicks();
  ticks = currTicks-prevTicks;
  if(FRAME_CAP_ON)
  {
    // DO DELAY SO NOT TO OCCUPY CPU
    if (ticks < PERIOD)
      return 0;
    prevTicks = currTicks;
    return ticks;
  }
  else
  {
    prevTicks = currTicks;
    return ticks;
  }
}

int Clock::getFps() const
{
  if(getSeconds() > 0)
    return frames / getSeconds();
  else return 0;
}

void Clock::incrFrame()
{
  if(!paused)
    ++frames;
}

void Clock::startClock()
{
  started = true;
  paused = false;
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks();
  prevTicks = 0;
}

void Clock::pause()
{
  if(started && !paused)
  {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}

void Clock::unpause()
{
  if(started && paused)
  {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}
