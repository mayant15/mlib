#pragma once

// TODO: Use custom versions
#include <deque>
#include <vector>

#include <algorithm>

namespace mm
{
    template<typename T, typename Container = std::deque<T>>
    class queue
    {
        //
    };

    template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
    class priority_queue
    {
    private:
        Container _data;
        Compare _compare;

    public:
        priority_queue() : priority_queue(Compare(), Container()) {}
        explicit priority_queue(const Compare& compare) : priority_queue(compare, Container()) {}
        priority_queue(const Compare& compare, const Container& container) : _compare(compare), _data(container)
        {
            std::make_heap(_data.begin(), _data.end());
        }

        priority_queue(const priority_queue& other) : _compare(std::move(other._compare)), _data(other._data) {}
        priority_queue(priority_queue&& other) : _compare(std::move(other._compare)), _data(std::move(other._data)) {}

        const T& top() const
        {
            return _data[0];
        }

        bool empty() const
        {
            return (_data.size() == 0);
        }

        size_t size() const
        {
            return _data.size();
        }

        void push(const T& val)
        {
            _data.push_back(val);
            std::push_heap(_data.begin(), _data.end(), _compare);
        }

        void push(T&& val)
        {
            _data.push_back(std::move(val));
            std::push_heap(_data.begin(), _data.end(), _compare);
        }

        template<typename ...Args>
        void emplace(Args&& ...args)
        {
            _data.emplace_back(std::forward<Args>(args)...);
            std::push_heap(_data.begin(), _data.end(), _compare);
        }

        void pop()
        {
            std::pop_heap(_data.begin(), _data.end(), _compare);
            _data.pop_back();
        }
    };
}
