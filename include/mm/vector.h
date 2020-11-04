#pragma once

#include <memory>
#include <stdexcept>
#include <cmath>

namespace mm
{
    constexpr unsigned int CAPACITY_MULTIPLIER = 2;

    template<typename T, typename Allocator = std::allocator<T>>
    class vector
    {
    private:
        size_t _size = 0;
        size_t _capacity = 0;
        T* _data = nullptr;

    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        
        using traits = std::allocator_traits<Allocator>;
        using pointer = traits::pointer;
        using const_pointer = traits::const_pointer;

        vector(const size_t size = 0) : _size(size)
        {
            if (size == 0)
            {
                _capacity = 1;
            }
            else
            {
                _capacity = std::pow(2, std::ceil(std::log2(_size)));
            }

            Allocator ac;
            _data = traits::allocate(ac, _capacity, nullptr);
        }

        vector(const vector& other) : _size(other.size()), _capacity(other.capacity())
        {
            Allocator ac;
            _data = traits::allocate(ac, _capacity, nullptr);
            T* other_data = other.data();
            for (size_t i = 0; i < _size; i++)
            {
                traits::construct(ac, _data + i, other_data[i]);
            }
        }

        vector(vector&& other) noexcept : _size(other.size()), _capacity(other.capacity())
        {
            Allocator ac;
            _data = traits::allocate(ac, _capacity, nullptr);
            T* other_data = other.data();
            for (size_t i = 0; i < _size; i++)
            {
                traits::construct(ac, _data + i, other_data[i]);
                traits::destroy(ac, other_data + i);
            }
            traits::deallocate(ac, other_data, _capacity);
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }

        vector(std::initializer_list<T> list) : vector(list.size())
        {
            Allocator ac;
            for (auto iter = list.begin(); iter < list.end(); iter++)
            {
                traits::construct(ac, _data + (iter - list.begin()), *iter);
            }
        }

        ~vector()
        {
            Allocator ac;
            for (size_t i = 0; i < _size; i++)
            {
                traits::destroy(ac, _data + i);
            }
            traits::deallocate(ac, _data, _capacity);
        }

        size_t size() const
        {
            return _size;
        }

        size_t capacity() const
        {
            return _capacity;
        }

        const T& operator[](const size_t index) const
        {
            return *(_data + index);
        }

        T& operator[](const size_t index)
        {
            return *(_data + index);
        }

        T& at(const size_t index)
        {
            if (index >= _size)
            {
                throw std::out_of_range("index out of range");
            }

            return *(_data + index);
        }

        T* data() const
        {
            return _data;
        }

        T& front() const
        {
            return *_data;
        }

        T& back() const
        {
            return *(_data + _size - 1);
        }

        bool empty() const
        {
            return (_size == 0);
        }

        void push_back(const T& val)
        {
            if (_size + 1 > _capacity)
            {
                realloc(CAPACITY_MULTIPLIER * _capacity);
            }

            Allocator ac;
            traits::construct(ac, _data + _size, val);
            _size = _size + 1;
        }

    private:
        void realloc(const size_t capacity)
        {
            Allocator ac;
            T* new_data = traits::allocate(ac, capacity, nullptr);
            
            for (size_t i = 0; i < _size; i++)
            {
                new_data[i] = _data[i];
            }
            
            // Delete old data
            for (size_t i = 0; i < _size; i++)
            {
                traits::destroy(ac, _data + i);
            }
            traits::deallocate(ac, _data, _capacity);
            _data = new_data;
            _capacity = capacity;
        }
    };
}
