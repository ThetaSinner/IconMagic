#ifndef KEY_PATH
#define KEY_PATH

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
