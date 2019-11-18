#include <string>
#include <iostream>
#include "sdl_sound.h"
using std::string;

SDL_Sound& SDL_Sound::getInstance()
{
  static SDL_Sound sound;
  return sound;
}

SDL_Sound::~SDL_Sound()
{
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  for (unsigned int i = 0; i < sounds.size(); ++i)
    Mix_FreeChunk(sounds[i]);
  Mix_CloseAudio();
}

SDL_Sound::SDL_Sound() :
  volume(SDL_MIX_MAXVOLUME),
  currentSound(-1),
  music(NULL),
  audioRate(22050),
  audioChannels(2),
  audioBuffers(4096),
  sounds(),
  channels()
  {
    if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, audioBuffers))
      throw string("Unable to open audio!");
    music = Mix_LoadMUS("sounds/Phantasm.mp3");
    if (!music)
      throw string("Couldn't load music.wav")+Mix_GetError();
    startMusic();
    sounds.push_back(Mix_LoadWAV("sounds/Splat.wav"));
    sounds.push_back(Mix_LoadWAV("sounds/9mm.wav"));
    sounds.push_back(Mix_LoadWAV("sounds/12Gauge.wav"));
    sounds.push_back(Mix_LoadWAV("sounds/garand_reload_clipin.wav"));
    for(unsigned int i = 0; i < sounds.size(); ++i)
      channels.push_back(i);
  }

void SDL_Sound::toggleMusic()
{
  if(Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
}

void SDL_Sound::operator[](int index)
{
  if (currentSound >= 0)
    Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume);
  channels[index] = Mix_PlayChannel(-1, sounds[index], 0);
}

void SDL_Sound::startMusic()
{
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDL_Sound::stopMusic()
{
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}
