#pragma once

#include <cassert>
#include <stdexcept>

namespace mm::concurrent
{
    template<class T>
    class set
    {
    public:
        set()
        {
            _head = new node;
            _tail = new node;
            _head->_next = _tail;
        }

        ~set()
        {
            auto current = _head;
            while (current != nullptr)
            {
                auto tmp = current->_next;
                delete current;
                current = tmp;
            }
        }

        void add(T val)
        {
            // Create new node
            auto newnode = new node;
            newnode->_data = val;

            // Find insert position
            node* current = nullptr;
            if (_size == 0)
            {
                current = _head;
            }
            else
            {
                current = _head->_next;
                while (current->_data < val && current->_next != _tail)
                {
                    current = current->_next;
                }
            }

            newnode->_next = current->_next;
            current->_next = newnode;
            ++_size;
        }

        void remove(T val)
        {
            assert(_size != 0);
            auto current = _head->_next;
            auto prev = _head;
            while (current != _tail && current->_data != val)
            {
                prev = current;
                current = current->_next;
            }

            if (current == _tail)
            {
                throw std::runtime_error { "Value does not exist" };
            }

            prev->_next = current->_next;
            delete current;
            --_size;
        }

        bool contains(T val)
        {
            if (_size == 0) return false;

            auto current = _head->_next;
            while (current != _tail && current->_data != val)
            {
                current = current->_next;
            }

            return (current != _tail);
        }

        [[nodiscard]] size_t size() const { return _size; }

    private:

        struct node
        {
            T _data {};
            node* _next = nullptr;
        };

    private:
        node* _head = nullptr;
        node* _tail = nullptr;
        size_t _size = 0;
    };
}
