// Parallel QuickSort Implementation
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Function to generate random data
void generateRandomData(vector<int>& data, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 10000;
    }
}

// Optimized Parallel QuickSort using OpenMP Tasks
void parallelQuickSort(vector<int>& arr, int low, int high, int depth) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        if (depth > 0 && (high - low) > 10000) {  // Only parallelize large partitions
            #pragma omp task
            parallelQuickSort(arr, low, pi - 1, depth - 1);
            #pragma omp task
            parallelQuickSort(arr, pi + 1, high, depth - 1);
        } else {
            parallelQuickSort(arr, low, pi - 1, 0);
            parallelQuickSort(arr, pi + 1, high, 0);
        }
    }
}

int main() {
    const int SIZE = 1000000;
    vector<int> data(SIZE);
    generateRandomData(data, SIZE);

    // Parallel execution
    auto start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        parallelQuickSort(data, 0, SIZE - 1, 4);  // Limit depth to avoid overhead
    }
    auto end = high_resolution_clock::now();
    auto duration_par = duration_cast<milliseconds>(end - start);
    cout << "Parallel QuickSort Time: " << duration_par.count() << " ms" << endl;

    return 0;
}
