/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */


#include "Testing.hpp"

#include "TextUI.hpp"

void testTextUI()
{
  setConsoleCharacterOutputWidth(80);
  setPrintFillerCharacter('-');
  printTitleBox("TestTitleBox");
  std::cout << "\n";
  printTitleLine("TestTitleLine");
  std::cout << "\n";
  printLine("TestLine\n");
  std::cout << "\n";
  std::string in = getInputLine("What's your favourite food?");
  std::cout << "Awesome! I eat " << in << " too!\n\n";
  std::string yn = getInputYesNo("Are you hungry?");

  if(yn == "y")
  {
    std::cout << "You answered yes, please don't eat me.\n";
  }
  else if(yn == "n")
  {
    std::cout << "You answered no, okay then...\n";
  }
  else
  {
    std::cout << "You didn't answer yes or no, I should have set forceAnswer=true\n";
  }

  std::cout << "\n";
  std::string ynf = getInputYesNo("Are you angry?", true);

  if(ynf == "y")
  {
    std::cout << "You answered yes, please don't hurt me.\n";
  }
  else
  {
    std::cout << "You answered no, I don't trust you.\n";
  }

  std::cout << "\n\nTesting TextUI complete.\n";
}
