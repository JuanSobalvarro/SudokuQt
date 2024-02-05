#include "sudoku.h"
#include "ui_sudoku.h"

sudoku::sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sudoku)
{
    ui->setupUi(this);
}

sudoku::~sudoku()
{
    delete ui;
}
