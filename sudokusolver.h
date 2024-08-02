#include "sudoku.h"
#include <utility>

class SudokuSolver
{
public:
    SudokuSolver(Sudoku *sudoku);
    bool solve();

private:
    Sudoku *sudoku;
    std::pair<int, int> findEmptyCells();
};
