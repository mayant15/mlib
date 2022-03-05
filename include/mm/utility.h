#pragma once

#include "assert.h"

namespace mm
{

    template <class T>
    constexpr T &&forward(T &&arg)
    {
        return static_cast<T &&>(arg);
    }

    template <class T>
    class Lazy
    {
    public:
        Lazy() = default;
        ~Lazy()
        {
            if (p_data != nullptr)
            {
                delete p_data;
            }
        }

        [[nodiscard]] inline const T &get() const
        {
            assert((p_data != nullptr));
            return *p_data;
        }

        [[nodiscard]] inline T &get()
        {
            if (p_data == nullptr)
            {
                p_data = new T();
            }
            return *p_data;
        }

        template <class Arg>
        inline void set(Arg &&arg)
        {
            delete p_data;
            p_data = new T(forward(arg));
        }

    private:
        T *p_data = nullptr;
    };

    template <class T>
    class Option
    {
    public:
        bool has_value = false;

        static Option<T> none()
        {
            return Option();
        }

        template <class Arg>
        static Option<T> from(Arg &&arg)
        {
            return Option(forward(arg));
        }

        [[nodiscard]] const T &unwrap() const
        {
            return value.get();
        }

        ~Option()
        {
        }

    private:
        Lazy<T> value;

        Option()
            : has_value(false),
              value()
        {
        }

        Option(const T &arg)
            : has_value(true),
              value()
        {
            value.set(arg);
        }

        Option(T &&arg)
            : has_value(true),
              value()
        {
            value.set(arg);
        }
    };

    template <class L, class R>
    class Result;

    template <class T>
    struct Left
    {
        const T value;

        Left(const T &v) : value(v) {}
        Left(T &&v) : value(v) {}

        template <class R>
        operator Result<T, R>()
        {
            return Result(*this);
        }
    };

    template <class T>
    struct Right
    {
        const T value;

        Right(const T &v) : value(v) {}
        Right(T &&v) : value(v) {}

        template <class L>
        operator Result<L, T>()
        {
            return Result(*this);
        }
    };

    template <class U, class V>
    struct IsSameType
    {
        static constexpr value = false;
    };

    template <class T>
    struct IsSameType<T, T>
    {
        static constexpr value = true;
    };

    template <class L, class R>
    class Result
    {
    public:
        Result(const Right<R> &r) : has_left(false)
        {
            data.right = r;
        }

        Result(const Left<L> &l) : has_left(true)
        {
            data.left = l;
        }

        template <class LFn, class RFn>
        decltype(auto) match(LFn left_fn, RFn right_fn)
        {
            if (has_left)
            {
                return left_fn(data.left.value);
            }
            else
            {
                return right_fn(data.right.value);
            }
        }

    private:
        union
        {
            Left<L> left;
            Right<R> right;
        } data;

        bool has_left;
    };
}
