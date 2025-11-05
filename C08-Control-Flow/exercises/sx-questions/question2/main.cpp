// Make sure that assert triggers even if we compile in release mode
#undef NDEBUG

#include <cassert> // for assert
#include <iostream>

bool isPrime(int x)
{   
    if (x < 2) { // 0 and 1 are not prime numbers
        return false;
    }
    if (x == 2) { // 2 is the only even prime number
        return true;
    }
    if (x % 2 == 0) { // eliminate even numbers greater than 2
        return false;
    }

    for (int i {2}; i * i < x; i += 2) { // check divisors from 2 to sqrt(x), and skip even numbers
        if (x % i == 0) { // found a divisor
            return false; // x is not prime
        }
    }
    return true; // no divisors found, x is prime
}

int main()
{
    assert(!isPrime(0)); // terminate program if isPrime(0) is true
    assert(!isPrime(1));
    assert(isPrime(2));  // terminate program if isPrime(2) is false
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";

    return 0;
}