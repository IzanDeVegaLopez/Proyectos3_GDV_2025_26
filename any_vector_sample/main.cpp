#include "any_vector.hpp"
#include <iostream>
#include <limits>

struct custom {
    size_t value;
    custom(const size_t v) : value(v) {
        std::cout << "custom constructed: " << value << std::endl;
    }
    ~custom() {
        if (value != std::numeric_limits<size_t>::max()) {
            std::cout << "custom destructed: " << value << std::endl;
        }
        value = std::numeric_limits<size_t>::max();
    }

    custom(const custom &other) = default;
    custom &operator=(const custom &other) = default;

    custom(custom &&other) noexcept : value(other.value) {
        other.value = std::numeric_limits<size_t>::max();
    }
    custom &operator=(custom &&other) noexcept {
        if (this != &other) {
            value = other.value;
            other.value = std::numeric_limits<size_t>::max();
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const custom &c);
};
std::ostream &operator<<(std::ostream &os, const custom &c) {
    os << c.value;
    return os;
}

int main(void) {
    any_vector vec{};
    vec.reserve<custom>(8);
    for (size_t i = 0; i < 5; ++i) {
        vec.push<custom>(i * 10);
    }
    for (size_t i = 0; i < vec.size; ++i) {
        std::cout << "Element " << i << ": " << vec.at<custom>(i) << std::endl;
    }
    
    vec.emplace<custom>(42);
    std::cout << "After emplace: " << vec.at<custom>(5) << std::endl;
    
    vec.pop<custom>();
    std::cout << "After pop, size: " << vec.size << std::endl;
    vec.swap_last_pop<custom>(1);
    std::cout << "After swap_last_pop at index 1:" << std::endl;
    for (size_t i = 0; i < vec.size; ++i) {
        std::cout << "Element " << i << ": " << vec.at<custom>(i) << std::endl;
    }
    vec.truncate<custom>(2);
    vec.shrink<custom>(2);
    std::cout << "After truncate to size 2, size: " << vec.size << std::endl;
    
    vec.destroy<custom>();
    return 0;
}