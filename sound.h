#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>

class Sound
{
  private:
    int volume;
    int currentSound;
    int audioRate;
    int audioChannels;
    int audioBuffers;
    std::vector<Mix_Chunk*> sounds;
    std::vector<int> channels;

  public:
    Sound();
    ~Sound();
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    void operator[](int);
};
