#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include "vector2f.h"

class GameOver
{
  private:
    int width;
    int height;
    Vector2f pos;
    bool visible;
    SDL_Color winBackgroundColor;
    SDL_Color winOutlineColor;
    SDL_Color winTextColor;
    SDL_Color loseBackgroundColor;
    SDL_Color loseOutlineColor;
    SDL_Color loseTextColor;

    GameOver();
    GameOver(const GameOver&);
    GameOver& operator=(const GameOver&);

  public:
    static GameOver& getInstance();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    const Vector2f& getPosition() const { return pos; }
    bool isVisible() const { return visible; }
    void setVisibility(bool v) { visible = v; }

    void draw(bool);
};
