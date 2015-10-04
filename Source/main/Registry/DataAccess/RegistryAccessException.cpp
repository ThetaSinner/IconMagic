/**
 * \file RegistryAccessException.cpp
 * \brief The RegistryAccessException class implementation.
 * \sa RegistryAccessException.hpp
 */

#include "./RegistryAccessException.hpp"

RegistryAccessException::RegistryAccessException(std::string message)
{
  exceptionMessage = message;
}

std::string RegistryAccessException::what()
{
  return exceptionMessage;
}
