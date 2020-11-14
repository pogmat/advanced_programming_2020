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

#define PRINT(x) std::cout << #x " = " << x << std::endl;

void init_screen(int& rows, int& cols)
{
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    rows = size.ws_row;
    cols = size.ws_col;

    std::cout << "\033[2J\033[1;1H";
}

void print_frame(const std::vector<uint_fast8_t>& s,
                 const int rows,
                 const int cols)
{
    const uint_fast8_t status_mask{0x01};

    for (int i{0}; i < rows - 1; ++i) {
        for (int j{0}; j < cols; ++j)
            std::cout << ((s[i * cols + j] & status_mask) ? "*" : " ");
        std::cout << '\n';
    }

    for (int j{0}; j < cols; ++j)
        std::cout << ((s[(rows - 1) * cols + j] & status_mask) ? "*" : " ");

    std::cout.flush();
}

void set_cell(std::vector<uint_fast8_t>& s,
              const int i,
              const int j,
              const bool val,
              const int rows,
              const int cols)
{
    const int position{(i % rows) * cols + (j % cols)};
    uint_fast8_t& status_bit{s[position]};
    const uint_fast8_t status_mask{0x01};
    const uint_fast8_t neigh_plus_one{0x10};
    const uint_fast8_t neigh_minus_one{0xf0};

    if ((status_bit & status_mask) == static_cast<uint_fast8_t>(val))
        return;
    // There is nothing go do

    status_bit ^= status_mask;
    // Otherwise toggle status bit
 
    uint_fast8_t delta = val ? neigh_plus_one : neigh_minus_one;
    const int NW{((i + rows - 1) % rows) * cols + ((j + cols - 1) % cols)};
    const int N {((i + rows - 1) % rows) * cols + ((j           ) % cols)};
    const int NE{((i + rows - 1) % rows) * cols + ((j + 1       ) % cols)};
    const int W {((i           ) % rows) * cols + ((j + cols - 1) % cols)};
    const int E {((i           ) % rows) * cols + ((j + 1       ) % cols)};
    const int SW{((i + 1       ) % rows) * cols + ((j + cols - 1) % cols)};
    const int S {((i + 1       ) % rows) * cols + ((j           ) % cols)};
    const int SE{((i + 1       ) % rows) * cols + ((j + 1       ) % cols)};

    s[NW] += delta;
    s[N ] += delta;
    s[NE] += delta;
    s[W ] += delta;
    s[E ] += delta;
    s[SW] += delta;
    s[S ] += delta;
    s[SE] += delta;

    return;
}

void print_info(std::vector<uint8_t>& status,
                const int rows,
                const int cols)
{
    int tot{0};

    for (int i{0}; i < rows; ++i)
        for (int j{0}; j < cols; ++j) {
            uint_fast8_t s = (status[i * cols + j] & 0xFF) >> 4;
            if (s & 0xFF) {
                std::cout << "(" << i << ", " << j << ") => " << static_cast<unsigned int>(s) << std::endl;
                tot += static_cast<unsigned int>(s);
            }
        }

    std::cout << "TOTAL : " << tot <<std::endl;
}

void update_frame(std::vector<uint_fast8_t>& s,
                  const int rows,
                  const int cols)
{
    const std::vector<uint_fast8_t> prev_s{s};

    for (int i{0}; i < rows; ++i) {
        for (int j{0}; j < cols; ++j) {
            const int position{i * cols + j};
            const uint_fast8_t death_3{0x30};
            const uint_fast8_t live_2{0x21};
            const uint_fast8_t live_3{0x31};

            switch (prev_s[position]) {
            case death_3:
                set_cell(s, i, j, true, rows, cols);
                break;
            case live_2:
            case live_3:
                break;
            default:
                set_cell(s, i, j, false, rows, cols);
                break;
            }
        }
    }
}

int main()
{
    int rows, cols;

    init_screen(rows, cols);

    std::cout << rows << ", " << cols << std::endl;

    std::vector<uint_fast8_t> status(rows * cols, 0x0);

    set_cell(status, 5, 5, true, rows, cols);
    set_cell(status, 6, 5, true, rows, cols);
    set_cell(status, 7, 5, true, rows, cols);

    set_cell(status, 4, 12, true, rows, cols);
    set_cell(status, 5, 12, true, rows, cols);
    set_cell(status, 4, 13, true, rows, cols);
    set_cell(status, 5, 13, true, rows, cols);

    set_cell(status, 1, 20, true, rows, cols);
    set_cell(status, 2, 21, true, rows, cols);
    set_cell(status, 3, 19, true, rows, cols);
    set_cell(status, 3, 20, true, rows, cols);
    set_cell(status, 3, 21, true, rows, cols);

    set_cell(status,  7, 42, true, rows, cols);
    set_cell(status,  7, 43, true, rows, cols);
    set_cell(status,  7, 44, true, rows, cols);
    set_cell(status,  9, 40, true, rows, cols);
    set_cell(status, 10, 40, true, rows, cols);
    set_cell(status, 11, 40, true, rows, cols);



    print_frame(status, rows, cols);
    for (;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        update_frame(status, rows, cols);
        print_frame(status, rows, cols);
    }

    return 0;
}
