#include <iostream>
#include <cmath>

int main()
{
    uint64_t n_max;

    std::cout << "n_max= ";
    std::cin >> n_max;

    bool* sieve{new bool[n_max - 1]};
    for (uint64_t i{0}; i < n_max; ++i)
        sieve[i] = true;

    const u_int64_t n_sqrt{static_cast<uint64_t>(std::ceil(std::sqrt(n_max)))};
    for (uint64_t i{2}; i < n_sqrt; ++i) {
        if (sieve[i - 2]) {
            for (uint64_t j{i * i}; j <= n_max; j += i)
                sieve[j - 2] = false;
        }
    }

    for (uint64_t i{0}; i < n_max - 1; ++i)
        if (sieve[i])
            std::cout << i + 2 << std::endl;

    return 0;
}