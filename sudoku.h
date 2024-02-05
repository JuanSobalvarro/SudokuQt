#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class sudoku;
}
QT_END_NAMESPACE

class sudoku : public QMainWindow
{
    Q_OBJECT

public:
    sudoku(QWidget *parent = nullptr);
    ~sudoku();

private:
    Ui::sudoku *ui;
};
#endif // SUDOKU_H
