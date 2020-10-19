#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string>


void usage(const char* const name)
{
    std::cerr << "USAGE" 
              << std::endl
              << *name << 
              "[-l <line number=80>] <filename>" 
              << std::endl;
              
              exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{
    // Parsing options
    const std::string space_c = "\t\v\f\r ";
    int opt;
    long line_width{80}, line_curr{0};
    size_t breaking_point;
    char* endptr{NULL};
    std::string filename, line;
    std::ifstream file;
    
    errno = 0;
    while ((opt = getopt(argc, argv, ":l:")) != -1) {
        switch (opt) {
            case 'l':
                line_width = std::strtol(optarg, &endptr, 10);
                if (errno !=0 || line_width <= 0 || *endptr || endptr == optarg)
                   usage(argv[0]);
                break;
            case ':':
                usage(argv[0]);
        }
    }
    if (argc - optind != 1)
        usage(argv[0]);
    filename = argv[optind];
    
    // Open file
    file.open(filename);
    if (file.fail())
        std::cout << "No such file: " << filename << "." << std::endl;
    
    // Reading file
    while (std::getline(file, line)) {
        ++line_curr;
        while (line.length() > static_cast<size_t>(line_width)) {
            breaking_point = line.find_last_of(space_c, line_width);
            if (breaking_point == std::string::npos) {
                std::cerr << ":::: Too long word at line "
                          << line_curr 
                          << "." 
                          << std::endl;
                breaking_point = line.find_first_of(space_c);               
            }
            std::cout << line.substr(0, breaking_point) << std::endl;
            line.erase(0, line.find_first_not_of(space_c, breaking_point));
        }
        if (line.erase(0, line.find_first_not_of(space_c)) != "")
            std::cout << line << std::endl;
    }
    // Notice that we do not have to worry too much about nested
    // while and if since the bottleneck probabily is the memory


    return 0;
}
