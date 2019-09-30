#include <sstream>
#include <iostream>
#include <limits>
#include <cmath>
#include <ctime>
#include "gameData.h"

GameData& GameData::getInstance()
{
  static GameData gameData;
  return gameData;
}

GameData::~GameData() {}

GameData::GameData(const string& fn) :
  parser(fn),
  gameData(parser.getXmlData()) {}

float GameData::getRandInRange(int min, int max) const
{
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

float GameData::getRandFloat(float min, float max) const
{
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}

bool  GameData::checkTag(const std::string& tag) const
{
  return gameData.count(tag) != 0;
}

bool GameData::getXmlBool(const string& tag) const
{
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if(ptr == gameData.end())
    throw string("Game: Didn't find boolean tag ")+tag+string(" in xml");
  else
  {
    if(ptr->second == "true")
      return true;
    else
      return false;
  }
}

int GameData::getXmlInt(const string& tag) const
{
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if(ptr == gameData.end())
    throw string("Game: Didn't find integer tag ") + tag + string(" in xml");
  else
  {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float GameData::getXmlFloat(const string& tag) const
{
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if(ptr == gameData.end())
    throw string("Game: Didn't find float tag ") + tag + string(" in xml");
  else
  {
    std::stringstream strm;
    strm << ptr->second;
    float data;
    strm >> data;
    return data;
  }
}

const string& GameData::getXmlStr(const string& tag) const
{
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if(ptr == gameData.end())
    throw string("Game: Didn't find string tag ")+tag+string(" in xml");
  else
    return ptr->second;
}

void GameData::displayData() const
{
  for(auto& ptr : gameData)
    std::cout << ptr.first << ", " << ptr.second << std::endl;
}
