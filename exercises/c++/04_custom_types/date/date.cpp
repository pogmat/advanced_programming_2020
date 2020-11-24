#include <iostream>
#include <string>
#include <array>

enum class month_t : uint_fast8_t {
    jan,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
};

using day_t = uint_fast8_t;
using year_t = int_fast16_t;

bool is_leap(const year_t y) {
    if (y % 4) 
        return false;
    if (!(y % 400))
        return true;
    if (y % 100)
        return true;
    return false;
}

day_t days_of_month(const month_t m, const year_t y) {
    switch (m) {
    case month_t::apr:
    case month_t::jun:
    case month_t::sep:
    case month_t::nov:
        return 30;
        break;
    case month_t::feb:
        if (is_leap(y))
            return 29;
        return 28;
        break;
    default:
        return 30;
        break;
    }
}    

class date {
    day_t _day;
    month_t _month;
    year_t _year;

public:
    date(const day_t d, const month_t m, const year_t y) {
        if (d > days_of_month(m, y)) {
            std::cerr << "Wrong date!" << std::endl;
            exit(EXIT_FAILURE);
        }

        _day = d;
        _month = m;
        _year = y;
    };

    day_t day() const { return _day; }
    month_t month() const { return _month; }
    year_t year() const { return _year; }

    date& operator++();

    friend std::ostream& operator<<(std::ostream& os, const date& dt) {
        std::array<const std::string, 12> month_names {"January", 
                                                       "February",
                                                       "March",
                                                       "April",
                                                       "May",
                                                       "June",
                                                       "July",
                                                       "August",
                                                       "September",
                                                       "October",
                                                       "November",
                                                       "December"};

        os << static_cast<int>(dt._day) << " " << month_names[static_cast<uint_fast8_t>(dt._month)] << " " << dt._year;
        return os;
    }

    void add_days(const unsigned int n) {
        for (unsigned int i{0}; i < n; ++i)
            ++(*this);
    }

    date& operator+=(const unsigned int n) {
        this->add_days(n);
        return *this;
    }

    friend bool operator==(const date& lhs, const date& rhs) {
        if (lhs._day == rhs._day && lhs._month == rhs._month && lhs._year == rhs._year)
            return true;
        return false;
    }

    friend bool operator!=(const date& lhs, const date& rhs) {
        return !(lhs == rhs);
    }

};

date& date::operator++()
{
    if (_day < days_of_month(_month, _year)) {
        ++_day;
        return *this;
    }
    if (_month != month_t::dec) {
        _day = 1;
        _month = static_cast<month_t>(static_cast<uint_fast8_t>(_month) + 1);
        return *this;
    }
    _day = 1;
    _month = month_t::jan;
    ++_year;
    return *this;
}

int main()
{
    date bday{15, month_t::jan, 1988};
    bday += 11763;
    std::cout << bday << std::endl;
    std::cout << (bday == date(15, month_t::nov, 2020)) << std::endl;


    return 0;
}