#include <iostream>

int main () {
    int maxN {20};
    for (int i {0}; i <= maxN; ++i) {
        if (i % 2 == 0) {
            std::cout << i << " ";
        }
    }
    return 0;
}