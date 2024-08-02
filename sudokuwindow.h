#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "sudokugenerator.h"
#include "sudokusolver.h"
#include <memory>

class SudokuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SudokuWindow(QWidget *parent = nullptr);
    QString getCellStyleSheet();
    void setCellStyleSheet(int row,int col, QString stl);
    ~SudokuWindow();

private:
    bool generated = false;
    QLineEdit* cells[9][9];
    //QString borderStyle;
    QString cellStyleSheet =  "background-color: white;"
                              "font : 50px;"
                              "color :blue;"
                              "border : 0; "
                              "border-left: 3px solid grey;"
                              "border-top: 3px solid grey;";

    std::unique_ptr<SudokuSolver> sudokuSolver;
    //std::unique_ptr<Sudoku>
    Sudoku* sudoku;               // Use smart pointers
    std::unique_ptr<SudokuGenerator> sudokuGenerator;
private slots:
    void onGenerateButtonClicked();
    void onSolutionButtonClicked();
    void onCellTextChanged();

};
#endif // SUDOKUWINDOW_H
