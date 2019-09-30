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
    float shotgunInterval;
    float pistolInterval;
    float timeSinceLastShot;
    bool shotgun;
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
    void switchWeapons() { shotgun = !shotgun; }
    bool getWeapon() { return shotgun; }
};
