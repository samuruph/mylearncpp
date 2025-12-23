#include <iostream>

// str is a pointer to the first element of the array
// this is because arrays decay to pointers when passed to functions
// you could also write void printString(const char *str), it would be the same
void printString(const char str[]) {

    // iterate until the null character is reached
    while (*str != '\0')
    {
        // print current character
        std::cout << *str;

        // move to the next character
        ++str;
    }

    // print a newline
    std::cout << '\n';
    return;
}

int main()
{
    const char str[] {"Hello, world!"};
    printString(str);
    return 0;
}