// Write a program to implement Min, Max, Sum and Average
// operations using OpenMP Parallel Reduction.

// # Reduction in OpenMP

// Reduction is an OpenMP operation used to:

// # safely combine results from multiple threads into a single final result.

// In parallel programming, multiple threads may try to update the same variable simultaneously, causing:

// # race condition

// Reduction solves this problem by:

// * creating private copy of variable for each thread
// * performing operation locally
// * combining all local results automatically at the end

// ---

// # Sum Reduction

// Syntax:

// #pragma omp parallel for reduction(+:sum)

// Meaning:

// * each thread calculates local sum
// * OpenMP adds all local sums together

// ---

// # Minimum Reduction

// Syntax:

// #pragma omp parallel for reduction(min:minimum)

// Meaning:

// * each thread finds local minimum
// * OpenMP finds final minimum value

// ---

// # Maximum Reduction

// Syntax:

// #pragma omp parallel for reduction(max:maximum)

// Meaning:

// * each thread finds local maximum
// * OpenMP finds final maximum value

// ---

// # Average

// Average is calculated using:

// Average = Sum / Number of Elements

// Parallel reduction is used only for calculating sum safely.

// ---

// # Race Condition

// Race condition occurs when multiple threads modify the same variable simultaneously causing incorrect results.

// Reduction prevents race conditions automatically.


#include <iostream>
#include <vector>
#include <omp.h>      // OpenMP library

using namespace std;

int main()
{
    // Input array
    vector<int> arr = {10, 20, 5, 40, 15, 25, 30};

    int n = arr.size();

    // Variables for operations
    int sum = 0;

    // Initialize min and max with first element
    int minimum = arr[0];
    int maximum = arr[0];

    // =====================================================
    // PARALLEL SUM
    // reduction(+:sum)
    //
    // Each thread calculates local sum
    // OpenMP combines all local sums automatically
    // =====================================================

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // =====================================================
    // PARALLEL MINIMUM
    // reduction(min:minimum)
    //
    // Each thread finds local minimum
    // OpenMP combines final minimum automatically
    // =====================================================

    #pragma omp parallel for reduction(min:minimum)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < minimum)
        {
            minimum = arr[i];
        }
    }

    // =====================================================
    // PARALLEL MAXIMUM
    // reduction(max:maximum)
    //
    // Each thread finds local maximum
    // OpenMP combines final maximum automatically
    // =====================================================

    #pragma omp parallel for reduction(max:maximum)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > maximum)
        {
            maximum = arr[i];
        }
    }

    // Average formula
    double average = (double)sum / n;

    // Display results
    cout << "Sum = " << sum << endl;

    cout << "Average = " << average << endl;

    cout << "Minimum = " << minimum << endl;

    cout << "Maximum = " << maximum << endl;

    return 0;
}