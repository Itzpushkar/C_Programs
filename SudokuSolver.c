#include <stdio.h>

int puzzle[9][9];

int default_puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);
int is_valid_input(int puzzle[9][9]);
void input_puzzle(int puzzle[9][9]);

int main()
{
    int a = 0;
    printf("\n\tWelcome to SUDOKU Solver !!!\n");

    // Ask the user to input the puzzle if he wants otherwise display the default puzzle and its solution

    printf("If you want to enter the puzzle which I should solve then enter 1 otherwise 0:");
    scanf("%d", &a);

    if (a == 1)
    {
        input_puzzle(puzzle);

        // Check if the puzzle is valid
        if (!is_valid_input(puzzle))
        {
            printf("\nThe puzzle is not valid. It has violations in Sudoku rules.\n");
            return 0;
        }

        printf("\nOriginal Puzzle:\n");
        print_puzzle(puzzle);

        if (solve_puzzle(puzzle, 0, 0))
        {
            printf("\nThe puzzle is solved:\n");
            print_puzzle(puzzle);
        }
        else
        {
            printf("\nThis puzzle is not solvable.\n");
        }
    }
    else if (a == 0)
    {
        printf("\n\nOriginal Puzzle:");
        print_puzzle(default_puzzle);
        if (solve_puzzle(default_puzzle, 0, 0))
        {
            printf("\n The puzzle is solved: ");
            print_puzzle(default_puzzle);
        }
        else
        {
            printf("\n This puzzle is not Solvable\n");
        }
    }

    return 0;
}

void input_puzzle(int puzzle[9][9])
{
    printf("\nPlease enter the Sudoku puzzle (enter 0 for empty cells):\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("Enter value for cell (%d, %d): ", i + 1, j + 1);
            scanf("%d", &puzzle[i][j]);
            if (puzzle[i][j] < 0 || puzzle[i][j] > 9)
            {
                printf("Invalid input! Enter a number between 0 and 9.\n");
                j--; // Redo the same cell
            }
        }
    }
}

int is_valid_input(int puzzle[9][9])
{
    // Check rows for duplicates
    for (int row = 0; row < 9; row++)
    {
        int seen[10] = {0}; // Array to track seen numbers in the row
        for (int col = 0; col < 9; col++)
        {
            if (puzzle[row][col] != 0)
            {
                if (seen[puzzle[row][col]])
                {
                    return 0; // Duplicate found in row
                }
                seen[puzzle[row][col]] = 1;
            }
        }
    }

    // Check columns for duplicates
    for (int col = 0; col < 9; col++)
    {
        int seen[10] = {0}; // Array to track seen numbers in the column
        for (int row = 0; row < 9; row++)
        {
            if (puzzle[row][col] != 0)
            {
                if (seen[puzzle[row][col]])
                {
                    return 0; // Duplicate found in column
                }
                seen[puzzle[row][col]] = 1;
            }
        }
    }

    // Check 3x3 subgrids for duplicates
    for (int box_row = 0; box_row < 9; box_row += 3)
    {
        for (int box_col = 0; box_col < 9; box_col += 3)
        {
            int seen[10] = {0}; // Array to track seen numbers in the 3x3 subgrid
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int r = box_row + i;
                    int c = box_col + j;
                    if (puzzle[r][c] != 0)
                    {
                        if (seen[puzzle[r][c]])
                        {
                            return 0; // Duplicate found in 3x3 subgrid
                        }
                        seen[puzzle[r][c]] = 1;
                    }
                }
            }
        }
    }

    return 1; // No violations found
}

int solve_puzzle(int puzzle[9][9], int row, int col)
{
    if (col == 9)
    {
        if (row == 8)
        {
            return 1; // Puzzle solved
        }
        row++;
        col = 0;
    }

    if (puzzle[row][col] > 0)
    {
        return solve_puzzle(puzzle, row, col + 1);
    }

    for (int i = 1; i <= 9; i++)
    {
        if (valid_move(puzzle, row, col, i))
        {
            puzzle[row][col] = i;
            if (solve_puzzle(puzzle, row, col + 1))
            {
                return 1;
            }
            puzzle[row][col] = 0;
        }
    }
    return 0;
}

int valid_move(int puzzle[9][9], int row, int col, int val)
{
    // Valid row
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == val)
        {
            return 0;
        }
    }

    // Valid column
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[i][col] == val)
        {
            return 0;
        }
    }

    // Valid square
    int r = row - row % 3;
    int c = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[r + i][c + j] == val)
            {
                return 0;
            }
        }
    }

    return 1;
}

void print_puzzle(int puzzle[9][9])
{
    printf("\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("\n|-------+-------+-------|");
        }
        printf("\n");
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("| ");
            }
            if (puzzle[row][col] != 0)
            {
                printf("%d ", puzzle[row][col]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}
