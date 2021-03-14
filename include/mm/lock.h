#pragma once

#include <thread>
#include <unordered_map>
#include <cassert>
#include <vector>

namespace mm
{
    struct filter_lock
    {
        void lock()
        {
            auto id = std::this_thread::get_id();
            _level.insert_or_assign(id, 0);
            for (size_t i = 0; i < _level.size(); ++i)
            {
                _level[id] = i;
                _victim[i] = id;

                bool k_found = false;
                for (auto& iter : _level)
                {
                    if ((iter.second > i) && (iter.first != id))
                    {
                        k_found = true;
                        break;
                    }
                }

                while (k_found && _victim[i] == id)
                {}
            }
        }

        void unlock()
        {
            auto id = std::this_thread::get_id();
            auto iter = _level.find(id);
            assert(iter != _level.end()); // unlock shouldn't be called before lock
            _level[id] = 0;
        }

    private:
        std::unordered_map<std::thread::id, size_t> _level;
        std::unordered_map<size_t, std::thread::id> _victim;
    };
}
