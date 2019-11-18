#include <string>
#include <iostream>
#include "sound.h"
using std::string;

Sound::~Sound()
{
  for (unsigned int i = 0; i < sounds.size(); ++i)
    Mix_FreeChunk(sounds[i]);
  Mix_CloseAudio();
}

Sound::Sound() :
  volume(SDL_MIX_MAXVOLUME),
  currentSound(-1),
  audioRate(22050),
  audioChannels(2),
  audioBuffers(4096),
  sounds(),
  channels()
  {
    if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, audioBuffers))
      throw string("Unable to open audio!");
    sounds.push_back(Mix_LoadWAV("sounds/Splat.wav"));
    sounds.push_back(Mix_LoadWAV("sounds/9mm.wav"));
    sounds.push_back(Mix_LoadWAV("sounds/12Gauge.wav"));
    sounds.push_back(Mix_LoadWAV("sounds/garand_reload_clipin.wav"));
    for(unsigned int i = 0; i < sounds.size(); ++i)
      channels.push_back(i);
  }

void Sound::operator[](int index)
{
  if (currentSound >= 0)
    Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume);
  channels[index] = Mix_PlayChannel(-1, sounds[index], 0);
}
