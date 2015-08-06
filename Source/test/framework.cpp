/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#include "framework.hpp"

// TODO remove testing includes
#include <iostream>

/** @brief addTest
  *
  * @todo: document this function
  */
void TestFramework::addTest(std::function<bool(void)> testFunction)
{
  testList.push_back(testFunction);
}

/** @brief execute
  *
  * @todo: document this function
  */
bool TestFramework::execute()
{
  this -> totalTestsRun = 0;
  this -> totalTestsRunSuccessfully = 0;

  for(auto &i : testList)
  {
    if(i())
    {
      totalTestsRunSuccessfully++;
    }

    totalTestsRun++;
  }

  if(totalTestsRun == totalTestsRunSuccessfully)
  {
    testsStatus = true;
  }
  else
  {
    testsStatus = false;
  }

  return testsStatus;
}

/** @brief getTestStatus
  *
  * @todo: document this function
  */
bool TestFramework::getTestsStatus()
{
  return this -> testsStatus;
}

/** @brief getTotalTestsRun
  *
  * @todo: document this function
  */
int TestFramework::getTotalTestsRun()
{
  return this -> totalTestsRun;
}

/** @brief getTotalTestsRunSuccessfully
  *
  * @todo: document this function
  */
int TestFramework::getTotalTestsRunSuccessfully()
{
  return this -> totalTestsRunSuccessfully;
}

/** @brief TestFramework
  *
  * @todo: document this function
  */
TestFramework::TestFramework()
{
  this -> testsStatus = false;
  this -> totalTestsRun = 0;
  this -> totalTestsRunSuccessfully = 0;
}

/** @brief ~TestFramework
  *
  * @todo: document this function
  */
TestFramework::~TestFramework()
{
}
