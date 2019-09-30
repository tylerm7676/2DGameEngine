#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class IoMod
{
  private:
    int init;
    SDL_Renderer* renderer;
    TTF_Font* font;
    TTF_Font* bigFont;
    SDL_Color textColor;
    IoMod();

  public:
    static IoMod& getInstance();
    IoMod(const IoMod&) = delete;
    IoMod& operator=(const IoMod&) = delete;
    ~IoMod();
    SDL_Texture* readTexture(const std::string& filename);
    SDL_Surface* readSurface(const std::string& filename);
    void writeText(const std::string&, int, int) const;
    void writeText(const std::string&, int, int, bool) const;
    void writeText(const std::string&, int, int, const SDL_Color&) const;
    void writeTextBold(const std::string&, int, int) const;
    void writeTextBold(const std::string&, int, int, SDL_Color&) const;
    void writeTextWrapped(const std::string&, int, int, int) const;
    void writeTextWrapped(const std::string&, int, int, int, SDL_Color&) const;
    void writeTextWrappedBold(const std::string&, int, int, int) const;
    void writeTextWrappedBold(const std::string&, int, int, int, SDL_Color&) const;
    SDL_Renderer* getRenderer() const { return renderer; }
};
