#include <iostream>
#include <iomanip>
#include <array>
#include <utility>
#include <random>

constexpr std::size_t ROWS{3}, COLUMNS{5};


template <typename T>
void print_matrix(const T& m, std::size_t rows, std::size_t cols) {
    if (m.size() != rows * cols) {
        std::cerr << "The given array is not a matrix" << std::endl;
        exit(EXIT_FAILURE);
    }


    for (std::size_t i{0}; i < rows; ++i) {
        for (std::size_t j{0}; j < cols; ++j)
            std::cout << std::left << std::setw(15) << std::fixed << std::setprecision(5) << m[i * cols + j];
        std::cout << '\n';
    }
    std::cout << std::flush;
}

template <typename T>
void initialize_matrix(T& m)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution{0.0, 1.0};
    
    for (auto& el: m)
        el = distribution(generator);
}

template <typename T>
void transpose_matrix(T& m, std::size_t rows, std::size_t cols)
{
    T mT;
    std::size_t pos{0};
    
    // for (std::size_t i{0}; i < cols; ++i)
    //     for (std::size_t j{0}; j < rows; ++j)
    //         mT[i * rows + j] = m[j * cols + i];

    for (auto& el: mT) {
        el = m[(pos % rows) * cols + pos / rows];
        ++pos;
    }

    std::swap(m, mT);
}

int main()
{
    std::array<double, ROWS * COLUMNS> matrix;

    initialize_matrix(matrix);
    print_matrix(matrix, ROWS, COLUMNS);
    std::cout << std::endl;

    transpose_matrix(matrix, ROWS, COLUMNS);
    print_matrix(matrix, COLUMNS, ROWS);

    return  0;
}