#ifndef SUDOKU_H
#define SUDOKU_H
#include <array>

constexpr int row_size = 9;
constexpr int column_size = 9;

class Sudoku
{
public:
    Sudoku();
    Sudoku(const std::array<std::array<int, 9>, 9> &matrix);
    int getValue(int row, int column);
    void setValue(int row, int column, int value);
    bool isValuePossible(int row, int column, int value);
    void resetSudoku();
#ifdef NATIVE
    void printSudoku();
#endif

private:
    std::array<std::array<int, column_size>, row_size> matrix;
};

#endif // SUDOKU_H
