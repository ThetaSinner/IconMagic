#ifndef FRAMEWORK_HPP_INCLUDED
#define FRAMEWORK_HPP_INCLUDED

#include <functional>
#include <list>
#include <vector>

class TestFramework
{
public:
  void addTest(std::function<bool(void)> testFunction);
  bool execute();

  bool getTestsStatus();
  int getTotalTestsRun();
  int getTotalTestsRunSuccessfully();

  TestFramework();
  ~TestFramework();
private:
std::list<std::function<bool(void)> > testList;

bool testsStatus;
int totalTestsRun;
int totalTestsRunSuccessfully;
};

#endif // FRAMEWORK_HPP_INCLUDED
