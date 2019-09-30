#pragma once
#include <SDL.h>
#include <string>

class Engine;

class Clock
{
  private:
    friend class Engine;
    bool started;
    bool paused;
    const bool FRAME_CAP_ON;
    const Uint32 PERIOD;

    unsigned int frames;
    unsigned int timeAtStart;
    unsigned int timeAtPause;
    unsigned int currTicks;
    unsigned int prevTicks;
    unsigned int ticks;

    unsigned int getElapsedTicks();
    void incrFrame();
    void toggleSloMo();

    bool isStarted() const { return started; }
    bool isPaused() const  { return paused;  }
    unsigned int getFrames() const  { return frames;  }
    unsigned int capFrameRate() const;
    int getFps() const;

    void pause();
    void unpause();

    Clock();
    Clock(const Clock&);
    Clock&operator=(const Clock&);

  public:
    static Clock& getInstance();
    unsigned int getTicks() const;
    unsigned int getSeconds() const { return getTicks()/1000; }
    void startClock();
};
