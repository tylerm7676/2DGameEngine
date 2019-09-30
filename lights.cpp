#include <sstream>
#include "lights.h"
#include "gameData.h"
#include "ioMod.h"

Lights::Lights( ) :
  gdata( GameData::getInstance() ),
  renderer( IoMod::getInstance().getRenderer() ),
  viewWidth( gdata.getXmlInt("view/width") ),
  viewHeight( gdata.getXmlInt("view/height") ),
  diffuseGridX( gdata.getXmlInt("diffuseGrid/x") ),
  diffuseGridY( gdata.getXmlInt("diffuseGrid/y") ),
  lights()
{
  addLights();
}

Lights::~Lights( ) {
  std::cout << "Putting out the lights ..." << std::endl;
  std::list<Light*>::iterator ptr = lights.begin();
  while ( ptr != lights.end() ) {
    delete (*ptr);
    ++ptr;
  }
}

void Lights::addLight(const Triple& triple, int brightness) {
  lights.push_back(new Light( triple, brightness ) );
}

void Lights::addLights( ) {
  std::string thisLight("lightSpec/light");
  unsigned int numberOfLights = gdata.getXmlInt("numberOfLights");
  for (unsigned int i = 0; i < numberOfLights; ++i) {
    std::stringstream strm;
    strm << i+1;
    int x = gdata.getXmlInt(thisLight+"X"+strm.str());
    int y = gdata.getXmlInt(thisLight+"Y"+strm.str());
    int z = gdata.getXmlInt(thisLight+"Z"+strm.str());
    addLight( Triple(x, y, z), gdata.getXmlInt("brightness") );
  }
}

void Lights::draw( ) const {
  Light::drawIllumination(renderer, lights,
    viewWidth, viewHeight, diffuseGridX, diffuseGridY
  );
}

void Lights::update( ) const {
  std::list<Light*>::const_iterator ptr = lights.begin();
  while ( ptr != lights.end() ) {
    (*ptr)->update();
    ++ptr;
  }
}
