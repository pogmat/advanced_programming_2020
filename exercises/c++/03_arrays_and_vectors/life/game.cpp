#ifndef __linux__
#error I refuse to compile
#endif

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include <sys/ioctl.h> 
#include <unistd.h>

void print_frame(const std::vector<bool>& s, const int r, const int c)
{
    for (int i{0}; i < r - 1; ++i) {
        for (int j{0}; j < c; ++j) 
            std::cout << ((s[i * c + j]) ? "*" : " ");
        std::cout << '\n';
    }

    for (int j{0}; j < c; ++j)
        std::cout << ((s[(r - 1) * c + j]) ? "*" : " ");

    std::cout.flush();
}

// This has to be used to set the cell manually
int init_cell(std::vector<bool>& s,
              std::vector<int8_t>& n,
              const int i,
              const int j,
              const bool status,
              const int rows,
              const int cols)
{
    if ( i < 0 || i >= rows || j < 0 || j >= cols) {
        std::cout << "PRECRAP!" << std::endl;
        return -1;
    }

    // std::vector<bool> is strange it cannot be set equal to reference.
    if (s[i * cols + j] == status)
        return 0;
    else
        s[i * cols + j] = status;
    
    int8_t delta = status ? 1 : -1;

    // This is the less intelligent way to implement it
    if (i != 0 && j != 0){
        n[(i - 1) * cols + (j - 1)] += delta;
        //std::cout << "NW\n";
        }
    if (i != 0){
        n[(i - 1) * cols + j] += delta;
        //std::cout << "N\n";
        }
    if (i != 0 && j != cols - 1){
        n[(i - 1) * cols + (j + 1)] += delta;
        //std::cout << "NE\n";
        }
    if (j != cols - 1){
        n[i * cols + (j + 1)] += delta;
        //std::cout << "E\n";
        }
    if (i != rows - 1 && j != cols - 1){
        n[(i + 1) * cols + (j + 1)] += delta;
        //std::cout << "SE\n";
        }
    if (i != rows - 1){
        n[(i + 1) * cols + j] += delta;
        //std::cout << "S\n";
        }
    if (i != rows - 1 && j != 0){
        n[(i + 1) * cols + (j - 1)] += delta;
        //std::cout << "SW\n";
        }
    if (j != 0){
        n[i * cols + (j - 1)] += delta;
        //std::cout << "W\n";
        }

    return 0;
}

// This is to be used to set the cell in the update loop
template <bool state, bool N=false, bool W=false, bool S=false, bool E=false>
void set_cell(std::vector<bool>& s,
              std::vector<int8_t>& n,
              const int i,
              const int j,
              const int cols)
{
    s[i * cols + j] = state;
    int8_t delta;

    if constexpr(state)
        delta = 1;
    else
        delta = -1;

    if constexpr(!N && !W)
        n[(i - 1) * cols + (j - 1)] += delta;
    if constexpr(!N)
        n[(i - 1) * cols + j] += delta;
    if constexpr(!N && !E)
        n[(i - 1) * cols + (j + 1)] += delta;
    if constexpr(!E)
        n[i * cols + (j + 1)] += delta;
    if constexpr(!S && !E)
        n[(i + 1) * cols + (j + 1)] += delta;
    if constexpr(!S)
        n[(i + 1) * cols + j] += delta;
    if constexpr(!S && !W)
        n[(i + 1) * cols + (j - 1)] += delta;
    if constexpr(!W)
        n[i * cols + (j - 1)] += delta;

}

int main()
{

    int rows, cols;
    {
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

        rows = size.ws_row;
        cols = size.ws_col;
    }

    std::vector<bool> status(rows * cols, false);
    std::vector<int8_t> neig(rows * cols, 0);


    //std::cout << "\033[2J\033[1;1H";


    // set_cell<true, true, true, false, false>(status, neig,        0,        0, cols);
    // set_cell<true, true, false, false, true>(status, neig,        0, cols - 1, cols);
    // set_cell<true, false, true, true, false>(status, neig, rows - 1,        0, cols);
    // set_cell<true, false, false, true, true>(status, neig, rows - 1, cols - 1, cols);

    init_cell(status, neig,        0,        0, true, rows, cols);
    init_cell(status, neig,        0, cols - 1, true, rows, cols);
    init_cell(status, neig, rows - 1,        0, true, rows, cols);
    init_cell(status, neig, rows - 1, cols - 1, true, rows, cols);

    print_frame(status, rows, cols);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << rows << ", " << cols << std::endl;

    for (int i{0}; i < rows; ++i)
        for (int j{0}; j < cols; ++j)
            if (int8_t val = neig[i * cols + j])
                std::cout << "(" << i << ", " << j << ") => " << static_cast<int>(val) << std::endl;

    return 0;
}