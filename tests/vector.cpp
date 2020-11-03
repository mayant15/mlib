#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/mm/vector.h"

TEST_CASE("Testing the vector class") 
{
    mm::vector<int> vec = {1, 2, 3};
    REQUIRE(vec.size() == 3);
    REQUIRE(vec.capacity() == 4);

    SUBCASE("Test direct access and assignment")
    {
        CHECK(vec[2] == 3);
        vec[2] = 10;
        CHECK(vec[2] == 10);
    }

    SUBCASE("Test vector::at()")
    {
        CHECK(vec.at(2) == 3);
        CHECK_THROWS_AS(vec.at(10), std::out_of_range);
    }

    SUBCASE("Test vector::front()")
    {
        CHECK(vec.front() == 1);
    }

    SUBCASE("Test vector::back()")
    {
        CHECK(vec.back() == 3);
    }

    SUBCASE("Test vector::push_back()")
    {
        vec.push_back(30);
        CHECK(vec.size() == 4);
        CHECK(vec.back() == 30);
    }

    SUBCASE("Test vector::realloc()")
    {
        vec.push_back(20);
        vec.push_back(30);
        CHECK(vec.capacity() == 8);
        CHECK(vec.back() == 30);
    }

    SUBCASE("Test vector::empty()")
    {
        mm::vector<int> empty;
        CHECK(empty.empty());
        CHECK_FALSE(vec.empty());
    }

    SUBCASE("Test vector::data()")
    {
        CHECK(*vec.data() == vec.front());
        CHECK_FALSE(vec.empty());
    }
}
