#pragma once


#include <iostream>

#include <memory>
#include <memory_resource>

#include <list>



class DynamicMemoryResource : public std::pmr::memory_resource {
public:


    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        
        void* ptr = malloc(bytes);

        if (!ptr) {
            throw std::bad_alloc();
        }
        
        blocks.emplace_back(ptr, bytes);
        return ptr;
    }

    void do_deallocate(void *ptr, std::size_t bytes, std::size_t alignment) override {
        
        auto it = blocks.begin();

        while (it != blocks.end()) {
            if (it.operator*().first == ptr) {
              blocks.erase(it);
              std::free(ptr);
            }
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

    ~DynamicMemoryResource() override {
        for (auto &[ptr, bytes]: blocks) {
            std::free(ptr);
        }
    }

private:
    std::list<std::pair<void*, std::size_t>> blocks;
};




template <class T, class allocator_type = std::pmr::polymorphic_allocator<T>>
class DynamicArray{
    private:
        allocator_type allocator;
        size_t _size;
        size_t _capacity;
        T* data;

    public:

        class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            iterator(T* ptr) : ptr(ptr) {
            }

            T &operator*() const { 
                return *ptr; 
            }
            T *operator->() const {
                return ptr; 
            }
            iterator &operator++() {
                ++ptr;
                return *this;
            }
            iterator operator++(int) {
                iterator tmp = *this;
                ++ptr;
                return tmp;
            }
            bool operator==(const iterator &other) const { 
                return ptr == other.ptr; 
            }
            bool operator!=(const iterator &other) const { 
                return ptr != other.ptr; 
            }
            T *get_ptr() const { 
                return ptr; 
            }

        private:
            T *ptr;
        };

        iterator begin() { 
            return iterator(data); 
        }
        iterator end() { 
            return iterator(data + _size);
        }

        DynamicArray (std::pmr::memory_resource *mr = std::pmr::get_default_resource()) : allocator(mr), data(nullptr), _size(0), _capacity(0) {}


        DynamicArray(const DynamicArray &other) : allocator(other.allocator), _size(other._size), _capacity(other._capacity) {
            data = allocator.allocate(_capacity);
            for (size_t i = 0; i < _size; ++i) {
                allocator.construct(data + i, other.data[i]);
            }
        }


        ~DynamicArray() {
            clear();
        }

        void push_back(const T& value) {
            if (_size == _capacity) {
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            }
            allocator.construct(data + _size, value);
            ++_size;
        }

        void pop_back() {
            if (_size > 0) {
                --_size;
            }
        }

        size_t size() const noexcept {
            return _size;
        }

        T& operator[](size_t pos) {
            return data[pos];
        }

        void reserve(size_t new_capacity) {
            if (new_capacity > _capacity) {
                T* new_data;
                T* it;
                
                for (size_t i = 0; i < new_capacity; ++i) {

                    new_data = allocator.allocate(1);

                    if (i < _size)
                        allocator.construct(new_data, data[i]);

                    if (i == 0) 
                        it = new_data;
                }

                for (size_t i = 0; i < _capacity; ++i) {
                    allocator.destroy(data + i);
                    allocator.deallocate(data + i, 1);
                }

                data = it;
                _capacity = new_capacity;
            }
        }


        void clear() {
            for (size_t i = 0; i < _size; ++i) {
                std::allocator_traits<allocator_type>::destroy(allocator, data + i);
            }
            _size = 0;
        }
};

