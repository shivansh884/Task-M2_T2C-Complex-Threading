// Sequential QuickSort Implementation
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate random data
void generateRandomData(vector<int>& data, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 10000;
    }
}

// Sequential QuickSort
void quickSort(vector<int>& arr, int low, int high) {
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
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    const int SIZE = 1000000;
    vector<int> data(SIZE);
    generateRandomData(data, SIZE);

    // Sequential execution
    auto start = high_resolution_clock::now();
    quickSort(data, 0, SIZE - 1);
    auto end = high_resolution_clock::now();
    auto duration_seq = duration_cast<milliseconds>(end - start);
    cout << "Sequential QuickSort Time: " << duration_seq.count() << " ms" << endl;

    return 0;
}
