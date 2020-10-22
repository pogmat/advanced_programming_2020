#include <iostream>
#include <cmath>

int main()
{
    uint64_t n_max;

    std::cout << "n_max= ";
    std::cin >> n_max;

    bool* sieve{new bool[n_max / 2 - 1]};
    for (uint64_t i{0}; i < n_max / 2; ++i)
        sieve[i] = true;

    const u_int64_t n_sqrt{static_cast<uint64_t>(std::ceil(std::sqrt(n_max)))};
    for (uint64_t i{3}; i < n_sqrt; i += 2) {
        if (sieve[(i - 3) / 2]) {
            for (uint64_t j{i * i}; j <= n_max; j += 2 * i)
                sieve[(j - 3) / 2] = false;
        }
    }

    std::cout << 2 << std::endl;
    for (uint64_t i{0}; i < n_max / 2 - 1; ++i)
        if (sieve[i])
            std::cout << 2 * i + 3 << std::endl;

    return 0;
}