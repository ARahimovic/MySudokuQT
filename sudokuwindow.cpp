#include "sudokuwindow.h"
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QWidget>
#include <QString>
#include <QSpacerItem>
#include <QIntValidator>
#include <QRegularExpressionValidator>

SudokuWindow::SudokuWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    QGridLayout* gridLayout = new QGridLayout(centralWidget);
    QRegularExpression regex("[1-9]"); // Regex for digits 1 to 9
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, this);

    for(int row = 0; row < 9; row ++)
    {
        for(int column = 0; column < 9; column++)
        {
            QLineEdit* cell = new QLineEdit();
            cell->setFixedHeight(80);
            cell->setFixedWidth(80);
            cell->setAlignment(Qt::AlignCenter);
            cell->setMaxLength(1); // allow only one characthe
            //QIntValidator* validator = new QIntValidator(1,9, this);
            cell->setValidator(validator);
            //set the cell style sheet
            gridLayout->addWidget(cell, row, column);
            cells[row][column] = cell;
            setCellStyleSheet(row,column,"");
            //connect the qlineEdit signal to the slot
            connect(cell, &QLineEdit::textChanged, this, &SudokuWindow::onCellTextChanged);
        }
    }




    //create pushButtons
    QPushButton* generateButton = new QPushButton("Generate");
    QPushButton* solveButton = new QPushButton("Solve");
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(generateButton);
    vBoxLayout->addWidget(solveButton);

    gridLayout->addLayout(vBoxLayout, 0, 9, 9, 1); // layout to add, row, column, row span, column span

    QSpacerItem * verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer,9,0,1,7); // Add spacer after the last row

    gridLayout->setHorizontalSpacing(0); // Space between columns
    gridLayout->setVerticalSpacing(0);
    // gridLayout->setContentsMargins(0,0,0,0);

    centralWidget->setLayout(gridLayout);
    setWindowTitle("MySudoku");
    resize(1000,1000);

    connect(generateButton, &QPushButton::clicked, this, &SudokuWindow::onGenerateButtonClicked);
    connect(solveButton, &QPushButton::clicked, this, &SudokuWindow::onSolutionButtonClicked);
    //creat a slot where the user input in a cell,
    //make that cell readOnly

}

void SudokuWindow::onGenerateButtonClicked()
{
    sudokuGenerator = std::make_unique<SudokuGenerator>();
    // if(sudoku != nullptr)
    //     delete sudoku;

    sudoku = std::move(sudokuGenerator->generateSudoku());


    for(int i = 0; i < row_size; i++)
    {
        for(int j = 0; j < column_size; j++)
        {
            if(sudoku->getValue(i,j) == 0)
            {
                //if value is 0, empty cell
                cells[i][j]->setText(QString(""));
                //set it to write mode so user can input data
                cells[i][j]->setReadOnly(false);

            }
            else
            {
                //cell has already filled number
                cells[i][j]->setText(QString::number(sudoku->getValue(i,j)));
                //set it to readOnly
                cells[i][j]->setReadOnly(true);
            }

            setCellStyleSheet(i,j,"");

        }
    }

    generated = true;

}
void SudokuWindow::onSolutionButtonClicked()
{
    sudokuSolver = std::make_unique<SudokuSolver>(this->sudoku);
    sudokuSolver->solve();

    for(int i = 0; i < row_size; i++)
    {
        for(int j = 0; j < column_size; j++)
        {
            cells[i][j]->setText(QString::number(sudoku->getValue(i,j)));
        }
    }
}
void SudokuWindow::onCellTextChanged()
{
    if(generated)
    {
        //get the cell that sent the signal
        QLineEdit *senderCell = qobject_cast<QLineEdit*>(sender());
        if(senderCell && !senderCell->text().isEmpty())
        {
            for(int i =0; i<row_size ; i++)
            {
                for(int j=0; j<column_size; j++)
                {
                    if(cells[i][j] == senderCell)
                    {
                        int val = senderCell->text().toInt(nullptr);
                        if(sudoku->isValuePossible(i,j,val))
                        {
                            setCellStyleSheet(i,j,"color : green;");

                            sudoku->setValue(i,j,val);


                        }
                        else
                        {
                            setCellStyleSheet(i,j,"color : red;");

                        }
                        //we check if the value is possible
                        cells[i][j]->setReadOnly(true);
                        cells[i][j]->update();
                        cells[i][j]->repaint();

                    }
                }
            }

        }


    }

}

QString SudokuWindow::getCellStyleSheet(){ return cellStyleSheet; }
void SudokuWindow::setCellStyleSheet(int row, int col, QString stl)
{
    cellStyleSheet = "background-color: white;"
                     "font : 50px;"
                     "color :blue;"
                     "border : 0; "
                     "border-left: 3px solid grey;"
                     "border-top: 3px solid grey;";

    if (row % 3 == 0)
        cellStyleSheet += "border-top: 5px solid black;";
    if (col % 3 == 0)
        cellStyleSheet += "border-left: 5px solid black;";

    if(row == 8)
        cellStyleSheet += "border-bottom: 5px solid black;";
    if(col == 8)
        cellStyleSheet += "border-right: 5px solid black;";

    cells[row][col]->setStyleSheet(cellStyleSheet);

    if(stl.isEmpty())
        return;

    cellStyleSheet += stl;
    cells[row][col]->setStyleSheet(cellStyleSheet);


}

SudokuWindow::~SudokuWindow()
{
    // if(sudoku != nullptr)
    //     delete sudoku;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            delete cells[i][j];
        }
    }

}

