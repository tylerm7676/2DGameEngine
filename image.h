#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

class Image
{
  private:
    SDL_Renderer * renderer;
    SDL_Surface * surface;
    SDL_Texture * texture;
    SDL_Rect view;

  public:
    Image() = delete;
    Image( SDL_Surface*, SDL_Texture* );
    Image(const Image&);
    Image& operator=(const Image&);

    void draw(int x, int y) const;
    void draw(int x, int y, float scale) const;
    void draw(int sx, int sy, int dx, int dy) const;

    inline int getWidth()  const { return surface->w; }
    inline int getHeight() const { return surface->h; }
    SDL_Surface* getSurface() const { return surface; }
    Image* crop(SDL_Rect)const;
};
