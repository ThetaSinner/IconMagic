#include "./Util.hpp"

#include <sstream>
#include <exception>
#include <typeinfo>
#include <iostream>

bool stringIsValidInteger(std::string str, int min, int max)
{
  std::stringstream stream;
  stream << str;
  int i;
  try {
    if ((stream >> i).fail()) throw std::bad_cast();
  } catch (std::bad_cast& e) {
    std::cout << e.what();
    return false;
  }

  if (min < max)
  {
    if (min <= i && i <= max)  return true;
    else return false;
  }

  return true;
}

bool isStringBlank(std::string str)
{
  for (auto i : str)
  {
    if (!std::isspace(static_cast<int> (i)))
    {
      return false;
    }
  }

  return true;
}
