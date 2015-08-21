#include "./KeyPath.hpp"

KeyPath::KeyPath(std::string key_name)
{
  append(key_name);
}

KeyPath::KeyPath(const KeyPath& kp)
{
  this -> keyNames = std::vector<std::string>(kp.keyNames);
}

void KeyPath::append(std::string key_name)
{
  keyNames.push_back(key_name);
}

std::string KeyPath::getRootKeyName()
{
  return (getPathLength() ? keyNames[0] : "");
}

int KeyPath::getPathLength()
{
  return keyNames.size();
}

std::string KeyPath::getKeyName(int index)
{
  return (index < getPathLength() ? keyNames[index] : "");
}
