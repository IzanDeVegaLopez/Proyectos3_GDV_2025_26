#include "tasy_any_vector.hpp"

namespace tasy {
    any_vector::~any_vector() {
        if (used_size > 0) {
            assert(
                false
                && "error: destroying any_vector with non-zero size. "
                "any_vector needs to ensure there are no elements contained before destruction. "
                "Try calling destroy<T>(), clear<T>() or truncate<T>(0) before the destructor is run."
            );
            std::exit(EXIT_FAILURE);
        }
        std::free(values);
        values = nullptr;
        used_size = 0;
        allocation_size = 0;
    }
    
    any_vector &any_vector::operator=(any_vector &&other) {
        if (used_size > 0) {
            assert(
                false
                && "error: move-assigning to any_vector with non-zero size. "
                "any_vector needs to ensure there are no elements contained before move-assignment. "
                "Try calling destroy<T>(), clear<T>() or truncate<T>(0) before the move-assignment is run."
            );
            std::exit(EXIT_FAILURE);
        }
        if (this != &other) {
            std::free(values);
            values = std::exchange(other.values, nullptr);
            used_size = std::exchange(other.used_size, 0);
            allocation_size = std::exchange(other.allocation_size, 0);
        }
        return *this;
    }
    any_vector::any_vector(any_vector &&other) noexcept
        : values(other.values), used_size(other.used_size), allocation_size(other.allocation_size) {
        other.values = nullptr;
        other.used_size = 0;
        other.allocation_size = 0;
    }
}