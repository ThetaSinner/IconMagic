#ifndef TEXTUI_HPP_INCLUDED
#define TEXTUI_HPP_INCLUDED

#include <iostream>
#include <string>

void setConsoleCharacterOutputWidth(unsigned width);
void setConsoleCharacterOutputHeight(unsigned height);
void setPrintFillerCharacter(char character);
void setInputBufferMaxCharacters(unsigned maximum);

void printTitleBox(std::string title);
void printTitleLine(std::string title);

void printLine(std::string line);

std::string getInputLine(std::string prompt);
std::string getInputYesNo(std::string prompt, bool forceAnswer = false);

void printNewLine(int times = 1);
void clearConsole();

#endif // TEXTUI_HPP_INCLUDED
