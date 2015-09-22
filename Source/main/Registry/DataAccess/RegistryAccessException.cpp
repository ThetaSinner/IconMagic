#include "./RegistryAccessException.hpp"

RegistryAccessException::RegistryAccessException(std::string message)
{
  exceptionMessage = message;
}

std::string RegistryAccessException::what()
{
  return exceptionMessage;
}
