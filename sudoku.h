#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QAbstractbutton>
#include <QFrame>
#include <QPalette>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class sudoku : public QMainWindow
{
    Q_OBJECT
public:
    sudoku(QWidget *parent = nullptr);
private:
    void SetUpSudokuGrid(QGridLayout *grid);
    void SetUpDownGrid(QGridLayout *grid);
    void SetUpRightGrid(QGridLayout *grid);
    void sudokuSeparators(QGridLayout *grid);
    void addLayoutToMainGrid(QGridLayout *gridLayout, int row, int col, int rowspan, int colspan);
    void cleanButtons();
    void setButtons();

    /*
     * Sudoku functions uwunya
    */
    unsigned int generateSeed();
    bool checkValInMat(int val, int matrow, int matcol);
    bool checkValInRow(int val, int row);
    bool checkValInCol(int val, int col);
    void printSudoku();
    bool isSudokuValid();
    bool hasEmptyCell();
    bool isCellValid(int val, int row, int col);
    bool fillValues();
    void removeElements(int difficulty);

    void run();
    void selectCell(QPushButton *b, int row, int col);
    void deSelectCell(QPushButton *b, int row, int col);
    void inputNumber(QPushButton *b, int row, int col);

    QGridLayout *mainGrid;
    std::vector<std::vector<QPushButton*>> buttons;
    std::vector<std::vector<int>> sudokuValues;
    unsigned int seed;
    bool isButtonSelected;
    QPushButton *prevButton;
    int prevButtonCoord[2];
    bool isRunning;
    std::vector<QPushButton*> validButtons;
    std::vector<QPushButton*> goodButtons;
    QLabel *winningLabel;

public slots:
    void generateSudoku();
protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // SUDOKU_H
