#include "sudoku.h"
#include <iostream>

Sudoku::Sudoku():matrix{}
{

}

void Sudoku::resetSudoku()
{
    for(int i =0; i < 9; i++)
    {
        for(int j=0; j<9;j++)
        {
            this->setValue(i,j,0);
        }
    }
}

Sudoku::Sudoku(const std::array<std::array<int, 9>, 9> &matr) : matrix(matr)
{
}

int Sudoku::getValue(int row, int column)
{
    return this->matrix.at(row).at(column);
}

void Sudoku::setValue(int row, int column, int val)
{
    this->matrix.at(row).at(column) = val;
}

bool Sudoku::isValuePossible(int row, int column, int val)
{
    for (int i = 0; i < row_size; i++)
    {
        if (matrix[row][i] == val)
            return false;
        if (matrix[i][column] == val)
            return false;
    }

    int start_row = (row / 3) * 3;
    int start_col = (column / 3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[start_row + i][start_col + j] == val)
                return false;
        }
    }

    return true;
}

#ifdef NATIVE
void printSudoku()
{
    for (int row = 0; row < row_size; row++)
    {
        for (int col = 0; col < column_size; col++)
        {
            if (col % 3 == 2)
                std::cout << matrix[row][col] << " | ";
            else
                std::cout << matrix[row][col] << " ";

            std::cout << std::endl;
        }
        if (row % 3 == 2)
            std::cout << "------------------" << std::endl;
    }
}
#endif
