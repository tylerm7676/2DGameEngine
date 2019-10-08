#include <string>
#include "drawable.h"
#include "sound.h"

class Player;
class Sprite;

class SmartSprite : public Drawable
{
  private:
    enum Mode {EVADE, ATTACK};
    Mode currentMode;
    Vector2f playerPos;
    int playerWidth;
    int playerHeight;
    float safeDistance;
    bool collided;
    bool colliding;
    Sprite* explosion;
    float explosionStartTime;
    int numLives;
    int livesLeft;
    Sound sound;
    static int randomPos;

    void moveLeft()  { setVelocityX(-abs(getVelocityX()));  }
    void moveRight() { setVelocityX(fabs(getVelocityX()));  }
    void moveUp()    { setVelocityY(-fabs(getVelocityY())); }
    void moveDown()  { setVelocityY(fabs(getVelocityY()));  }
    void advanceFrame(Uint32);

  public:
    SmartSprite(const std::string&, const Player*);
    SmartSprite(const SmartSprite&) = delete;
    virtual ~SmartSprite() { }
    SmartSprite& operator=(const SmartSprite&) = delete;

    virtual void draw() const;
    virtual void update(Uint32 ticks);
    virtual void collide();

    const Vector2f& getPlayerPos() const { return playerPos; }
    int getPlayerWidth() const { return playerWidth; }
    int getPlayerHeight() const { return playerHeight; }
    float getSafeDistance() const { return safeDistance; }
    Mode getCurrentMode() const { return currentMode; }
    bool hasCollided() const { return collided; }
    bool isColliding() const { return colliding; }
    void setCollided(bool b) { collided = b; }
    void setColliding(bool b) { colliding = b; }

    void setPlayerPos(const Vector2f& p) { playerPos = p; }
    void setPlayerWidth(int w) { playerWidth = w; }
    void setPlayerHeight(int h) { playerHeight = h; }
    void setSafeDistance(float sd) { safeDistance = sd; }
    void switchMode()
    {
      if(currentMode == ATTACK)
        currentMode = EVADE;
      else
        currentMode = ATTACK;
    }
    void randomizeVelocity();
    void randomizePosition();
    void loseLife() { livesLeft--; }
    int getNumLives() { return livesLeft; }
};
