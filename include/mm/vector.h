#pragma once

#include <stdexcept>
#include <cmath>

namespace mm
{
    constexpr unsigned int CAPACITY_MULTIPLIER = 2;

    template<typename T>
    class vector
    {
    private:
        size_t _size = 0;
        size_t _capacity = 0;
        T* _data = nullptr;

    public:
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

            _data = new T[size];
        }

        vector(std::initializer_list<T> list) : vector(list.size())
        {
            for (auto iter = list.begin(); iter < list.end(); iter++)
            {
                _data[iter - list.begin()] = *iter;
            }
        }

        ~vector()
        {
           delete[] _data;
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

            _data[_size] = val;
            _size = _size + 1;
        }

    private:
        void realloc(const size_t capacity)
        {
            T* new_data = new T[capacity];
            
            for (size_t i = 0; i < _size; i++)
            {
                new_data[i] = _data[i];
            }
            delete[] _data;

            _data = new_data;
            _capacity = capacity;
        }
    };
}
