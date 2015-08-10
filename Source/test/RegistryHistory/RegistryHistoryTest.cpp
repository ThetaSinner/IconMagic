/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#include "./../framework.hpp"
#include "./../../main//RegistryHistory.hpp"

bool setAndRetrieveImageEntry();
bool setAndRetrieveFormattedImageEntry();

bool testRegistryHistory(int &total_tests_run, int &total_tests_run_successfully)
{
  total_tests_run = 0;
  total_tests_run_successfully = 0;

  /**< Use the test framework to run all tests. */
  TestFramework testFramework;
  testFramework.addTest(setAndRetrieveImageEntry);
  testFramework.execute();

  /**< Set the test statisics so they can be used by the calling process. */
  total_tests_run = testFramework.getTotalTestsRun();
  total_tests_run_successfully = testFramework.getTotalTestsRunSuccessfully();
  return testFramework.getTestsStatus();
}

bool setAndRetrieveImageEntry()
{
  ImageEntry imageEntry;
  imageEntry.createFromRawData("dummy", "values");

  if(imageEntry.getImagePath() != "dummy")
  {
    return false;
  }

  if(imageEntry.getImageIndex() != "values")
  {
    return false;
  }

  return true;
}
