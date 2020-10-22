#include <iostream>
#include <vector>

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
    std::vector<uint64_t> primes{0};

    for (uint64_t n{3}; n <= n_max; n += 2) {
        if (is_prime(n))
            primes.push_back(n);
    }

    for (auto p: primes) {
        std::cout << p << std::endl;
    }

    return 0;
}