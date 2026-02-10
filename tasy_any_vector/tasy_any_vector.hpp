#ifndef TASY_ANY_VECTOR_HPP
#define TASY_ANY_VECTOR_HPP

#include <cstdlib>
#include <memory>
#include <utility>

// TODO: migrate to `tasy::panic` and alike in `tasy_error.hpp`. Instead of just the default `assert` and `std::exit`.
#include <cassert>

namespace tasy {
    struct any_vector {
        void *values{nullptr};
        std::size_t used_size{0ull};
        std::size_t allocation_size{0ull};

        ~any_vector();
        template <typename T>
        void destroy();

        any_vector() = default;
        template <typename T>
        explicit any_vector(const std::size_t initial_size, const T& default_value);
        template <typename T>
        any_vector(std::initializer_list<T> init_list);


        any_vector(const any_vector &other) = delete;
        any_vector &operator=(const any_vector &other) = delete;

        any_vector &operator=(any_vector &&other);
        any_vector(any_vector &&other) noexcept;


        template <typename T>
        void reserve_exact(const std::size_t new_capacity);
        template <typename T>
        void reserve(const std::size_t new_capacity);


        template <typename T>
        void shrink_exact(const std::size_t new_capacity);
        template <typename T>
        void shrink(const std::size_t new_capacity);
        template <typename T>
        void shrink_to_fit();


        template <typename T>
        void push(const T& value);
        template <typename T, typename S = std::remove_cv_t<T>>
        void push(S &&value);
        template <typename T, typename... Args>
        T &emplace(Args&&... args);


        template <typename T>
        void insert(const std::size_t index, const T& value);
        template <typename T, typename S = std::remove_cv_t<T>>
        void insert(const std::size_t index, S &&value);
        template <typename T, typename... Args>
        T &emplace(const std::size_t index, Args&&... args);


        template <typename T>
        void extend_with(const std::size_t count, const T& value);
        
        // TODO: add if needed
        // template <typename InputIterator>
        // void extend(InputIterator first, InputIterator last);

        template <typename T>
        void pop();
        template <typename T>
        void swap_last_pop(const std::size_t index);
        template <typename T>
        void truncate(const std::size_t new_size);
        template <typename T>
        void clear();

        // XXX: prefer to use explicitly `extend_with(count, value)` and `truncate(new_size)` instead of `resize(new_size, default_value)`.
        //      Might add `resize` if needed. 
        // template <typename T>
        // void resize(const std::size_t new_size, const T& default_value);


        template <typename T>
        T &operator[](const std::size_t index);
        template <typename T>
        const T &operator[](const std::size_t index) const;

        template <typename T>
        T &at(const std::size_t index);
        template <typename T>
        const T &at(const std::size_t index) const;

        template <typename T>
        T &front();
        template <typename T>
        const T &front() const;

        template <typename T>
        T &back();
        template <typename T>
        const T &back() const;

        template <typename T>
        T *data();
        template <typename T>
        const T *data() const;

        inline bool empty() const;
        inline std::size_t size() const;
        inline std::size_t capacity() const;
    };

    template <typename T>
    inline void any_vector::destroy() {
        if (values != nullptr) {
            for (std::size_t i = 0; i < used_size; ++i) {
                T *const ptr = &this->operator[]<T>(i);
                std::destroy_at(ptr);
            }
        }
        std::free(values);
        values = nullptr;
        used_size = 0;
        allocation_size = 0;
    }
    
    template <typename T>
    inline any_vector::any_vector(const std::size_t initial_size, const T &default_value) {
        extend_with<T>(initial_size, default_value);
    }
    template <typename T>
    inline any_vector::any_vector(std::initializer_list<T> init_list) {
        const std::size_t init_size = init_list.size();
        reserve_exact<T>(init_size);
        std::size_t i = 0;
        for (const T& value : init_list) {
            std::construct_at<T>(&this->operator[]<T>(i), value);
            ++i;
        }
        used_size = init_size;
    }
    
