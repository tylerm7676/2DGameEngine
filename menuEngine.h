#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine
{
  private:
    Clock& clock;
    SDL_Renderer * const renderer;
    Menu menu;
    int optionChoice;
    bool starsOption;
    int numZombies;

    void draw() const;
    void update(Uint32);

  public:
    MenuEngine();
    ~MenuEngine();
    MenuEngine(const MenuEngine&) = delete;
    MenuEngine& operator=(const MenuEngine&) = delete;
    void play();
    int getOptionChoice() const { return optionChoice; }
    bool starsOptionChosen();
    int getNumZombies() const { return menu.getNumZombies(); }
};
