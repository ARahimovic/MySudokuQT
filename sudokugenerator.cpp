#include "sudokugenerator.h"
#include <algorithm>
#include <numeric>

SudokuGenerator::SudokuGenerator()
{
    sudoku = new Sudoku();
    std::iota(validNumbers.begin(), validNumbers.end(), 1);
}

SudokuGenerator::~SudokuGenerator()
{
    delete sudoku;
}


void SudokuGenerator::shuffleList()
{
    // create random devide to seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(validNumbers.begin(), validNumbers.end(), gen);
}

bool SudokuGenerator::generateFullSudoku()
{

    for (int row = 0; row < row_size; row++)
    {
        for (int column = 0; column < column_size; column++)
        {
            // we found empty cell
            if (sudoku->getValue(row, column) == 0)
            {
                // we shuffle the valid numbers that we can input, to get unique sudoku each time
                shuffleList();
                // get random value from 1 to 9
                for (auto val : validNumbers)
                {
                    // if the value is possible to be entered into the cell, assign it
                    if (sudoku->isValuePossible(row, column, val))
                    {
                        sudoku->setValue(row, column, val);
                        // we call the function recursevly
                        if (generateFullSudoku())
                            return true;
                        // backtracking
                        sudoku->setValue(row, column, 0);
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void SudokuGenerator::emptyCells(int numCellsToEmpty)
{
    int count = 0;
    if (numCellsToEmpty > 60)
        numCellsToEmpty = 60;

    // get random index
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, row_size - 1);

    while (count < numCellsToEmpty)
    {

        int row = dis(gen);
        int col = dis(gen);
        // if value is not already zero , set it to zero
        if (sudoku->getValue(row, col) != 0)
        {
            sudoku->setValue(row, col, 0);
            count++;
        }
    }
}

Sudoku *SudokuGenerator::generateSudoku()
{
    SudokuGenerator::generateFullSudoku();
    SudokuGenerator::emptyCells(5);
    return this->sudoku;
}
