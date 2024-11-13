#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0;
    int k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Added missing loop for remaining elements in R
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

std::vector<int> mergeSortWrapper(std::vector<int> arr) {
    if (!arr.empty()) {
        mergeSort(arr, 0, arr.size() - 1);
    }
    return arr;
}

PYBIND11_MODULE(mergesort, m) {  // Changed from mymodule to mergesort
    m.doc() = "Merge sort implementation in C++";
    m.def("sort", &mergeSortWrapper, "Merge sort algorithm");  // Changed function name to be more intuitive
}