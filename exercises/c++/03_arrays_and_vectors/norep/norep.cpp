#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::string line;
    std::unordered_map<std::string, int> dictionary{};

    while (std::getline(std::cin, line)) {
        auto position = dictionary.find(line);
        
        if (position == dictionary.end())
            dictionary.insert({line, 1});
        else
            ++(position->second);

    }

    std::cout << "\nSUMMARY" << std::endl;

    for (auto el: dictionary) {
        std::cout << el.first << " :" << el.second << std::endl;
    }

    return 0;
}