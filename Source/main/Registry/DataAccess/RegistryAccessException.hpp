#ifndef REGISTRY_ACCESS_EXCEPTION_INCLUDED
#define REGISTRY_ACCESS_EXCEPTION_INCLUDED

#include <exception>
#include <string>

class RegistryAccessException : public std::exception
{
  std::string exceptionMessage;

  public:

  RegistryAccessException(std::string message);

  std::string what();
};

#endif
