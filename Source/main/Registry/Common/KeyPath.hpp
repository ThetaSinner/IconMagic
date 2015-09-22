#ifndef KEY_PATH_INCLUDED
#define KEY_PATH_INCLUDED

#include <vector>
#include <string>

class KeyPath
{
public:
  KeyPath(std::string key_name);
  KeyPath(const KeyPath& kp);

  KeyPath& append(std::string key_name);

  int getPathLength();
  std::string getKeyName(int index);

  std::string toString();
private:
  std::vector<std::string> keyNames;
};

#endif
