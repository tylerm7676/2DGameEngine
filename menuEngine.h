#include <vector>
#include <SDL.h>
#include "buyMenuEngine.h"

class MenuEngine
{
  private:
    Clock& clock;
    SDL_Renderer * const renderer;
    Menu menu;
    BuyMenuEngine buyMenuEngine;
    int optionChoice;

    void draw(int) const;
    void update(Uint32);

  public:
    MenuEngine();
    ~MenuEngine();
    MenuEngine(const MenuEngine&) = delete;
    MenuEngine& operator=(const MenuEngine&) = delete;
    void play(int, Player*);
    int getOptionChoice() const { return optionChoice; }
    bool starsOptionChosen();
};
