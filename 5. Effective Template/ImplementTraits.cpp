/*
* File: ImplementTraits.cpp
* Author: trung.la
* Date: 03-26-2025
* Description: Templates in C++ allow us to create classes and functions that can work with different types.
*/

template <typename T>
struct AccumulationTraits;

template <>
struct AccumulationTraits<char> {
    using AccT = int;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<short> {
    using AccT = int;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<int> {
    using AccT = long;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<unsigned int> {
    using AccT = unsigned long;
    static AccT const zero = 0;
};

template <>
struct AccumulationTraits<float> {
    using AccT = double;
    static AccT const zero = 0;
};

template <typename T>
auto accum(T const* beg, T const* end)
{
    using AccT = typename AccumulationTraits<T>::AccT;
    AccT total = AccumulationTraits<T>::zero;

    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}