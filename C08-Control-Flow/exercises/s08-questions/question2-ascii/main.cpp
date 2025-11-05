#include <iostream>

int main()
{
  char character {'a'};

  while(character <= 'z') // using <= on characters is valid (compares ASCII values)
  {
    std::cout << "The ASCII value of '" << character << "' is " << static_cast<int>(character) << std::endl;
    ++character;
  }

  return 0;
}