#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <utility>
#include <random>


using vct = std::vector<double>;

void print_matrix(const vct& m, std::size_t rows, std::size_t cols) {
    if (m.size() != rows * cols) {
        std::cerr << "The given array is not a matrix " << std::endl;
        exit(EXIT_FAILURE);
    }


    for (std::size_t i{0}; i < rows; ++i) {
        for (std::size_t j{0}; j < cols; ++j)
            std::cout << std::left << std::setw(15) << std::fixed << std::setprecision(5) << m[i * cols + j];
        std::cout << '\n';
    }
    std::cout << std::flush;
}

void initialize_matrix(vct& m, const std::size_t rows, const std::size_t cols)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution{0.0, 1.0};
    
    const std::size_t size{rows * cols};
    for (std::size_t i{0}; i < size; ++i)
        m.push_back(distribution(generator));
}

void transpose_matrix(vct& m, std::size_t rows, std::size_t cols)
{
    vct mT;
    std::size_t pos{0};
    const std::size_t size{rows * cols};

    for (std::size_t i{0}; i < size; ++i) {
        mT.push_back(m[(pos % rows) * cols + pos / rows]);
        ++pos;
    }

    std::swap(m, mT);
}

void usage(const char* argv0)
{
        std::cerr << "USAGE:\n" << argv0 << " <rows> <columns>" << std::endl;
        exit(EXIT_FAILURE);    
}

int main(int argc, char** argv)
{   
    std::size_t ROWS, COLUMNS;

    if (argc != 3) 
        usage(argv[0]);

    {
        std::istringstream row_stream{argv[1]};
        std::istringstream col_stream{argv[2]};

        row_stream >> ROWS;
        if (row_stream.fail())
            usage(argv[0]);

        col_stream >> COLUMNS;
        if (col_stream.fail())
            usage(argv[0]);
    }

    std::vector<double> matrix;

    initialize_matrix(matrix, ROWS, COLUMNS);
    print_matrix(matrix, ROWS, COLUMNS);
    std::cout << std::endl;

    transpose_matrix(matrix, ROWS, COLUMNS);
    print_matrix(matrix, COLUMNS, ROWS);

    return  0;
}