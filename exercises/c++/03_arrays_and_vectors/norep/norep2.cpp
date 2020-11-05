#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#if defined _VCT_ && !defined _MAP_  && !defined _U_MAP_
#include <vector>
#include <algorithm>
#elif !defined _VCT_ && defined _MAP_ && !defined _U_MAP_
#include <map>
#elif !defined _VCT_ && !defined _MAP_ && defined _U_MAP_
#include <unordered_map>
#else
#error You must define one and only one among _VCT_, _MAP_, _U_MAP_
#endif

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

    std::ifstream file{filename, std::fstream::in};
    if (!file.is_open()) {
        std::cerr << filename
                  << ": file not found"
                  << std::endl;

        exit(EXIT_FAILURE);
    }

    auto t0 = std::chrono::high_resolution_clock::now();

    std::string word;
    #if defined(_VCT_)
    std::vector<std::string> words{};
    std::vector<int> counts{};
    #elif defined(_MAP_)
    std::map<std::string, int> words{};
    #elif defined(_U_MAP_)
    std::unordered_map<std::string, int> words{};
    #endif
    while (file >> word) {
        #if defined(_VCT_)
        auto position = std::find(words.begin(), words.end(), word);
        if (position == words.end()) {
            words.push_back(word);
            counts.push_back(1);
        } else {
            auto index = std::distance(words.begin(), position);
            ++counts[index];
        }
        #elif defined(_MAP_) || defined(_U_MAP_)
        auto position = words.find(word);
        if (position == words.end())
            words.insert({word, 1});
        else
            ++(position->second);
        #endif
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
    std::clog << "ELAPSED : " << elapsed.count() << " ms" << std::endl;
    
    std::cout << "\nSUMMARY" << std::endl;

    #if defined(_VCT_)
    auto size_v = words.size();
    for (decltype(size_v) i{0}; i < size_v; ++i)
        std::cout << words[i] << ": " << counts[i] << std::endl;

    #elif defined(_MAP_) || defined(_U_MAP_)
    for (auto el: words)
        std::cout << el.first << ": " << el.second << std::endl;
    #endif

    file.close();

    return 0;
}