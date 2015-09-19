#include "./KeyPath.hpp"

KeyPath::KeyPath(std::string key_name)
{
  append(key_name);
}

KeyPath::KeyPath(const KeyPath& kp)
{
  this -> keyNames = std::vector<std::string>(kp.keyNames);
}

KeyPath& KeyPath::append(std::string key_name)
{
  keyNames.push_back(key_name);
  return *this;
}

int KeyPath::getPathLength()
{
  return keyNames.size();
}

std::string KeyPath::getKeyName(int index)
{
  return (0 <= index && index < getPathLength() ? keyNames[index] : "");
}

std::string KeyPath::toString()
{
  std::string path = "";
  for (int i = 0; i < keyNames.size(); i++)
  {
    path += getKeyName(i) + "/";
  }
  path.pop_back();

  return path;
}
