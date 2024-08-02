#include "sudokusolver.h"

SudokuSolver::SudokuSolver(Sudoku *sudoku)
{
    if (sudoku == nullptr)
        sudoku = new Sudoku();

    this->sudoku = sudoku;
}

std::pair<int, int> SudokuSolver::findEmptyCells()
{
    for (int row = 0; row < row_size; row++)
    {
        for (int col = 0; col < column_size; col++)
        {
            if (sudoku->getValue(row, col) == 0)
                return std::make_pair(row, col);
        }
    }

    return std::make_pair(-1, -1);
}

bool SudokuSolver::solve()
{
    std::pair<int, int> empty = findEmptyCells();
    // means no empty cells left, sudoku is complete (might check if the sudoku is valid to make sure)
    if (empty.first == -1 && empty.second == -1)
        return true;

    // we found an empty cell
    int row = empty.first;
    int col = empty.second;
    // we check for every valid value, is value possible on that empty cell
    for (int possibleVal = 1; possibleVal < 10; possibleVal++)
    {
        if (sudoku->isValuePossible(row, col, possibleVal))
        {
            sudoku->setValue(row, col, possibleVal);
            // call method recurseivly to check for next empty cell
            if (solve())
                return true;
            // if function return false, means that the value we sent on previous cell, was not good, set it to zero, and try with another value
            sudoku->setValue(row, col, 0);
        }
    }
    // we couldnt find a possible value for that empty slot
    return false;
}

// int main()
// {
//     std::array<std::array<int, 9>, 9> puzzle = {};
//     Sudoku *sudoku = new Sudoku(puzzle);
//     SudokuSolver sudokuSolver = SudokuSolver(sudoku);
//     sudokuSolver.solve();
//     delete sudoku;
// }
