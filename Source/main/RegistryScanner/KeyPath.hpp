#ifndef KEY_PATH
#define KEY_PATH

#include <vector>
#include <string>

class KeyPath
{
public:
  KeyPath() {}
  KeyPath(std::string key_name);
  KeyPath(const KeyPath& kp);

  void append(std::string key_name);

  std::string getRootKeyName();

  int getPathLength();
  std::string getKeyName(int index);
private:
  std::vector<std::string> keyNames;
};

#endif
