/**
 * \file KeyService.cpp
 * \brief The KeyService class implementation.
 * \sa KeyService.hpp
 */

#include "./KeyService.hpp"

const std::map<std::string, std::string> KeyService::ALTERNATE_KEY_NAME_MAP = {
  {"classes_root", "HKEY_CLASSES_ROOT"},
  {"current_config", "HKEY_CURRENT_CONFIG"},
  {"current_user", "HKEY_CURRENT_USER"},
  {"local_machine", "HKEY_LOCAL_MACHINE"},
  {"users", "HKEY_USERS"}
};

const std::map<std::string, HKEY> KeyService::PREDEFINED_ROOT_KEYS = {
  {"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT},
  {"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
  {"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
  {"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE},
  {"HKEY_USERS", HKEY_USERS}
};

std::string KeyService::resolveName(std::string name)
{
  if (KeyService::ALTERNATE_KEY_NAME_MAP.find(name) != KeyService::ALTERNATE_KEY_NAME_MAP.end()) {
    name = KeyService::ALTERNATE_KEY_NAME_MAP.at(name);
  }

  if (KeyService::PREDEFINED_ROOT_KEYS.find(name) != KeyService::PREDEFINED_ROOT_KEYS.end()) {
    return name;
  }

  return "";
}

HKEY KeyService::getkeyByName(std::string name)
{
  if (KeyService::PREDEFINED_ROOT_KEYS.find(name) != KeyService::PREDEFINED_ROOT_KEYS.end()) {
    return KeyService::PREDEFINED_ROOT_KEYS.at(name);
  }

  return NULL;
}

HKEY KeyService::getKeyByAnyName(std::string name)
{
  return getkeyByName(resolveName(name));
}
