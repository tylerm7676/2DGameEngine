#include <string>
#include "image.h"
#include "viewport.h"

class World
{
  private:
    Image* const image;
    int factor;
    unsigned worldWidth;
    unsigned imageWidth;
    float viewX;
    float viewY;
    const Viewport & view;

  public:
    World(const std::string& name, int fact);
    World(const World&) = delete;
    World& operator=(const World&) = delete;
    // ~World() { } // The image will be deleted by the FrameFactory
    void update();
    void draw() const;
};
