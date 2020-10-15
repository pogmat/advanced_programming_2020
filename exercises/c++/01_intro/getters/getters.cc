#include <iostream>
#include <string>
#include <sstream>
#include <limits>


template <typename T>
T read_until(const std::string& msg) noexcept
{
        T read;
        std::string buffer;
        std::istringstream sstream;
        // Use the class instringstream which is a subclass of istream
        
        do {
            sstream.clear();
            // At each cycle reset the failbit
            // Note that not .ignore() has to be called:
            //     every time we reset the sstream
            std::cout << msg; 
            std::cin >> buffer;
            sstream.str(buffer);
            // Set the sstream to the (string) buffer just read
            sstream >> read;
            // Try to input to read the value
        } while (sstream.fail() || !sstream.eof());
        // until two condition are satisfied:
        // 1. no failure happen
        // 2. the stream arrived at the end of the file
        //    (otherwhise "34r" is accepted)
        
        return read;
}


template <typename T>
T read_until_bis(const std::string& msg) noexcept
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
            std::getline(std::cin, buf_tail);
            if(buf_tail.erase(buf_tail.find_last_not_of(null_c) + 1)
                    .erase(0, buf_tail.find_first_not_of(null_c)) == "")
                // If the trim of the tail buffer is empty the read is correct
                break;
        }
        
        return read;
}


int main()
{
    int i = read_until<int>("Insert and integer: ");
    double d = read_until<double>("Insert a dobule: ");
    
    std::cout << "i= " << i << std::endl;
    std::cout << "d= " << d << std::endl;
    
    i = read_until_bis<int>("Insert and integer: ");
    d = read_until_bis<double>("Insert a dobule: ");
    
    std::cout << "i= " << i << std::endl;
    std::cout << "d= " << d << std::endl;  

    return 0;
}
