#include <iostream>
#include <string>

void func(std::string s) {
    std::cout << s << std::endl;
}

int main() {
    const std::string test{"First,second  ,third,,,;; fourth   fifth,   ,"};

    auto curr_p = test.begin();
    auto begin_word = test.begin();
    auto end_s = test.end();
    int alpha_prev{0}, alpha_curr;
    for(; curr_p != end_s; ++curr_p) {
        alpha_curr = std::isalpha(*curr_p);
        if (alpha_curr && !alpha_prev) {
            begin_word = curr_p;
        } else if (!alpha_curr && alpha_prev) {
            func(std::string(begin_word, curr_p));
        }

    alpha_prev = alpha_curr;
    }
    if (alpha_curr)
        func(std::string(begin_word, end_s));


    return 0;
}