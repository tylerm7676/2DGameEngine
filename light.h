#ifndef _LIGHT_H_
#define _LIGHT_H_

// This class is designed and implemented by Sean Kelly
// and is a tribute to Dr. Geist's 405 course

#include <cmath>
#include <iostream>
#include <list>
#include <vector>
#include "gameData.h"
#include "triple.h"

class polygon;
class Triple;

class Light {
public:
   Light(const Triple& il = Triple(0.0,0.0,1.0),
         double ib=0) :
      loc(il),
      translated(),
      brightness(ib),
      effectiveRad(sqrt(
        brightness/GameData::
        getInstance().getXmlFloat("noneffectiveLighting")))
      {}

   Light(std::string name) :
      loc(Triple(GameData::getInstance().getXmlFloat(name+"X"),
                 GameData::getInstance().getXmlFloat(name+"Y"),
                 GameData::getInstance().getXmlFloat(name+"Z"))),
      translated(),
      brightness(GameData::getInstance().getXmlFloat(name+"Bright")),
      effectiveRad(
        sqrt( brightness/GameData::getInstance().
              getXmlFloat("noneffectiveLighting"))
      )
      {}

   Light(const Light& l) : loc(l.loc), translated(),
         brightness(l.brightness), effectiveRad(l.effectiveRad)
         {}
   Light& operator=(const Light& l) {
      if (this != &l) {
         loc = l.loc;
         brightness = l.brightness;
         effectiveRad = l.effectiveRad;
      }
      return *this;
   }
   // ~Light() default destructor

   static void drawIllumination(SDL_Renderer *, const std::list<Light*>&,
      int, int, int, int);


   void update();
   std::vector<Triple> cons_shadow(const std::vector<Triple>& poly) const;
   double averageDistance(const std::vector<Triple>& verts) const;
   Uint8 shadowDarknessAtDistance(double d) const;


   const Triple& pos() const;
   void pos(const Triple& v) { loc = v; }
   double bright() const { return brightness; }

private:
   Triple loc;
   Triple translated;
   double brightness;

   double effectiveRad;
};


#endif
