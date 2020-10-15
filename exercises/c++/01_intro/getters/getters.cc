#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>

template <typename T>
T read_until(const std::string& msg) noexcept
{
        T read;
        std::string buf_tail;
        const std::string null_c = "\t\n\v\f\r ";
        
        std::cin.clear();
        for (;;) {
            std::cout << msg;
            std::cin >> read;
            if (std::cin.fail()) {
                // If failure 
                std::cin.clear();
                // Reset failbit
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // Ignore the rest of the string
                continue;
            }
            if(!std::getline(std::cin, buf_tail))
                continue;
            if(buf_tail.erase(buf_tail.find_last_not_of(null_c) + 1)
                    .erase(0, buf_tail.find_first_not_of(null_c)) == "")
                // If the trim of the tail buffer is empty the read is correct
                break;
        }
        
        return read;
}


int main()
{
    const std::string msg_int = isatty(fileno(stdin)) ? "Insert an integer: " : "";
    const std::string msg_dbl = isatty(fileno(stdin)) ? "Insert a dobule: " : "";
    // If it is piping do not cout insert message
    int i = read_until<int>(msg_int);
    double d = read_until<double>(msg_dbl);
    
    std::cout << "i= " << i << std::endl;
    std::cout << "d= " << d << std::endl; 

    return 0;
}
