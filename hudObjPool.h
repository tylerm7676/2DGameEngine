#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include "vector2f.h"

class HudObjPool
{
  private:
    int width;
    int height;
    Vector2f pos;
    bool visible;
    SDL_Color backgroundColor;
    SDL_Color outlineColor;

    HudObjPool();
    HudObjPool(const HudObjPool&);
    HudObjPool& operator=(const HudObjPool&);

  public:
    static HudObjPool& getInstance();
    bool isVisible() const { return visible; }
    void setVisibility(bool v) { visible = v; }
    void draw(int, int, int, int);
};
