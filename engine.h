#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "clock.h"
#include "hudMain.h"
#include "hudObjPool.h"
#include "gameOver.h"
#include "world.h"
#include "viewport.h"
#include "renderContext.h"
#include "sdl_sound.h"
#include "healthBar.h"
#include "menuEngine.h"
#include "lights.h"

class Player;
class SmartSprite;
class FallingSprite;
class CollisionStrategy;

class Engine
{
  private:
    const RenderContext& rc;
    const IoMod& io;
    Clock& clock;
    HudMain& hudMain;
    HealthBar& healthBar;
    HudObjPool& hudObjPool;
    GameOver& gameOver;
    Viewport& viewport;
    SDL_Sound& sound;
    SDL_Renderer* const renderer;
    World world;
    Player* player;
    std::vector<SmartSprite*> smartSprites;
    CollisionStrategy* collisionStrategy;
    MenuEngine menuEngine;
    int numZombies;
    int waveNum, wave1, wave2, wave3, wave4, wave5, wave6, wave7, wave8, wave9, wave10;
    int result;
    //Lights lights;

    void draw();
    void update(Uint32);
    void checkForCollisions();

  public:
    Engine ();
    ~Engine ();
    bool play();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};
