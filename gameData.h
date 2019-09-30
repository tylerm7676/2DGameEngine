#pragma once
#include <string>
#include <map>
#include "vector2f.h"
#include "parseXML.h"

class GameData
{
  private:
    ParseXML parser;
    const map<std::string, std::string> gameData;
    GameData(const std::string& fn = "xmlSpec/game.xml");
    GameData(const GameData&);
    GameData& operator=(const GameData&);

  public:
    static GameData& getInstance();
    ~GameData();
    void displayData() const;
    bool getXmlBool(const std::string&) const;
    const std::string& getXmlStr(const std::string&) const;
    float getXmlFloat(const std::string&) const;
    int getXmlInt(const std::string&) const;
    float getRandInRange(int min, int max) const;
    float getRandFloat(float min, float max) const;
    bool  checkTag(const std::string&)const;
};
