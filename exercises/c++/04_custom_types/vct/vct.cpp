#include <iostream>

template <typename T>
class vct {
    T* v_ptr;
    std::size_t size;
public:
    vct(const std::size_t n) : v_ptr{new T[n]}, size{n} {}
    ~vct() {delete[] v_ptr;}

    T& operator[](const std::size_t i) {
        std::cout << "operator[]" << std::endl;
        return v_ptr[i];}
    const T& operator[](const std::size_t i) const {
        std::cout << "operator[] const" << std::endl;
        return v_ptr[i];}

    T* begin() {
        std::cout << "begin" << std::endl;
        return v_ptr;}
    T* end() {
        std::cout << "end" << std::endl;
        return v_ptr + size;}

    const T* begin() const {
        std::cout << "begin const" << std::endl;
        return v_ptr;}
    const T* end() const {
        std::cout << "end const" << std::endl;
        return v_ptr + size;}

    const T* cbegin() const {
        std::cout << "cbegin const" << std::endl;
        return v_ptr;}
    const T* cend() const {
        std::cout << "cend const" << std::endl;
        return v_ptr + size;}
};

int main()
{
    vct<int> v{5};
    const vct<int> cv{3};

    for (auto& x : v)
        x = 5; 
    v[0] = 7;

    const auto& cr_v = v;
        std::cout << cr_v[0] << std::endl;
    for (const auto& x : cr_v)
        std::cout << x << std::endl;
        
    
    for (const auto& x : cv)
        std::cout << x << std::endl;

    return 0;
}