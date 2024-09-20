#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>
#include <forward_list>
#include <deque>
#include <list>
#include <limits>

template< typename T >
void printSequence(T& container)
{
    for (auto& elem : container)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

template< typename Container, typename Func >
void oddEvenSort(Container& list, Func func)
{
    bool isSorted = false;
    while (!isSorted)
    {
        isSorted = true;

        for (auto it = std::begin(list); it != std::end(list); ++it)
        {
            auto nextIt = std::next(it);
            if (nextIt != std::end(list) && func(*nextIt, *it))
            {
                std::iter_swap(it, nextIt);
                isSorted = false;
            }
        }
        auto prevIt = std::begin(list);
        for (auto it = std::next(std::begin(list)); it != std::end(list); ++it)
        {
            if (func(*it, *prevIt))
            {
                std::iter_swap(prevIt, it);
                isSorted = false;
            }
            prevIt = std::next(it);
        }
    }
}

template< typename Container, typename Func >
void selectionSort(Container& cont, Func function)
{
    for (auto i = cont.begin(); i != cont.end(); ++i)
    {
        auto min = i;
        for (auto j = std::next(i); j != cont.end(); ++j)
        {
            if (function(*j, *min))
            {
                min = j;
            }
        }
        std::iter_swap(i, min);
    }
}

template< typename Container, typename T >
void fill_container_random(Container& cont, T min_value, T max_value, size_t size)
{
    static_assert(std::is_arithmetic< T >::value, "Тип T должен быть арифметическим");

    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral< T >::value)
    {
        std::uniform_int_distribution< T > dist(min_value, max_value);
        for (int i = 0; i < size; ++i)
        {
            cont.push_back(dist(gen));
        }
    }
    else
    {
        std::uniform_real_distribution< T > dist(min_value, max_value);
        for (int i = 0; i < size; ++i)
        {
            cont.push_back(dist(gen));
        }
    }
}

template< typename T >
void Worker(std::string& cmd, size_t size)
{
    std::deque< T > deq;
    fill_container_random(deq, std::numeric_limits< T > ::min(), std::numeric_limits< T > ::max(), size);
    std::forward_list< T > forwardList(deq.begin(), deq.end());
    std::list< T > list(deq.begin(), deq.end());

    printSequence(deq);

    std::function< bool (T, T) > func;

    if (cmd == "ascending")
    {
        func = std::less< T >();
    }
    else if (cmd == "descending")
    {
        func = std::greater< T >();
    }

    selectionSort< std::deque< T > >(deq, func);
    selectionSort< std::list< T > >(list, func);
    selectionSort< std::forward_list< T > >(forwardList, func);
    oddEvenSort(forwardList,func);
    oddEvenSort(list,func);
    printSequence(deq);
    printSequence(forwardList);
    printSequence(list);
}

#endif
