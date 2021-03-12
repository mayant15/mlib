#pragma once

#include <iterator>
#include <iostream>

namespace mm
{
    template<typename T>
    using default_comp = std::less<typename std::iterator_traits<T>::value_type>;

    template<typename RandomIt, typename Compare>
    void make_heap(RandomIt first, RandomIt last, Compare comp = default_comp<RandomIt>())
    {
        size_t size = std::distance(first, last);
        // NOTE: this offset will overflow if size_t is used, so use a signed int
        for (int offset = size / 2; offset >= 0; offset--) // NOLINT(cppcoreguidelines-narrowing-conversions)
        {
            sift_down(first + offset, first, last, comp);
        }
    }

    template<typename RandomIt, typename Compare>
    void pop_heap(const RandomIt first, const RandomIt last, const Compare comp = default_comp<RandomIt>())
    {
        auto tmp = *first;
        *first = *(last - 1);
        *(last - 1) = tmp;
        sift_down(first, first, last - 1, comp);
    }

    template<typename RandomIt, typename Compare>
    void push_heap(const RandomIt first, const RandomIt last, const Compare comp = default_comp<RandomIt>())
    {
        sift_up(last - 1, first, last, comp);
    }

    template<typename RandomIt>
    std::pair<RandomIt, RandomIt> get_children(const RandomIt current, const RandomIt first, const RandomIt last)
    {
        size_t o_current = std::distance(first, current);
        size_t o_left = 2 * o_current + 1;
        size_t o_right = 2 * o_current + 2;
        return { (first + o_left), (first + o_right) };
    }

    template<typename RandomIt>
    RandomIt get_parent(const RandomIt current, const RandomIt first, const RandomIt last)
    {
        if (current < last && current > first)
        {
            return first + (std::distance(first, current) - 1) / 2;
        }
        return last;
    }

    template<typename RandomIt, typename Compare>
    bool is_heap(const RandomIt current, const RandomIt first, const RandomIt last, const Compare comp)
    {
        auto [left, right] = get_children(current, first, last);
        if (left < last && comp(*current, *left))
        {
            return false;
        }
        if (right < last && comp(*current, *right))
        {
            return false;
        }
        return true;
    }

    template<typename RandomIt, typename Compare>
    void sift_down(RandomIt sift, const RandomIt first, const RandomIt last, const Compare comp)
    {
        RandomIt current = sift;
        while (!is_heap(current, first, last, comp))
        {
            // Swap with the larger child
            auto [left, right] = get_children(current, first, last);

            RandomIt larger;
            if (left < last)
            {
                larger = left;
            }
            if (right < last)
            {
                larger = (*larger < *right) ? right : larger;
            }

            std::cout << "Largest " << *larger << std::endl;
            auto tmp = *current;
            *current = *larger;
            *larger = tmp;
            current = larger;
        }
    }

    template<typename RandomIt, typename Compare>
    void sift_up(RandomIt sift, const RandomIt first, const RandomIt last, const Compare comp)
    {
        RandomIt current = sift;
        RandomIt parent = get_parent(current, first, last);
        if (parent == last)
        {
            // This node has no parent
            return;
        }

        while(!is_heap(parent, first, last, comp))
        {
            // Swap with parent
            auto tmp = *current;
            *current = *parent;
            *parent = tmp;

            current = parent;
            parent = get_parent(parent, first, last);
            if (parent == last)
            {
                return;
            }
        }
    }
}
