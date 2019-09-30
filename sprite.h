#pragma once
#include <string>
#include "drawable.h"

class Sprite : public Drawable
{
  public:
    Sprite(const std::string& name) : Drawable(name) {}
    Sprite(const Sprite& s) : Drawable(s) {}
    virtual ~Sprite() { }
    virtual void update(Uint32 ticks);
    virtual void collide();
    void randomizeVelocity();
    void randomizePosition();
};
