#include "doctest.h"
#include <mm/lock.h>

#include <chrono>

TEST_CASE("Test the filter_lock class")
{
    int x = 0;
    mm::filter_lock lock;

    auto func = [&](){
        lock.lock();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        x++;
        lock.unlock();
    };

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    CHECK(x == 2);
}