    template <typename T>
    inline void any_vector::reserve_exact(const std::size_t additional_capacity) {
        if (additional_capacity > allocation_size - used_size) {
            const std::size_t new_capacity = allocation_size + additional_capacity;
            T *const new_values = static_cast<T*>(
                std::calloc(new_capacity, sizeof(T))
            );
            if (values != nullptr) {
                for (std::size_t i = 0; i < used_size; ++i) {
                    T *const old = &this->operator[]<T>(i);
                    std::construct_at<T>(new_values + i, std::move(*old));
                    std::destroy_at(old);
                }
                std::free(values);
            }
            values = new_values;
            allocation_size = new_capacity;
        }
    }
    template <typename T>
    inline void any_vector::reserve(const std::size_t additional_capacity) {
        reserve_exact<T>(std::max(additional_capacity, used_size << 1ull));
    }

    template <typename T>
    inline void any_vector::shrink_exact(const std::size_t new_capacity) {
        if (new_capacity < used_size) {
            assert(false && "error: new capacity less than current size in call to shrink_exact<T>()");
            std::exit(EXIT_FAILURE);
        }

        if (new_capacity < allocation_size) {
            T* new_values = new_capacity == 0 ? nullptr : static_cast<T*>(
                std::calloc(new_capacity, sizeof(T))
            );
            for (std::size_t i = 0; i < used_size; ++i) {
                T *const old = &this->operator[]<T>(i);
                std::construct_at<T>(new_values + i, std::move(*old));
                std::destroy_at(old);
            }
            std::free(values);
            values = new_values;   
            allocation_size = new_capacity;
        }
    }
    template <typename T>
    inline void any_vector::shrink(const std::size_t new_capacity){
        shrink_exact<T>(std::max(new_capacity, used_size));
    }
    template <typename T>
    inline void any_vector::shrink_to_fit() {
        shrink_exact<T>(used_size);
    }


    template <typename T>
    inline void any_vector::push(const T &value) {
        if (used_size >= allocation_size) {
            reserve<T>(1ull);
        }
        std::construct_at<T>(&this->operator[]<T>(used_size), value);
        ++used_size;
    }
    template <typename T, typename S>
    inline void any_vector::push(S &&value) {
        if (used_size >= allocation_size) {
            reserve<T>(1ull);
        }
        std::construct_at<T>(&this->operator[]<T>(used_size), std::forward<S>(value));
        ++used_size;
    }
    template <typename T, typename... Args>
    inline T &any_vector::emplace(Args &&...args) {
        if (used_size >= allocation_size) {
            reserve<T>(1ull);
        }
        T *const ptr = std::construct_at<T>(&this->operator[]<T>(used_size), std::forward<Args>(args)...);
        ++used_size;
        return *ptr;
    }


    template <typename T>
    inline void any_vector::insert(const std::size_t index, const T &value) {
        if (index > used_size) {
            assert(false && "error: index out of range in call to insert<T>()");
            std::exit(EXIT_FAILURE);
        }
        if (used_size >= allocation_size) {
            reserve<T>(1ull);
        }
        for (std::size_t i = used_size; i > index; --i) {
            T *const to = &this->operator[]<T>(i);
            T *const from = &this->operator[]<T>(i - 1);
            std::construct_at<T>(to, std::move(*from));
            std::destroy_at(from);
        }
        std::construct_at<T>(&this->operator[]<T>(index), value);
        ++used_size;
    }
    template <typename T, typename S>
    inline void any_vector::insert(const std::size_t index, S &&value) {
        if (index > used_size) {
            assert(false && "error: index out of range in call to insert<T>()");
            std::exit(EXIT_FAILURE);
        }
        if (used_size >= allocation_size) {
            reserve<T>(1ull);
        }
        for (std::size_t i = used_size; i > index; --i) {
            T *const to = &this->operator[]<T>(i);
            T *const from = &this->operator[]<T>(i - 1);
            std::construct_at<T>(to, std::move(*from));
            std::destroy_at(from);
        }
        std::construct_at<T>(&this->operator[]<T>(index), std::forward<S>(value));
        ++used_size;
    }
    template <typename T, typename... Args>
    inline T &any_vector::emplace(const std::size_t index, Args &&...args) {
        if (index > used_size) {
            assert(false && "error: index out of range in call to emplace<T>()");
            std::exit(EXIT_FAILURE);
        }
        if (used_size >= allocation_size) {
            reserve<T>(1ull);
        }
        for (std::size_t i = used_size; i > index; --i) {
            T *const to = &this->operator[]<T>(i);
            T *const from = &this->operator[]<T>(i - 1);
            std::construct_at<T>(to, std::move(*from));
            std::destroy_at(from);
        }
        T *const ptr = std::construct_at<T>(&this->operator[]<T>(index), std::forward<Args>(args)...);
        ++used_size;
        return *ptr;
    }

