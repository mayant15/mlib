#pragma once

namespace mm
{
    constexpr unsigned int RAND_MAX = (1 << 31);

    struct uniform_generator
    {
        explicit uniform_generator(unsigned int seed = 1) : _next(seed) {}

        double next()
        {
            _next = (1103515245 * _next + 12345) % RAND_MAX;
            return _next / static_cast<double>(RAND_MAX);
        }

    private:
        unsigned int _next;
    };
}
