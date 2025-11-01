#include <iostream>

int main () {
    int smaller {};
    int larger  {};

    std::cout << "Enter an integer: ";
    std::cin >> smaller;
    std::cout << "Enter a larger integer: ";
    std::cin >> larger;

    if (smaller > larger) {
      int tmp {smaller};
      smaller = larger;
      larger = tmp;
    } // tmp goes out of scope here

    // optional: swap using std::swap from <utility>
    // #include <utility>
    // std::swap(smaller, larger);

    std::cout << "The smaller value is: " << smaller << '\n';
    std::cout << "The larger value is: " << larger << '\n';
} // smaller and larger go out of scope here
