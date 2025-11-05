# Assignment: Fibonacci Numbers using Recursive and Non-Recursive Approach
# Aim: Write a program (non-recursive and recursive) to calculate Fibonacci numbers
#      and analyze their time and space complexity.

import time

# ---------------------------------------------------
# Non-Recursive (Iterative) Fibonacci Series
# ---------------------------------------------------
def fibonacci_iterative(n):
    if n < 0:
        print("Invalid input! Enter a non-negative integer.")
        return []
    elif n == 0:
        return [0]
    elif n == 1:
        return [0, 1]

    series = [0, 1]  # first two terms
    for i in range(2, n + 1):
        series.append(series[i - 1] + series[i - 2])
    return series


# ---------------------------------------------------
# Recursive Fibonacci Function (to find one number)
# ---------------------------------------------------
def fibonacci_recursive(n):
    if n < 0:
        return -1
    elif n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)


# ---------------------------------------------------
# Generate Full Fibonacci Series Recursively
# ---------------------------------------------------
def fibonacci_recursive_series(n):
    series = []
    for i in range(n + 1):
        series.append(fibonacci_recursive(i))
    return series


# ---------------------------------------------------
# Main Program
# ---------------------------------------------------
if __name__ == "__main__":
    n = int(input("Enter how many terms you want in Fibonacci series: "))

    # ------------------ Iterative ------------------
    start_time = time.time()
    iter_series = fibonacci_iterative(n)
    end_time = time.time()
    iter_time = end_time - start_time

    # ------------------ Recursive ------------------
    start_time = time.time()
    recur_series = fibonacci_recursive_series(n)
    end_time = time.time()
    recur_time = end_time - start_time

    # ------------------ Output ------------------
    print("\n==============================")
    print(" NON-RECURSIVE (ITERATIVE) APPROACH")
    print("==============================")
    print("Fibonacci Series:", iter_series)
    print(f"Fibonacci({n}) = {iter_series[-1] if iter_series else 'N/A'}")
    print(f"Execution Time : {iter_time:.8f} seconds")
    print("Time Complexity : O(n)")
    print("Space Complexity : O(1)")

    print("\n==============================")
    print(" RECURSIVE APPROACH")
    print("==============================")
    print("Fibonacci Series:", recur_series)
    print(f"Fibonacci({n}) = {recur_series[-1] if recur_series else 'N/A'}")
    print(f"Execution Time : {recur_time:.8f} seconds")
    print("Time Complexity : O(2^n)")
    print("Space Complexity : O(n)  (due to recursion stack)")
