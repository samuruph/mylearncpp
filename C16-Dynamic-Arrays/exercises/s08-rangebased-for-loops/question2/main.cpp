#include <iostream>
#include <string>
#include <string_view>
#include <vector>

template <typename T>
bool isValueInArray(const std::vector<T>& arr, const T& value )
{
    // we'll use a reference since we don't know if T is expensive to copy
    for (const auto& a : arr)
    {
        if (a == value)
            return true;
    }

    return false;
}

int main()
{
    std::vector<std::string_view> names{ "Alex", "Betty", "Caroline", "Dave",
        "Emily", "Fred", "Greg", "Holly" };

    std::cout << "Enter a name: ";
    std::string username{};
    std::cin >> username;

    // By explicitly specifying std::string_view as a function template argument,
    // the compiler will implicitly convert username to `std::string_view` to match the parameter type.
    bool found{ isValueInArray<std::string_view>(names, username) };

    // The following is also okay.  If we rely on template argument deduction instead, the compiler
    // won't do implicit conversions, so we need to make sure `username` has the expected type.
    // bool found{ isValueInArray(names, static_cast<std::string_view>(username)) };

    if (found)
        std::cout << username << " was found.\n";
    else
        std::cout << username << " was not found.\n";

    return 0;
}