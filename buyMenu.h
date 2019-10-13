#include <vector>
#include <string>
#include "SDL.h"
#include "gameData.h"
#include "clock.h"
#include "ioMod.h"
#include "sprite.h"

class BuyMenu
{
  private:
    SDL_Renderer* renderer;
    GameData& gdata;
    SDL_Rect hudFrame;
    SDL_Color backColor;
    SDL_Color menuColor;
    Clock& clock;
    IoMod& io;
    std::vector<std::string> options;
    std::vector<int> optionLoc;
    std::vector<Sprite> clicks;
    int currentClick;
    int currentOption;
    int spaces;
    int startClickX;
    int startClickY;
    int clickX;
    int clickY;
    void drawBackground() const;
    //int getBuyEventLoop() const;

  public:
    BuyMenu(SDL_Renderer*);
    BuyMenu(const BuyMenu&) = delete;
    BuyMenu& operator=(const BuyMenu&) = delete;
    void draw() const;
    void update();
    void incrIcon();
    void decrIcon();
    void lightOn() { currentClick = 1; }
    void lightOff() { currentClick = 0; }
    int getOptionNo() const { return currentOption; }
    //int getBuyMenu() const;
};
