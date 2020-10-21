#include <iostream>
#include <cmath>


constexpr uint64_t n_max = 100;


bool is_prime(const uint64_t n)
{
    const uint64_t p_max{n};
    for (uint64_t p{3}; p < p_max; ++p) {
        if (!(n % p))
            return false;
    }
    return true;
}


int main()
{
    uint64_t* primes{new uint64_t[n_max]};
    // No reason to resize every time the array:
    // if the number ars small this is better.
    // However I allocated in the heap, just in case...
    // If N_max grows dramatically there are some upper
    // bound on the number of prime above N_max.
    uint64_t i{1};

    primes[0] = 2;
    for (uint64_t n{3}; n <= n_max; n += 2) {
        if (is_prime(n)) {
            primes[i++] = n;
        }
    }


    for (uint64_t j{0}; j < i; ++j)
        std::cout << "p_" << j + 1 << "= " << primes[j] << std::endl;

    delete[] primes;

    return 0;
}