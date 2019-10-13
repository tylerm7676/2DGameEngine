#include <vector>
#include <SDL.h>
#include "buyMenu.h"
#include "menu.h"
#include "player.h"

class BuyMenuEngine
{
  private:
    Clock& clock;
    SDL_Renderer * const renderer;
    BuyMenu menu;
    int optionChoice;
    int result;

    void draw() const;
    void update(Uint32);

  public:
    BuyMenuEngine();
    ~BuyMenuEngine();
    BuyMenuEngine(const BuyMenuEngine&) = delete;
    BuyMenuEngine& operator=(const BuyMenuEngine&) = delete;
    int play(Player* player);
    int getOptionChoice() const { return optionChoice; }
    bool starsOptionChosen();
    void resetResult() { result = 0; }
};
