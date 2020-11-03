#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/mm/stack.h"

#include <string>

struct dummy
{
    int x;
    dummy(int x) : x(x) {}
};

TEST_CASE("Testing the stack class") 
{
    mm::stack<int> istack;
    mm::stack<std::string> sstack;

    REQUIRE(istack.size() == 0);
    REQUIRE(istack.empty());

    SUBCASE("Test stack::push()")
    {
        istack.push(2);
        CHECK(istack.size() == 1);

        sstack.push("hello");
        CHECK(sstack.size() == 1);

        mm::stack<dummy> dstack;
        dstack.push(dummy {2});
        CHECK(dstack.top().x == 2);
    }

    SUBCASE("Test stack::top()")
    {
        istack.push(2);
        CHECK(istack.top() == 2);

        sstack.push("hello");
        CHECK(sstack.top() == "hello");
    }

    SUBCASE("Test stack::pop()")
    {
        istack.push(1);
        istack.pop();
        CHECK(istack.size() == 0);

        sstack.push("hello");
        sstack.pop();
        CHECK(sstack.size() == 0);
    }

    SUBCASE("Test stack::emplace()")
    {
        mm::stack<dummy> dstack;
        dstack.emplace(3);
        CHECK(dstack.top().x == 3);
    }
}
