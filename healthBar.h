#include "SDL.h"
#include "gameData.h"

class HealthBar
{
  private:
    Vector2f barPos;
    Vector2f pos;
    bool visible;
    SDL_Renderer* renderer;
    int width;
    int height;
    int barWidth;
    int barHeight;
    SDL_Color barColor;
    SDL_Color backColor;
    SDL_Color backgroundColor;
    SDL_Color outlineColor;
    float currentLength;
    HealthBar();
    HealthBar(const HealthBar&);

  public:
    static HealthBar& getInstance();
    bool isVisible() const { return visible; }
    void setVisibility(bool v) { visible = v; }
    void draw(std::string) const;
    void reset() { currentLength = 1; }
    void setCurrentLength(float l) { currentLength = l; }
    float getCurrentLength() const { return currentLength; }
    HealthBar& operator=(const HealthBar&) = delete;
};
