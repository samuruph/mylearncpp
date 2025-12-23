#include <iostream>

// str is a pointer to the first element of the array
// this is because arrays decay to pointers when passed to functions
// you could also write void printString(const char *str), it would be the same
void printString(const char str[]) {

    // define a pointer that helps us getting to the end of the array
    // starts at the first element of the array
    const char* ptr { str };

    // iterate until the null character is reached (end of the array)
    while (*ptr != '\0')
    {
        ++ptr;
    }

    // iterate backward until ptr is equal to str (first element)
    do {
        std::cout << *ptr;
    } while (ptr-- != str);

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