#include <SDL.h>
#include <cmath>
#include <cstdlib>
#include <string>

#include "triple.h"
#include "light.h"
#include "viewport.h"


void Light::drawIllumination(SDL_Renderer *s, const std::list<Light*>& ll,
        int w_wid, int w_hgt, int dif_grid_wid, int dif_grid_hgt) {
    // Now let's get some diffuse Lighting going

    SDL_BlendMode oldBlendMode;
    SDL_GetRenderDrawBlendMode(s, &oldBlendMode);
    SDL_SetRenderDrawBlendMode(s, SDL_BLENDMODE_MOD);

    int currX, currY;
    Uint8 brightness;
    double dist, fals_brig;

    for (currX = 0; currX < w_wid; currX += dif_grid_wid) {
        for (currY = 0; currY < w_hgt; currY += dif_grid_hgt) {
            // Select center
            double cX = currX + dif_grid_wid / 2;
            double cY = currY + dif_grid_hgt / 2;
            Triple cent(cX, cY, 0.0);
            double bright_accum = 0;
            std::list<Light*>::const_iterator plitr;
            for(plitr = ll.begin(); plitr != ll.end(); plitr++) {
                const Light& currLight = *(*plitr);
                const Triple& foreLight_pos = currLight.pos();
                dist = (foreLight_pos - cent).len();

                fals_brig = currLight.bright() / (dist*dist);
                bright_accum += fals_brig;
            }
            bright_accum = bright_accum > 255? 255.0 :
            bright_accum < 0? 0 : bright_accum;

            brightness = (Uint8) bright_accum;
            SDL_SetRenderDrawColor(s, brightness, brightness, brightness, 255);
            SDL_Rect region{currX, currY, dif_grid_wid, dif_grid_hgt};
            SDL_RenderFillRect(s, &region);
        }
    }
    SDL_SetRenderDrawBlendMode(s, oldBlendMode);
}

void Light::update() {
  const Drawable* obj = Viewport::getInstance().getObjectToTrack();
  double objX = obj->getX() + obj->getScaledWidth()/2 - loc.getX();
  double objY = obj->getY() + obj->getScaledHeight()/2 - loc.getY();
  double nx = objX + loc.getX() - Viewport::getInstance().getX();
  double ny = objY + loc.getY() - Viewport::getInstance().getY();
  translated = Triple(nx, ny, loc.getZ());
}

const Triple& Light::pos() const {
   return translated;
}

double Light::averageDistance(const std::vector<Triple>& verts) const {
   double dist = 0;
   for (unsigned i = 0; i < verts.size(); i++) {
      Triple r = verts[i] - pos();
      dist += r.len();
   }
   dist /= (double) verts.size();
   return dist;
}

Uint8 Light::shadowDarknessAtDistance(double d) const {
   double maxUint = 255.0;
   double scale = d / effectiveRad;
   // The ambient factor effects the brightness of the light:
   scale = scale*scale +
           GameData::getInstance().getXmlInt("ambientLighting");
   double brightness = (-maxUint)*(scale * scale) + maxUint;
   brightness = brightness < 0? 0 : brightness;
   return (Uint8) brightness;
}
