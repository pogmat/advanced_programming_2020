#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>

namespace to_metric {
    const std::unordered_map<std::string, double> conversion{
        {"thou", 0.0000254},
        {"inch", 0.0254},
        {"foot", 0.3048},
        {"yard", 0.9144},
        {"chain", 20.1168},
        {"furlong", 201.168},
        {"mile", 1609.344},
        {"league", 4828.032},
        {"km", 1000.0},
        {"m", 1.0},
        {"cm", 0.01},
        {"mm", 0.001},
        {"um", 1e-6},
        {"nm", 1e-9},
        {"angstrom", 1e-10},
        {"fm", 1e-15},
        {"fermi", 1e-15},
        {"ly", 0.461e15},
        {"light year", 9.461e15},
        {"pc", 3.086e16},
        {"parsec", 3.086e16},
        {"Mpc", 3.086e22},
        {"Mparsec", 3.086e22},
        {"Gpc", 3.086e25},
        {"Gparsec", 3.086e25}
    };
}

namespace std {
    std::string& trim(std::string s)
    {
        const std::string null_c = "\t\n\v\f\r ";
        
        return s.erase(s.find_last_not_of(null_c) + 1)
                .erase(0, s.find_first_not_of(null_c));
    }
}
                                                             
int main()
{
    double value;
    std::string unit;
    
    std::cout << "Insert a length with its units." << std::endl;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "No value given." << std::endl;
        return -1;
    }
    if(!std::getline(std::cin, unit)) {
        std::cerr << "IO error" << std::endl;
        return -1;
    }
    try {
        value *= to_metric::conversion.at(std::trim(unit));
    } catch (std::out_of_range&) {
        std::cerr << "Unit not known." << std::endl;
        return -1;
    }
    
    std::cout << value << " m" << std::endl;
    
    return 0;
}
