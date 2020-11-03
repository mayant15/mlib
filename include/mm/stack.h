#pragma once

#include <deque>

namespace mm
{
    template<typename T, typename Container = std::deque<T>>
    class stack
    {
        Container _data;
    public:
        stack() : stack(Container()) {}
        explicit stack(const Container& container)
        {
            _data = container;
        }

        explicit stack(Container&& container)
        {
            _data = std::move(container);
        }

        const T& top() const
        {
            return _data.back();
        }

        [[no_discard]] bool empty() const
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
        }

        void push(T&& val)
        {
            _data.push_back(std::move(val));
        }

        template<typename... Args>
        decltype(auto) emplace(Args&& ...args)
        {
            return _data.emplace_back(std::forward<Args>(args)...);
        }

        void pop()
        {
            _data.pop_back();
        }
    };
}
