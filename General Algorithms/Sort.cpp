// Robin Kalia
// robinkalia@berkeley.edu

// Problem: Implement Different Sorting Algorithms
// 1) QuickSort
// 2) MergeSort 

#include <iostream>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <initializer_list>

template<typename T>
void qSort(std::vector<T>& arr, int32_t first, int32_t last) {
    if (first >= last)  return;
    T bound = arr[(first+last)/2];
    std::swap(arr[first],arr[(first+last)/2]);
    int32_t lower = first+1;
    int32_t upper = last;
    while (lower<upper) {
        while (arr[lower] < bound)
            ++lower;
        while (bound < arr[upper])
            --upper;
        if (lower < upper)
            std::swap(arr[lower++], arr[upper--]);
        else
            ++lower;
    }

    std::swap(arr[first], arr[upper]);
    qSort(arr, first, upper-1);
    qSort(arr, upper+1, last);
}

template<typename T>
void Quicksort(std::vector<T>& arr) {
    if (arr.size() < 2)
        return;
    auto maxElemIt = std::max_element(arr.begin(), arr.end());
    int32_t maxElemPos = std::distance(arr.begin(), maxElemIt);
    std::swap(arr[maxElemPos], arr[arr.size()-1]);

    qSort(arr,0,arr.size()-2);
}

template<typename T>
void MergeSort(std::vector<T> &data, int32_t first, int32_t last) {
    if ((data.size() < 2) || (first >= last))   return;
    int32_t midPos = (first+last)/2;
    if (first<last) {
        MergeSort(data, first, midPos);
        MergeSort(data, midPos+1, last);
        merge(data, first, last);
    }
}

template<typename T>
void merge(std::vector<T>& data, int32_t first, int32_t last) {
    int32_t midPos = (first+last)/2;
    int32_t indexPos = midPos;
    std::vector<T> temp(last-first+1);
    while ((first<midPos) && (indexPos<last)) {
        while (data[first]<data[indexPos+1])
            temp.push_back(data[first++]);
        while (data[first] > data[indexPos+1]) {
            temp.push_back(data[indexPos+1]);
            ++midPos;
        }
    }

    if (first < midPos)     temp.insert(temp.end(), data.begin()+first,  data.begin()+midPos);
    if (indexPos < last)    temp.insert(temp.end(), data.begin()+indexPos, data.begin()+last); 
}

void testMergeSort() {
    std::vector<int32_t> inputArr {3, 5, 2, 6, 1 };
    std::vector<int32_t> expectedOutputArr { 1, 2, 3, 5, 6 };

    MergeSort<int32_t>(inputArr, 0, inputArr.size());
    assert(inputArr == expectedOutputArr);
}

void testQuickSort() {
    std::vector<int32_t> inputArr { 3, 5, 2, 6, 1 };
    std::vector<int32_t> expectedOutputArr { 1, 2, 3, 5, 6 };

    Quicksort<int32_t>(inputArr);
    assert(std::equal(inputArr.begin(), inputArr.end(), expectedOutputArr.begin()));
}

int32_t main(int32_t argc, char* argv[]) {
    
    testQuickSort();
    testMergeSort();

    return 0;
}

