#include <list>
#include <cmath>
#include "drawable.h"
#include "projectile.h"
#include "sound.h"

class SmartSprite;
class DumbSprite;

class Player : public Drawable
{
  private:
    enum Face {LEFT, RIGHT, UP, DOWN};
    Face facing;
    std::list<SmartSprite*> observers;
    bool collision;
    bool collided;
    bool colliding;
    Vector2f startingVelocity;
    float slowDownFactor;
    Sprite* explosion;
    float explosionStartTime;
    std::string projectileName;
    std::list<Projectile*> activeProjectiles;
    std::list<Projectile*> freeProjectiles;
    unsigned int initNumLives;
    unsigned int livesLeft;
    bool godMode;
    float minSpeed;
    float pistolInterval;
    float shotgunInterval;
    float assaultRifleInterval;
    float pistolReloadInterval;
    float shotgunReloadInterval;
    float assaultRifleReloadInterval;
    float timeSinceLastShot;
    float timeSinceLastPistolReload;
    float timeSinceLastShotgunReload;
    float timeSinceLastAssaultRifleReload;
    bool pistol;
    bool shotgun;
    bool assaultRifle;
    int pistolBulletsRemain;
    int pistolClip;
    int shotgunBulletsRemain;
    int shotgunClip;
    int assaultRifleBulletsRemain;
    int assaultRifleClip;
    bool pistolIsReloading;
    bool shotgunIsReloading;
    bool assaultRifleIsReloading;
    Sound sound;

    void advanceFrame(Uint32 ticks);

  public:
    Player(const std::string&);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    virtual ~Player() { }

    virtual void draw() const;
    virtual void update (Uint32 ticks);

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void stop();
    void attach(SmartSprite* o);
    void detach(SmartSprite* o);
    void collide();
    void shoot();

    std::list<Projectile*> getActiveProjectiles() const { return activeProjectiles; }
    std::list<Projectile*> getFreeProjectiles() const { return freeProjectiles; }
    unsigned int getLivesLeft() const { return livesLeft; }
    unsigned int getInitNumLives() const { return initNumLives; }
    bool hasCollided() const { return collided; }
    bool isColliding() const { return colliding; }
    void setCollided(bool b) { collided = b; }
    void loseLife() { --livesLeft; }
    bool isGodMode() const { return godMode; }
    void toggleGodMode() { godMode = !godMode; }
    void cycleLeft();
    void cycleRight();
    std::string getWeapon();
    void reload();
    void setReload();
    int getBulletsRemain();
    int getBulletsClip();
};
