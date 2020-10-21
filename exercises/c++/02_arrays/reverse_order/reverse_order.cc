#include <iostream>

template<typename T>
T* initialize_array(long n) {
    T* arr{new T[n]};

    for (long i{0}; i < n; ++i)
        std::cin >> arr[i];

    return arr;
}

template<typename T>
void print_reverse_array(long n, T* arr)
{
    for (long i{n - 1}; i >= 0; --i)
        std::cout << "arr[" << i << "]= " << arr[i] << std::endl;
}

int main()
{
    long size;
    int* ai;
    double* af;

    std::cout << "Insert the size of the array ";
    std::cin >> size;
    if (std::cin.fail() || size < 0) {
        std::cerr << "You must write a positive number." << std::endl;
        return -1;
    }

    ai = initialize_array<int>(size);
    print_reverse_array(size, ai);

    af = initialize_array<double>(size);
    print_reverse_array(size, af);

    delete[] ai;
    delete[] af;

    return 0;
}