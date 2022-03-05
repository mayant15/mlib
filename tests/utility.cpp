#include "doctest.h"

#include <mm/utility.h>
#include <utility>

using namespace mm;

class Dummy
{
public:
    enum class ConstructType
    {
        DEFAULT,
        COPY,
        MOVE
    };

    const ConstructType type;

    Dummy() : type(ConstructType::DEFAULT)
    {
    }

    Dummy(const Dummy &) : type(ConstructType::COPY)
    {
    }

    Dummy(Dummy &&) : type(ConstructType::MOVE)
    {
    }
};

TEST_CASE("Option")
{
    SUBCASE("Option::none()")
    {
        SUBCASE("should return empty optional")
        {
            auto value = Option<Dummy>::none();
            CHECK_FALSE(value.has_value);
        }
    }

    SUBCASE("Option::from()")
    {
        SUBCASE("should create new option by copy")
        {
            Dummy dummy{};

            auto option = Option<Dummy>::from(dummy);
            CHECK(option.has_value);
            CHECK(option.unwrap().type == Dummy::ConstructType::COPY);
        }

        SUBCASE("should create new option by move")
        {
            Dummy dummy{};

            auto option = Option<Dummy>::from(std::move(dummy));
            CHECK(option.has_value);
            CHECK(option.unwrap().type == Dummy::ConstructType::MOVE);
        }
    }
}

TEST_CASE("Result")
{

    const auto func = [](bool emit_left) -> Result<int, int>
    {
        if (emit_left)
        {
            return Left(1);
        }
        else
        {
            return Right(2);
        }
    };

    SUBCASE("should cast Left to Result")
    {
        const auto result = func(true);
        bool is_left;
        int contents;

        result.match(
            [&is_left, &contents](int val)
            {
                contents = val;
                is_left = true;
                return 1;
            },

            [&is_left, &contents](int val)
            {
                contents = 0;
                is_left = false;
                return 3;
            });

        CHECK(is_left);
        CHECK(contents == 1);
    }
}
