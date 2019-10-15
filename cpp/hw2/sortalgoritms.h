//
// Created by Dima on 10.10.2019.
//

#ifndef HW2_SORTALGORITMS_H
#define HW2_SORTALGORITMS_H

//
// Created by Dima on 10.10.2019.
//

#include <algorithm>

/*
 * Шаблоны используются для упрощения тестирования
 * и разделения части с алгоритмами от части с данными
 */

template<typename RandomIt>
void bubble_sort(RandomIt left, RandomIt right){
    bool swapped = false;
    do{
        swapped = false;
        for(RandomIt cur = left; cur < right-1; cur++){
            if(*cur > *(cur+1)){
                std::iter_swap(cur, cur+1); // Меняем местами элементы, если текущий больше следующего
                swapped = true;
            }
        }
    }while(swapped);
}


template<typename RandomIt>
void heapify(RandomIt begin, long len, long i)
{
    long largest = i;
    long left = 2 * i + 1; // Левый ребенок
    long right = 2 * i + 2; // Правый ребенок

    if (left < len && *(begin + left) > *(begin+largest))
        largest = left;

    if (right < len && *(begin + right) > *(begin+largest))
        largest = right;

    if (largest != i)
    {
        std::iter_swap(begin + i, begin + largest); // Перемещаем наибольший элемент в корень поддерева
        heapify(begin, len, largest); // Переделываем поддерево с бывшим наибольшим
    }
}

template<typename RandomIt>
void heap_sort(RandomIt left, RandomIt right)
{
    long len = std::distance(left, right);
    for (long i = len / 2 - 1; i >= 0; i--)
        heapify(left, len, i); // Делаем дерево

    for (long i = len - 1; i >= 0; i--)
    {
        std::iter_swap(left, left+i); // Перемещаем наименьший лемент в начало
        heapify(left, i, 0); // Переделываем дерево
    }
}
//#include "sortalgoritms.cpp"

#endif //HW2_SORTALGORITMS_H
