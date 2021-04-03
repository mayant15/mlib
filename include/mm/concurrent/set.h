#pragma once

#include <mutex>
#include <cassert>
#include <atomic>
#include <functional>
#include <stdexcept>

namespace mm::concurrent
{
    template<class T, class Hash = std::hash<T>>
    class lazy_set
    {
    public:
        lazy_set()
        {
            _head = new node;
            _tail = new node;
            _head->_next = _tail;
            _tail->_key = std::numeric_limits<size_t>::max();
        }

        ~lazy_set()
        {
            auto current = _head;
            while (current != nullptr)
            {
                auto tmp = current->_next;
                delete current;
                current = tmp;
            }
        }

        bool add(T val)
        {
            size_t key = _hash(val);
            while(true) // keep retrying
            {
                // Find the node to add this after
                node* prev = _head;
                node* curr = _head->_next;
                while(curr->_key < key)
                {
                    prev = curr;
                    curr = curr->_next;
                }

                // insert between prev and curr
                try
                {
                    // lock the nodes that we're operating on and validate
                    std::scoped_lock lock(prev->_mutex, curr->_mutex);
                    if (validate(prev, curr))
                    {
                        // check if already present
                        if (curr->_key == key) return false;

                        // add if not present
                        node* n = new node;
                        n->_data = val;
                        n->_key = key;
                        prev->_next = n;
                        n->_next = curr;
                        _size++;
                        return true;
                    }
                }
                catch (...) {}
            }
        }

        bool remove(T val)
        {
            if (_size == 0) return false;

            size_t key = _hash(val);
            while(true)
            {
                // find the node to remove
                node* prev = _head;
                node* curr = prev->_next;
                while(curr->_key < key)
                {
                    prev = curr;
                    curr = curr->_next;
                }

                try
                {
                    std::scoped_lock lock(prev->_mutex, curr->_mutex);
                    if (validate(prev, curr))
                    {
                        if (curr->_key != key) return false;

                        curr->_marked = true; // TODO: no garbage collection here, curr will dangle. shared_ptr?
                        prev->_next = curr->_next;
                        _size--;
                        return true;
                    }
                }
                catch (...) {}
            }
        }

        bool contains(T val)
        {
            size_t key = _hash(val);
            node* curr = _head;
            while(curr->_key < key)
            {
                curr = curr->_next;
            }
            return (!curr->_marked) && (curr->_key == key);
        }

        [[nodiscard]] size_t size() const { return _size; }

    private:
        struct node
        {
            T _data {};
            size_t _key = 0;
            bool _marked = false;
            node* _next = nullptr;
            std::mutex _mutex {};
        };

        node* _head = nullptr;
        node* _tail = nullptr;
        std::atomic<size_t> _size = 0;
        Hash _hash {};

    private:
        bool validate(const node* prev, const node* curr)
        {
            return (!prev->_marked) && (!curr->_marked) && (prev->_next == curr);
        }
    };

    template<class T>
    class non_blocking_set
    {
        //
    };
}
