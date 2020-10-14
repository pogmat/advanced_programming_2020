#include <iostream>
#include <string>

namespace std {
  const char tab = '\t';  
};

void print_count(const int c, const std::string& s)
{
    std::cout << std::tab << c << ": " << s << std::endl;
}

int main()
{

    std::string curr, prev;
    uint64_t i{1};

    if(!std::getline(std::cin, curr))
        return 0;
    prev = curr;
    while(std::getline(std::cin, curr)) {
        if(curr == prev)
            ++i;
        else {
            print_count(i, prev);
            i = 1;
        }
        prev = curr;
    }
    print_count(i, prev);

    return 0;
}
