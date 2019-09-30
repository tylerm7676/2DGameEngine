#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "vector2f.h"
#include "image.h"
#include "gameData.h"
#include "renderContext.h"

class Drawable
{
  protected:
    std::string name;
    std::vector<Image*> images;
    float scale;
    Vector2f position;
    Vector2f velocity;
    Vector2f minBound;
    Vector2f maxBound;
    unsigned numFrames;
    unsigned currentFrame;
    unsigned leftFrames;
    unsigned rightFrames;
    unsigned upFrames;
    unsigned downFrames;
    unsigned frameInterval;
    float timeSinceLastFrame;
    bool twoWay;

  public:
    Drawable(const std::string& n) :
      name(n),
      images(RenderContext::getInstance().getImages(name)),
      scale(GameData::getInstance().getXmlFloat(name+"/scale")),
      position(Vector2f(GameData::getInstance().getXmlInt(name+"/startPos/x"),
        GameData::getInstance().getXmlInt(name+"/startPos/y"))),
      velocity(Vector2f(GameData::getInstance().getXmlInt(name+"/startVel/x"),
        GameData::getInstance().getXmlInt(name+"/startVel/y"))),
      minBound(Vector2f(GameData::getInstance().getXmlInt(name+"/minBound/x"),
        GameData::getInstance().getXmlInt(name+"/minBound/y"))),
      maxBound(Vector2f(GameData::getInstance().getXmlInt(name+"/maxBound/x"),
        GameData::getInstance().getXmlInt(name+"/maxBound/y"))),
      numFrames(GameData::getInstance().getXmlInt(name+"/frames")),
      currentFrame(0),
      leftFrames(GameData::getInstance().getXmlInt(name+"/leftFrames")),
    	rightFrames(GameData::getInstance().getXmlInt(name+"/rightFrames")),
    	upFrames(GameData::getInstance().getXmlInt(name+"/upFrames")),
    	downFrames(GameData::getInstance().getXmlInt(name+"/downFrames")),
      frameInterval(GameData::getInstance().getXmlInt(name+"/frameInterval")),
      timeSinceLastFrame(0),
      twoWay(GameData::getInstance().getXmlBool(name+"/twoWay")) {}

    Drawable(const Drawable& s):
      name(s.name),
      images(s.images),
      scale(s.scale),
      position(s.position),
      velocity(s.velocity),
      minBound(s.minBound),
      maxBound(s.maxBound),
      numFrames(s.numFrames),
      currentFrame(s.currentFrame),
      leftFrames(s.leftFrames),
    	rightFrames(s.rightFrames),
    	upFrames(s.upFrames),
    	downFrames(s.downFrames),
      frameInterval(s.frameInterval),
      timeSinceLastFrame(s.timeSinceLastFrame),
      twoWay(s.twoWay) {}

    Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel) :
      name(n),
      images(RenderContext::getInstance().getImages(name)),
      scale(GameData::getInstance().getXmlFloat(name+"/scale")),
      position(pos),
      velocity(vel),
      minBound(Vector2f(GameData::getInstance().getXmlInt(name+"/minBound/x"),
        GameData::getInstance().getXmlInt(name+"/minBound/y"))),
      maxBound(Vector2f(GameData::getInstance().getXmlInt(name+"/maxBound/x"),
        GameData::getInstance().getXmlInt(name+"/maxBound/y"))),
      numFrames(GameData::getInstance().getXmlInt(name+"/frames")),
      currentFrame(0),
      leftFrames(GameData::getInstance().getXmlInt(name+"/leftFrames")),
    	rightFrames(GameData::getInstance().getXmlInt(name+"/rightFrames")),
    	upFrames(GameData::getInstance().getXmlInt(name+"/upFrames")),
    	downFrames(GameData::getInstance().getXmlInt(name+"/downFrames")),
      frameInterval(GameData::getInstance().getXmlInt(name+"/frameInterval")),
      timeSinceLastFrame(0),
      twoWay(GameData::getInstance().getXmlBool(name+"/twoWay")) {}

    virtual ~Drawable() {}

    virtual void update(Uint32 ticks) = 0;
    virtual void collide() = 0;
    virtual void draw() const { images[currentFrame]->draw(position[0], position[1], scale); }
    virtual void draw(Vector2f pos) const { images[currentFrame]->draw(pos[0], pos[1], scale); }
    int getScaledWidth() const { return getScale()*images[currentFrame]->getWidth(); }
    int getScaledHeight() const { return getScale()*images[currentFrame]->getHeight(); }
    const SDL_Surface* getSurface() const { return images[currentFrame]->getSurface(); }
    const Image* getImage() const { return images[currentFrame]; }
    float getScale() const { return scale; }
    const std::string& getName() const { return name; }
    const Vector2f& getVelocity() const { return velocity; }
    const Vector2f& getPosition() const { return position; }
    float getX() const { return position[0]; }
    float getY() const { return position[1]; }
    float getVelocityX() const { return velocity[0]; }
    float getVelocityY() const { return velocity[1]; }
    int getminBoundX() const { return minBound[0]; }
    int getminBoundY() const { return minBound[1]; }
    int getmaxBoundX() const { return maxBound[0]; }
    int getmaxBoundY() const { return maxBound[1]; }
    float getTimeSinceLastFrame() const { return timeSinceLastFrame; }
    unsigned getCurrentFrame() const { return currentFrame; }
    unsigned getNumFrames() const { return numFrames; }
    unsigned getFrameInterval() const { return frameInterval; }
    bool isTwoWay() const { return twoWay; }

    void setScale(float s) { scale = s; }
    void setName(const std::string& n) { name = n; }
    void setVelocity(const Vector2f& vel) { velocity = vel; }
    void setPosition(const Vector2f& pos) { position = pos; }
    void setX(float x) { position[0] = x; }
    void setY(float y) { position[1] = y; }
    void setVelocityX(float vx) { velocity[0] = vx; }
    void setVelocityY(float vy) { velocity[1] = vy; }
    void setminBoundX(float x) { minBound[0] = x; }
    void setminBoundY(float y) { minBound[1] = y; }
    void setmaxBoundX(float x) { maxBound[0] = x; }
    void setmaxBoundY(float y) { maxBound[1] = y; }
    void setTimeSinceLastFrame(float t)   { timeSinceLastFrame = t; }
    void setCurrentFrame(unsigned f)      { currentFrame = f; }
};
#endif
