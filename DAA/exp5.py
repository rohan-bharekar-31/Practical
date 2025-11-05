def print_solution(board):
    """Prints the N×N chessboard."""
    for row in board:
        print(" ".join("Q" if x == 1 else "." for x in row))
    print()


def is_safe(board, row, col, n):
    """Checks if a queen can be safely placed at (row, col)."""
    for r in range(n):
        for c in range(n):
            if board[r][c] == 1:
                # Check column or diagonal conflict
                if c == col or abs(r - row) == abs(c - col):
                    return False
    return True


def solve_n_queens_with_fixed(board, row, n, fixed_row):
    """Backtracking function that skips the row of the fixed queen."""
    if row == n:
        print_solution(board)
        return True

    # Skip the fixed queen’s row
    if row == fixed_row:
        return solve_n_queens_with_fixed(board, row + 1, n, fixed_row)

    found_solution = False
    for col in range(n):
        if is_safe(board, row, col, n):
            board[row][col] = 1
            found_solution = solve_n_queens_with_fixed(board, row + 1, n, fixed_row) or found_solution
            board[row][col] = 0  # Backtrack

    return found_solution


if __name__ == "__main__":
    # Take user input
    n = int(input("Enter the size of the board (N): "))
    fixed_row = int(input("Enter row position for the first queen (0-indexed): "))
    fixed_col = int(input("Enter column position for the first queen (0-indexed): "))

    # Initialize the board
    board = [[0 for _ in range(n)] for _ in range(n)]
    board[fixed_row][fixed_col] = 1  # Place the first queen

    print(f"\nFirst queen placed at row {fixed_row}, column {fixed_col}\n")
    print("Possible Solutions:\n")

    # Solve starting from row 0, skipping the fixed queen’s row
    if not solve_n_queens_with_fixed(board, 0, n, fixed_row):
        print("No solutions exist for this configuration.")
