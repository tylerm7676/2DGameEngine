#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "clock.h"
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
    int waveNum, wave1, wave1Slow, wave1Fast, wave2, wave2Slow, wave2Fast,
    wave3, wave3Slow, wave3Fast, wave4, wave4Slow, wave4Fast, wave5, wave5Slow,
    wave5Fast, wave6, wave6Slow, wave6Fast, wave7, wave7Slow, wave7Fast, wave8,
    wave8Slow, wave8Fast, wave9, wave9Slow, wave9Fast, wave10, wave10Slow, wave10Fast;
    //Lights lights;

    void draw();
    void update(Uint32);
    void checkForCollisions();
    void pause();

  public:
    Engine ();
    ~Engine ();
    bool play();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};
