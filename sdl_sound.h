#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>

class SDL_Sound
{
  private:
    int volume;
    int currentSound;
    Mix_Music *music;
    int audioRate;
    int audioChannels;
    int audioBuffers;
    std::vector<Mix_Chunk*> sounds;
    std::vector<int> channels;

    SDL_Sound();

  public:
    static SDL_Sound& getInstance();
    ~SDL_Sound();
    SDL_Sound(const SDL_Sound&) = delete;
    SDL_Sound& operator=(const SDL_Sound&) = delete;

    void startMusic();
    void stopMusic();
    void toggleMusic();
    void operator[](int);
};
