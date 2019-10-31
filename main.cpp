  #include "engine.h"
  #include <time.h>

  int main(int, char*[])
  {
  srand(time(NULL));
  bool keepPlaying = true;
  try
  {
    while(keepPlaying)
    {
      Engine engine;
      keepPlaying = engine.play();
      Clock::getInstance().startClock();
      SDL_Sound::getInstance().startMusic();
      HudObjPool::getInstance().setVisibility(false);
    }
  }
  catch (const string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return 0;
  }
