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

    void draw(int) const;
    void update(Uint32);

  public:
    MenuEngine();
    ~MenuEngine();
    MenuEngine(const MenuEngine&) = delete;
    MenuEngine& operator=(const MenuEngine&) = delete;
    void play(int);
    int getOptionChoice() const { return optionChoice; }
    bool starsOptionChosen();
};
