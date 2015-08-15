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

bool stringIsNotValidInteger(std::string str, int min, int max)
{
  return !stringIsValidInteger(str, min, max);
}

bool stringIsBlank(std::string str)
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

bool stringIsNotBlank(std::string str)
{
  return !stringIsBlank(str);
}

bool stringContains(std::string str, std::string c)
{
  return (static_cast<int>(str.find(c)) != -1);
}

bool stringDoesNotContains(std::string str, std::string c)
{
  return !stringContains(str, c);
}
