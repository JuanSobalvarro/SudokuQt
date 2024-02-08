#include "sudoku.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sudoku w;
    w.setWindowTitle("SUDOKU powered by Qt5.15");
    w.show();
    return a.exec();
}
