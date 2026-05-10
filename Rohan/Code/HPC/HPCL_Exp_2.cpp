// Write a program to implement Parallel Bubble Sort and Merge Sort using OpenMP.
// Measure performance of sequential and parallel algorithms.

// ------------------------------------------------------------------
// Algorithm                  | Time Complexity | Space Complexity
// ------------------------------------------------------------------
// Sequential Bubble Sort     | O(n^2)          | O(1)
// Parallel Bubble Sort       | O(n^2)          | O(1)
// Sequential Merge Sort      | O(n log n)      | O(n)
// Parallel Merge Sort        | O((n log n)/p)  | O(n)
//
// p = number of threads/processors
// ------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <omp.h>      // OpenMP library for parallel programming

using namespace std;

// ================= SEQUENTIAL BUBBLE SORT =================

// Normal bubble sort using single thread
void sequentialBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    // Number of passes
    for(int i = 0; i < n-1; i++)
    {
        // Compare adjacent elements
        for(int j = 0; j < n-i-1; j++)
        {
            // Swap if elements are in wrong order
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// ================= PARALLEL BUBBLE SORT =================

// Parallel Bubble Sort using Odd-Even Transposition Method
void parallelBubbleSort(vector<int>& arr)
{
    int n = arr.size();

    // Repeat passes
    for(int i = 0; i < n; i++)
    {
        // ---------------- EVEN PHASE ----------------
        // Compare:
        // (0,1), (2,3), (4,5) ...

        // Loop iterations divided among multiple threads
        #pragma omp parallel for
        for(int j = 0; j < n-1; j += 2)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
            }
        }

        // ---------------- ODD PHASE ----------------
        // Compare:
        // (1,2), (3,4), (5,6) ...

        // Again divide work among threads
        #pragma omp parallel for
        for(int j = 1; j < n-1; j += 2)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// ================= MERGE FUNCTION =================

// Merges two sorted halves into one sorted array
void merge(vector<int>& arr, int left, int mid, int right)
{
    // Temporary array used for merging
    vector<int> temp;

    // Left half pointer
    int i = left;

    // Right half pointer
    int j = mid + 1;

    // Compare elements from both halves
    while(i <= mid && j <= right)
    {
        // Insert smaller element into temp
        if(arr[i] < arr[j])
        {
            temp.push_back(arr[i]);
            i++;
        }
        else
        {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Copy remaining left half elements
    while(i <= mid)
    {
        temp.push_back(arr[i]);
        i++;
    }

    // Copy remaining right half elements
    while(j <= right)
    {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy merged data back into original array
    for(int k = 0; k < temp.size(); k++)
    {
        arr[left + k] = temp[k];
    }
}

// ================= SEQUENTIAL MERGE SORT =================

// Recursive Merge Sort using single thread
void sequentialMergeSort(vector<int>& arr, int left, int right)
{
    // Continue dividing until single element remains
    if(left < right)
    {
        // Find middle index
        int mid = (left + right) / 2;

        // Sort left half
        sequentialMergeSort(arr, left, mid);

        // Sort right half
        sequentialMergeSort(arr, mid + 1, right);

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

// ================= PARALLEL MERGE SORT =================

// Parallel Merge Sort using OpenMP sections
void parallelMergeSort(vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        // Execute different sections simultaneously
        #pragma omp parallel sections
        {
            // One thread sorts left half
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            // Another thread sorts right half
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        // Merge both sorted halves
        merge(arr, left, mid, right);
    }
}

// ================= MAIN FUNCTION =================

int main()
{
    // Large array size used to observe time difference
    const int SIZE = 50000;

    vector<int> arr(SIZE);

    // Initialize reverse sorted array
    // Worst case input for sorting
    for(int i = 0; i < SIZE; i++)
    {
        arr[i] = SIZE - i;
    }

    // Temporary array used before each test
    vector<int> temp;

    // =========================================================
    //                BUBBLE SORT PERFORMANCE
    // =========================================================

    // Copy original array
    temp = arr;

    // Store starting time
    double start = omp_get_wtime();

    // Run sequential bubble sort
    sequentialBubbleSort(temp);

    // Store ending time
    double end = omp_get_wtime();

    // Display execution time
    cout << "Sequential Bubble Sort Time: "
         << end - start << " seconds" << endl;

    // Reset array
    temp = arr;

    // Start timer
    start = omp_get_wtime();

    // Run parallel bubble sort
    parallelBubbleSort(temp);

    // End timer
    end = omp_get_wtime();

    // Display execution time
    cout << "Parallel Bubble Sort Time: "
         << end - start << " seconds" << endl;

    // =========================================================
    //                MERGE SORT PERFORMANCE
    // =========================================================

    // Reset array
    temp = arr;

    // Start timer
    start = omp_get_wtime();

    // Run sequential merge sort
    sequentialMergeSort(temp, 0, temp.size() - 1);

    // End timer
    end = omp_get_wtime();

    // Display execution time
    cout << "Sequential Merge Sort Time: "
         << end - start << " seconds" << endl;

    // Reset array
    temp = arr;

    // Start timer
    start = omp_get_wtime();

    // Run parallel merge sort
    parallelMergeSort(temp, 0, temp.size() - 1);

    // End timer
    end = omp_get_wtime();

    // Display execution time
    cout << "Parallel Merge Sort Time: "
         << end - start << " seconds" << endl;

    return 0;
}