    template <typename T>
    inline void any_vector::extend_with(const std::size_t count, const T &value) {
        reserve<T>(count);
        for (std::size_t i = 0; i < count; ++i) {
            std::construct_at<T>(&this->operator[]<T>(i), value);
        }
        used_size += count;
    }

    template <typename T>
    inline void any_vector::pop() {
        if (used_size == 0) {
            assert(false && "error: pop from empty vector in call to pop<T>()");
            std::exit(EXIT_FAILURE);
        }
        --used_size;
        T *const ptr = &this->operator[]<T>(used_size);
        std::destroy_at(ptr);
    }
    template <typename T>
    inline void any_vector::swap_last_pop(const std::size_t index)  {
        if (index >= used_size) {
            assert(false && "error: index out of range in call to swap_last_pop<T>()");
            std::exit(EXIT_FAILURE);
        }
        T *const ptr = &this->operator[]<T>(index);
        T *const last_ptr = &this->operator[]<T>(used_size - 1);

        std::destroy_at(ptr);
        if (ptr != last_ptr) {
            std::construct_at<T>(ptr, std::move(*last_ptr));
            std::destroy_at(last_ptr);
        }
        --used_size;
    }
    template <typename T>
    inline void any_vector::truncate(const std::size_t new_size) {
        if (new_size > used_size) {
            assert(false && "error: new size greater than current size in call to truncate<T>()");
            std::exit(EXIT_FAILURE);
        }
        for (std::size_t i = new_size; i < used_size; ++i) {
            T *const ptr = &this->operator[]<T>(i);
            std::destroy_at(ptr);
        }
        used_size = new_size;
    }
    template <typename T>
    inline void any_vector::clear()  {
        for (std::size_t i = 0; i < used_size; ++i) {
            T *const ptr = &this->operator[]<T>(i);
            std::destroy_at(ptr);
        }
        used_size = 0;
    }


    template <typename T>
    inline T &any_vector::operator[](const std::size_t index) {
        return static_cast<T*>(values)[index];
    }
    template <typename T>
    inline const T &any_vector::operator[](const std::size_t index) const {
        return static_cast<T*>(values)[index];
    }

    template <typename T>
    inline T &any_vector::at(const std::size_t index) {
        if (index >= used_size) {
            assert(false && "error: index out of range accessing with at<T>()");
            std::exit(EXIT_FAILURE);
        }
        return static_cast<T*>(values)[index];
    }
    template <typename T>
    inline const T &any_vector::at(const std::size_t index) const {
        if (index >= used_size) {
            assert(false && "error: index out of range accessing with at<T>()");
            std::exit(EXIT_FAILURE);
        }
        return static_cast<T*>(values)[index];
    }

    template <typename T>
    inline T &any_vector::front() {
        return this->at<T>(0);
    }
    template <typename T>
    inline const T &any_vector::front() const {
        return this->at<T>(0);
    }

    template <typename T>
    inline T &any_vector::back() {
        return this->at<T>(used_size - 1ull);
    }
    template <typename T>
    inline const T &any_vector::back() const {
        return this->at<T>(used_size - 1ull);
    }

    template <typename T>
    inline T *any_vector::data() {
        return static_cast<T*>(values);
    }
    template <typename T>
    inline const T *any_vector::data() const {
        return static_cast<const T*>(values);
    }

    
    inline bool any_vector::empty() const {
        return used_size == 0;
    }
    inline std::size_t any_vector::size() const {
        return used_size;
    }
    inline std::size_t any_vector::capacity() const {
        return allocation_size;
    }
}

#endif
