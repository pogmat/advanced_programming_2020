#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

void usage(const char* argv0)
{
    std::cerr << "USAGE:\n" 
              << argv0 
              << " <filename>" 
              << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    if (argc != 2)
        usage(argv[0]);

    std::string filename{argv[1]};

    std::ifstream file{filename, std::ifstream::in};
    if (!file.is_open()) {
        std::cerr << filename << ": file not found." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<double> v;
    double record, sum{0};

    while (file >> record) {
        v.push_back(record);
        sum += record;
    }

    file.close();

    std::size_t size_v{v.size()};
    double mean = sum / size_v;

    std::sort(v.begin(), v.end());
    double median = (size_v % 2) ? (v[size_v / 2 -1] + v[size_v / 2]) / 2 : v[size_v / 2];

    std::cout << "Read " << size_v << " values\n"
              << "Mean  : " << mean << "\n"
              << "Median: " << median << std::endl;
}