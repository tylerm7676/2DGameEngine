// The design and implementation of this light module, which includes
// lights, light, and triple, was originally contributed for SDL 1.2
// by Sean Kelly, Spring 2013.  The inspiration for the module was from
// Dr. Geist's graphics course, CpSc 405.
// The module was updated for SDL 2.0 by Brian and Chris Malloy.
// Brian and Chris also eliminated the dependence on open mp and
// on the gfx library; thus, no additional libraries are necessary
// to install and run this module.

#include <list>
#include <SDL.h>
#include "triple.h"
#include "light.h"

class Gamedata;

class Lights {
public:
  Lights();
  ~Lights();
  // Triple specifies the position of the light in (x, y, z)
  // The second parameter specifies brightness, where 2,000,000 is
  // somewhat dark!
  void draw() const;
  void update() const;
  void addLights();
  void addLight(const Triple& triple, int brightness);
private:
  GameData& gdata;
  SDL_Renderer* renderer;
  unsigned int viewWidth;
  unsigned int viewHeight;
  unsigned int diffuseGridX;
  unsigned int diffuseGridY;
  std::list<Light*> lights;
  Lights(const Lights&);
  Lights& operator=(const Lights&);
};
