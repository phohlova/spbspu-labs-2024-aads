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

template < typename T >
void printSequence(T& container) {
    for (auto& elem : container) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

template< typename Container, typename Func >
void oddEvenSort(Container& list, Func func) {

    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;
        auto odd = list.begin();
        auto even = std::next(odd);
        auto end = list.begin();
        size_t size = std::distance(list.begin(), list.end());
        std::advance(end, size - 1);

        // Сортировка нечетных индексов
        for (auto i = even; i != end;) {
            auto next = std::next(i);
            if (func(*i, *next)) {
                std::swap(*i, *next);
                isSorted = false;
            }
            i++;
            i++;
        }

        end = list.begin();
        std::advance(end, size);
        // Сортировка четных индексов
        for (auto i = odd; i != end; ) {
            auto next = std::next(i);
            if (func(*i, *next)) {
                std::swap(*i, *next);
                isSorted = false;
            }
            i++;
            i++;
        }
    }
}

template< typename Container, typename Func >
void oddEvenSortList(Container& list, Func func) {
    std::list<int> even, odd;

    // Separate even and odd elements
    for (int num : list) {
        if (num % 2 == 0) {
            even.push_back(num);
        }
        else {
            odd.push_back(num);
        }
    }

    // Sort both lists
    odd.sort(func);
    even.sort(func);

    // Merge back into the original list
    list.clear();
    list.splice(list.end(), even);
    list.splice(list.end(), odd);
}

template <typename Container, typename Func>
void selectionSort(Container& cont, Func function) {
    int n = cont.size();

    // Проходим по массиву от начала до предпоследнего элемента
    for (int i = 0; i < n - 1; i++) {
        // Находим индекс минимального элемента в неотсортированной части массива
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (function(cont[j], cont[minIndex])) {
                minIndex = j;
            }
        }

        // Меняем местами текущий элемент с минимальным элементом
        std::swap(cont[minIndex], cont[i]);
    }
}


template<typename Container, typename T>
void fill_container_random(Container& cont, T min_value, T max_value, size_t size) {
    // Проверка, что тип T - арифметический (int, float, double и т.д.)
    static_assert(std::is_arithmetic<T>::value, "Тип T должен быть арифметическим");
    \
        // Создаем генератор случайных чисел
        std::random_device rd; // Используем std::random_device для получения seed
    std::mt19937 gen(rd()); // Инициализируем Mersenne Twister engine

    // Определяем распределение в зависимости от типа T
    if constexpr (std::is_integral<T>::value) {
        // Для целых чисел используем std::uniform_int_distribution
        std::uniform_int_distribution<T> dist(min_value, max_value);
        for (int i = 0; i < size; ++i) {
            cont.push_back(dist(gen));
        }
    }
    else {
        // Для чисел с плавающей точкой используем std::uniform_real_distribution
        std::uniform_real_distribution<T> dist(min_value, max_value);
        for (int i = 0; i < size; ++i) {
            cont.push_back(dist(gen));
        }
    }
}

template<typename T>
void Worker(std::string& cmd, size_t size) {
    std::deque<T> deq;
    fill_container_random(deq, std::numeric_limits<T> ::min(), std::numeric_limits<T> ::max(), size);
    std::forward_list<T> forwardList(deq.begin(), deq.end());
    std::list<T> list(deq.begin(), deq.end());

    printSequence(deq);

    std::function<bool(T, T)> func;

    if (cmd == "ascending")
    {
        func = std::less<T>();
    }
    else if (cmd == "descending")
    {
        func = std::greater<T>();
    }

    selectionSort<std::deque<T>, std::function<bool(T, T)>>(deq, func);
    oddEvenSort(forwardList, func);
    oddEvenSort(list, func);
    printSequence(deq);
    printSequence(forwardList);
    printSequence(list);
}

#endif
