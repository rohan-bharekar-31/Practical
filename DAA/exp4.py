# 0-1 Knapsack Problem using Dynamic Programming (with item selection)

def knapsack_01(weights, values, capacity, n):
    # Create DP table
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]

    # Build the table bottom-up
    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]],
                               dp[i - 1][w])
            else:
                dp[i][w] = dp[i - 1][w]

    # Reconstruct selected items
    selected_items = []
    w = capacity
    for i in range(n, 0, -1):
        if dp[i][w] != dp[i - 1][w]:
            selected_items.append(i)  # item index (1-based)
            w -= weights[i - 1]

    selected_items.reverse()  # optional, to maintain order
    return dp[n][capacity], selected_items


# ---------------------- MAIN SECTION ----------------------
n = int(input("Enter number of items: "))
weights = []
values = []

for i in range(n):
    w = int(input(f"Enter weight of item {i+1}: "))
    v = int(input(f"Enter value of item {i+1}: "))
    weights.append(w)
    values.append(v)

capacity = int(input("Enter capacity of knapsack: "))

# Solve
max_value, selected = knapsack_01(weights, values, capacity, n)

# Display Results
print("\n===============================")
print(" 0-1 KNAPSACK RESULTS ")
print("===============================")
print(f"Maximum value obtained: {max_value}")
print(f"Items selected (1-based indices): {selected}")

print("\nDetails of selected items:")
total_weight = 0
for i in selected:
    print(f"Item {i} -> Weight: {weights[i-1]}, Value: {values[i-1]}")
    total_weight += weights[i-1]
print(f"\nTotal Weight Used: {total_weight} / {capacity}")
