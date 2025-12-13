#include <vector>

int main()
{   
    std::vector<int> squares {1, 4, 9, 16, 25};
    // This invokes list constructor to define a 1 element vector containing 5
    std::vector<int> v1 {5};
    // This invokes a non-list constructor that define a 5 element vector with value-initialized elements
    std::vector<int> v1 (5);
    return 0;
}