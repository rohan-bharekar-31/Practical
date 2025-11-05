# Fractional Knapsack using Greedy Method

# Define a structure for each item
class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight

# Greedy function to get maximum value
def fractional_knapsack(items, capacity):
    # Step 1: Calculate value-to-weight ratio
    for item in items:
        item.ratio = item.value / item.weight

    # Step 2: Sort items by ratio in descending order
    items.sort(key=lambda x: x.ratio, reverse=True)

    total_value = 0.0  # Total profit
    remaining_capacity = capacity

    # Step 3: Pick items one by one
    for item in items:
        if remaining_capacity >= item.weight:
            # take the whole item
            total_value += item.value
            remaining_capacity -= item.weight
            print(f"Took all of item (value={item.value}, weight={item.weight})")
        else:
            # take fractional part
            fraction = remaining_capacity / item.weight
            total_value += item.value * fraction
            print(f"Took {fraction*100:.2f}% of item (value={item.value}, weight={item.weight})")
            remaining_capacity = 0
            break  # knapsack full

    return total_value


# ------------------ Main Section ------------------
if __name__ == "__main__":
    n = int(input("Enter number of items: "))
    items = []

    for i in range(n):
        val = float(input(f"Enter value of item {i+1}: "))
        wt = float(input(f"Enter weight of item {i+1}: "))
        items.append(Item(val, wt))

    capacity = float(input("Enter knapsack capacity: "))

    max_value = fractional_knapsack(items, capacity)
    print(f"\nMaximum value in Knapsack = {max_value:.2f}")
