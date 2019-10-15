//
// Created by Dima on 10.10.2019.
//

#ifndef HW2_SORTALGORITMS_H
#define HW2_SORTALGORITMS_H

//
// Created by Dima on 10.10.2019.
//

#include <algorithm>
#include <iostream>

template<typename RandomIt>
void selection_sort(RandomIt left, RandomIt right){
    RandomIt min, cur;
    for(;left<right;left++) { // сдвигаем начало неотсортированного массива
        min = left;
        for (cur = left; cur < right; cur++) {
            if (*cur < *min) {
                min = cur; // Ищем и запоминаем максимальный элемент
            }
        }
        if (min != left) {
            std::iter_swap(min, left); // Помещаем его в начало неотсортированного массива
        }
    }
}

template<typename RandomIt>
void bubble_sort(RandomIt left, RandomIt right){
    bool swapped = false;
    do{
        swapped = false;
        for(RandomIt cur = left; cur < right-1; cur++){
            if(*cur > *(cur+1)){
                std::iter_swap(cur, cur+1);
                swapped = true;
            }
        }
    }while(swapped);
}

template<typename RandomIt>
void insertion_sort(RandomIt left, RandomIt right){
    RandomIt j;
    for(RandomIt t = left;t<right;t++){
        j = t;
        for(; (j > left)&&(*j < *(j-1));j--){
            std::iter_swap(j, j-1);
        }
    }
}

//template<class RandomIt>
//void heapsort(RandomIt left, RandomIt right){
//
//}


template<typename RandomIt>
void shaker_sort(RandomIt left, RandomIt right){
    bool swaped = false;
    while(left<right){
        for(RandomIt t = left; t < right-1; t++){
            if(*t > *(t+1)){
                std::iter_swap(t, t+1);
                swaped = true;
            }
        }
        right--;
        for(RandomIt t = right-1; t > left; t--){
            if(*(t-1) > *t){
                std::iter_swap(t-1, t);
                swaped = true;
            }
        }
        left++;
        if(!swaped){
            break;
        }
    }
}


template<typename RandomIt>
void heapify(RandomIt begin, long len, long i)
{
    long largest = i;
    long left = 2 * i + 1;
    long right = 2 * i + 2;

    if (left < len && *(begin + left) > *(begin+largest))
        largest = left;

    if (right < len && *(begin + right) > *(begin+largest))
        largest = right;

    if (largest != i)
    {
        std::iter_swap(begin + i, begin + largest);

        heapify(begin, len, largest);
    }
}

template<typename RandomIt>
void heap_sort(RandomIt left, RandomIt right)
{
    long len = std::distance(left, right);
    for (long i = len / 2 - 1; i >= 0; i--)
        heapify(left, len, i);

    for (long i = len - 1; i >= 0; i--)
    {
        std::iter_swap(left, left+i);
        heapify(left, i, 0);
    }
}
//#include "sortalgoritms.cpp"

#endif //HW2_SORTALGORITMS_H
