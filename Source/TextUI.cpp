#include "TextUI.hpp"


/*
* Internal global variable definitions.
*/
unsigned int CONSOLE_CHARACTER_OUTPUT_WIDTH = 80;
unsigned int CONSOLE_CHARACTER_OUTPUT_HEIGHT = 25;
unsigned int INPUT_BUFFER_MAX_CHARACTERS = 100;
std::string PRINT_FILLER_CHARACTER = "*";



/*
* Getters and setter for internal global variables.
*/
void setConsoleCharacterOutputWidth(unsigned width) { CONSOLE_CHARACTER_OUTPUT_WIDTH = width; }
void setConsoleCharacterOutputHeight(unsigned height) { CONSOLE_CHARACTER_OUTPUT_HEIGHT = height; }
void setPrintFillerCharacter(char character) { PRINT_FILLER_CHARACTER = std::string(1, character); }
void setInputBufferMaxCharacters(unsigned maximum) { INPUT_BUFFER_MAX_CHARACTERS = maximum; }

/*
* Internal prototypes.
*/
std::string repeatString(std::string str, int times = 1);
std::string centerStringForConsole(std::string str, std::string filler = "*");


/*
* Interface definitions.
*/
void printTitleBox(std::string title)
{
    std::cout
        << repeatString(PRINT_FILLER_CHARACTER, CONSOLE_CHARACTER_OUTPUT_WIDTH)
        << centerStringForConsole(" " + title + " ", PRINT_FILLER_CHARACTER)
        << repeatString(PRINT_FILLER_CHARACTER, CONSOLE_CHARACTER_OUTPUT_WIDTH);
}

void printTitleLine(std::string title)
{
    std::cout
        << centerStringForConsole(" " + title + " ", PRINT_FILLER_CHARACTER);
}

void printLine(std::string line)
{
    std::cout
        << line;
}

std::string getInputLine(std::string prompt)
{
    std::cout << prompt << " ";

    char buffer[INPUT_BUFFER_MAX_CHARACTERS];
    std::cin.getline(buffer, INPUT_BUFFER_MAX_CHARACTERS);

    return std::string(buffer);
}

std::string getInputYesNo(std::string prompt, bool forceAnswer)
{
    std::string yn = getInputLine(prompt + " (y/n) ");

    if (!forceAnswer)
    {
        return yn;
    }
    else
    {
        if (yn == "y" || yn == "n") return yn;
        else return getInputYesNo("Please input a 'y' or an 'n' to answer.\n" + prompt);
    }
}

void printNewLine(int times)
{
    std::cout
        << repeatString("\n", times);
}

void clearConsole()
{
    printNewLine(CONSOLE_CHARACTER_OUTPUT_HEIGHT);
}

/*
* Internal definitions.
*/
std::string repeatString(std::string str, int times)
{
    std::string repeated = "";

    while (times > 0) {
        repeated += str;
        times--;
    }

    return repeated;
}

std::string centerStringForConsole(std::string str, std::string filler)
{
    int starCountL = (CONSOLE_CHARACTER_OUTPUT_WIDTH - str.length()) / 2;
    int starCountR = (CONSOLE_CHARACTER_OUTPUT_WIDTH - str.length() - starCountL);

    return (repeatString(filler, starCountL) + str + repeatString(filler, starCountR));
}
