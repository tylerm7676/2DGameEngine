#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include "vector2f.h"

class HudMain
{
  private:
    int width;
    int height;
    Vector2f pos;
    bool visible;
    SDL_Color backgroundColor;
    SDL_Color outlineColor;

    HudMain();
    HudMain(const HudMain&);
    HudMain& operator=(const HudMain&);

  public:
    static HudMain& getInstance();
    bool isVisible() const { return visible; }
    void setVisibility(bool v) { visible = v; }
    void draw();
};
