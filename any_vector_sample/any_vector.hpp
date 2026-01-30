#ifndef ANY_VECTOR_HPP
#define ANY_VECTOR_HPP

#include <cstdlib>
#include <cassert>
#include <memory>
#include <utility>

#ifndef ANY_VECTOR_ALLOW_SILENT_DESTRUCTION
#define ANY_VECTOR_ALLOW_SILENT_DESTRUCTION_DEFAULT false
#define ANY_VECTOR_ALLOW_SILENT_DESTRUCTION ANY_VECTOR_ALLOW_SILENT_DESTRUCTION_DEFAULT
#endif

struct any_vector {
    static constexpr bool allow_silent_destruction = ANY_VECTOR_ALLOW_SILENT_DESTRUCTION;

    void *values{nullptr};
    std::size_t size{0ull};
    std::size_t capacity{0ull};

    ~any_vector() {
        if (!allow_silent_destruction && size > 0) {
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
        size = 0;
        capacity = 0;
    }
    template <typename T>
    void destroy() {
        if (values != nullptr) {
            for (std::size_t i = 0; i < size; ++i) {
                T *const ptr = &this->operator[]<T>(i);
                std::destroy_at(ptr);
            }
        }
        std::free(values);
        values = nullptr;
        size = 0;
        capacity = 0;
    }

    any_vector() = default;
    template <typename T>
    explicit any_vector(const std::size_t initial_capacity) {
        reserve_exact<T>(initial_capacity);
    }
    template <typename T>
    explicit any_vector(const std::size_t initial_size, const T& default_value) {
        reserve_exact<T>(initial_size);
        for (std::size_t i = 0; i < initial_size; ++i) {
            std::construct_at<T>(&this->operator[]<T>(i), default_value);
        }
        size = initial_size;
    }
    template <typename T>
    any_vector(std::initializer_list<T> init_list) {
        const std::size_t init_size = init_list.size();
        reserve_exact<T>(init_size);
        std::size_t i = 0;
        for (const T& value : init_list) {
            std::construct_at<T>(&this->operator[]<T>(i), value);
            ++i;
        }
        size = init_size;
    }

    any_vector(const any_vector &other) = delete;
    any_vector &operator=(const any_vector &other) = delete;

    any_vector &operator=(any_vector &&other) = delete;
    any_vector(any_vector &&other) noexcept
        : values(other.values), size(other.size), capacity(other.capacity) {
        other.values = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    template <typename T>
    void reserve_exact(const std::size_t new_capacity) {
        if (new_capacity > capacity) {
            T* new_values = static_cast<T*>(
                std::calloc(new_capacity, sizeof(T))
            );
            if (values != nullptr) {
                for (std::size_t i = 0; i < size; ++i) {
                    T *const old = &this->operator[]<T>(i);
                    std::construct_at<T>(new_values + i, std::move(*old));
                    std::destroy_at(old);
                }
                std::free(values);
            }
            values = new_values;
            capacity = new_capacity;
        }
    }
    template <typename T>
    void reserve(const std::size_t new_capacity) {
        reserve_exact<T>(std::max(new_capacity, capacity * 2));
    }

    template <typename T>
    void shrink_exact(const std::size_t new_capacity) {
        if (new_capacity < size) {
            assert(false && "error: new capacity less than current size in call to shrink_exact<T>()");
            std::exit(EXIT_FAILURE);
        }

        if (new_capacity < capacity) {
            T* new_values = new_capacity == 0 ? nullptr : static_cast<T*>(
                std::calloc(new_capacity, sizeof(T))
            );
            for (std::size_t i = 0; i < size; ++i) {
                T *const old = &this->operator[]<T>(i);
                std::construct_at<T>(new_values + i, std::move(*old));
                std::destroy_at(old);
            }
            std::free(values);
            values = new_values;   
            capacity = new_capacity;
        }
    }
    template <typename T>
    void shrink(const std::size_t new_capacity) {
        shrink_exact<T>(std::max(new_capacity, size));
    }
    template <typename T>
    void shrink_to_fit() {
        shrink_exact<T>(size);
    }

    template <typename T>
    void push(const T& value) {
        if (size >= capacity) {
            reserve<T>(size + 1);
        }
        std::construct_at<T>(&this->operator[]<T>(size), value);
        ++size;
    }
    template <typename T, typename S = std::remove_cv_t<T>>
    void push(S &&value) {
        if (size >= capacity) {
            reserve<T>(size + 1);
        }
        std::construct_at<T>(&this->operator[]<T>(size), std::forward<S>(value));
        ++size;
    }
    template <typename T, typename... Args>
    T &emplace(Args&&... args) {
        if (size >= capacity) {
            reserve<T>(size + 1);
        }
        T *const ptr = std::construct_at<T>(&this->operator[]<T>(size), std::forward<Args>(args)...);
        ++size;
        return *ptr;
    }

    template <typename T>
    void pop() {
        if (size == 0) {
            assert(false && "error: pop from empty vector in call to pop<T>()");
            std::exit(EXIT_FAILURE);
        }
        --size;
        T *const ptr = &this->operator[]<T>(size);
        std::destroy_at(ptr);

        const std::size_t half_capacity = capacity >> 1ull;
        if (size < half_capacity) {
            shrink_exact<T>(half_capacity);
        }
    }
    template <typename T>
    void swap_last_pop(const std::size_t index) {
        if (index >= size) {
            assert(false && "error: index out of range in call to swap_last_pop<T>()");
            std::exit(EXIT_FAILURE);
        }
        T *const ptr = &this->operator[]<T>(index);
        T *const last_ptr = &this->operator[]<T>(size - 1);

        std::destroy_at(ptr);
        if (ptr != last_ptr) {
            std::construct_at<T>(ptr, std::move(*last_ptr));
            std::destroy_at(last_ptr);
        }
        --size;

        const std::size_t half_capacity = capacity >> 1ull;
        if (size < half_capacity) {
            shrink_exact<T>(half_capacity);
        }
    }
    template <typename T>
    void truncate(const std::size_t new_size) {
        if (new_size > size) {
            assert(false && "error: new size greater than current size in call to truncate<T>()");
            std::exit(EXIT_FAILURE);
        }
        for (std::size_t i = new_size; i < size; ++i) {
            T *const ptr = &this->operator[]<T>(i);
            std::destroy_at(ptr);
        }
        size = new_size;

        const std::size_t half_capacity = capacity >> 1ull;
        if (size < half_capacity) {
            shrink_exact<T>(half_capacity);
        }
    }
    template <typename T>
    void clear() {
        for (std::size_t i = 0; i < size; ++i) {
            T *const ptr = &this->operator[]<T>(i);
            std::destroy_at(ptr);
        }
        size = 0;
    }

    template <typename T>
    T &operator[](const std::size_t index) {
        return static_cast<T*>(values)[index];
    }
    template <typename T>
    const T &operator[](const std::size_t index) const {
        return static_cast<T*>(values)[index];
    }

    template <typename T>
    T &at(const std::size_t index) {
        if (index >= size) {
            assert(false && "error: index out of range accessing with at<T>()");
            std::exit(EXIT_FAILURE);
        }
        return static_cast<T*>(values)[index];
    }
    template <typename T>
    const T &at(const std::size_t index) const {
        if (index >= size) {
            assert(false && "error: index out of range accessing with at<T>()");
            std::exit(EXIT_FAILURE);
        }
        return static_cast<T*>(values)[index];
    }

    template <typename T>
    T &front() {
        return this->at<T>(0);
    }
    template <typename T>
    const T &front() const {
        return this->at<T>(0);
    }

    template <typename T>
    T &back() {
        return this->at<T>(size - 1);
    }
    template <typename T>
    const T &back() const {
        return this->at<T>(size - 1);
    }

    template <typename T>
    T *data() {
        return static_cast<T*>(values);
    }
    template <typename T>
    const T *data() const {
        return static_cast<T*>(values);
    }

    inline bool empty() const {
        return size == 0;
    }
    // inline std::size_t size() const {
    //     return size;
    // }
    // inline std::size_t capacity() const {
    //     return capacity;
    // }
};


#endif