#include "doctest.h"
#include <mm/vector.h>
#include <string>

TEST_CASE("Testing the vector class") 
{
    mm::vector<int> ivec {1, 2, 3};
    mm::vector<std::string> svec {"hello", "world", "!"};
    
    REQUIRE(ivec.size() == 3);
    REQUIRE(ivec.capacity() == 4);

    SUBCASE("Test move")
    {
        auto new_ivec = std::move(ivec);
        CHECK(new_ivec.size() == 3);
        CHECK(new_ivec.front() == 1);
        CHECK(new_ivec.capacity() == 4);
        CHECK(ivec.data() == nullptr);
        CHECK(ivec.size() == 0);
        CHECK(ivec.capacity() == 0);

        auto new_svec = std::move(svec);
        CHECK(new_svec.size() == 3);
        CHECK(new_svec.front() == "hello");
        CHECK(new_svec.capacity() == 4);
        CHECK(svec.data() == nullptr);
        CHECK(svec.size() == 0);
        CHECK(svec.capacity() == 0);
    }

    SUBCASE("Test vector::operator[]")
    {
        CHECK(ivec[2] == 3);
        ivec[2] = 10;
        CHECK(ivec[2] == 10);

        CHECK(svec[2] == "!");
        svec[2] = "test";
        CHECK(svec[2] == "test");
    }

    SUBCASE("Test vector::at()")
    {
        CHECK(ivec.at(2) == 3);
        CHECK_THROWS_AS(ivec.at(10), std::out_of_range);

        CHECK(svec.at(2) == "!");
        CHECK_THROWS_AS(ivec.at(10), std::out_of_range);
    }

    SUBCASE("Test vector::front()")
    {
        CHECK(ivec.front() == 1);
        CHECK(svec.front() == "hello");
    }

    SUBCASE("Test vector::back()")
    {
        CHECK(ivec.back() == 3);
        CHECK(svec.back() == "!");
    }

    SUBCASE("Test vector::push_back()")
    {
        ivec.push_back(30);
        CHECK(ivec.size() == 4);
        CHECK(ivec.back() == 30);

        svec.push_back("next");
        CHECK(svec.size() == 4);
        CHECK(svec.back() == "next");
    }

    SUBCASE("Test vector::realloc()")
    {
        CHECK(true);
        // TODO
//        ivec.push_back(20);
//        ivec.push_back(30);
//        CHECK(ivec.capacity() == 8);
//        CHECK(ivec.back() == 30);
//
//        svec.push_back("new");
//        svec.push_back("word");
//        CHECK(svec.capacity() == 8);
//        CHECK(svec.back() == "word");
    }

    SUBCASE("Test vector::empty()")
    {
        mm::vector<int> empty;
        CHECK(empty.empty());
        CHECK_FALSE(ivec.empty());
    }

    SUBCASE("Test vector::data()")
    {
        CHECK(*ivec.data() == ivec.front());
        CHECK_FALSE(ivec.empty());

        CHECK(*svec.data() == svec.front());
        CHECK_FALSE(svec.empty());
    }
}
