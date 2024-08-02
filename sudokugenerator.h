#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H
#include "sudoku.h"
#include <random>
#include <array>

class SudokuGenerator
{
public:
    SudokuGenerator();
    ~SudokuGenerator();
    Sudoku *generateSudoku();

private:
    Sudoku *sudoku;
    std::array<int, 9> validNumbers;
    bool generateFullSudoku();
    void emptyCells(int numCellsToEmpty);
    void shuffleList();
};

#endif // SUDOKUGENERATOR_H
