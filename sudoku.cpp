#include "sudoku.h"
//#include "ui_sudoku.h"

/*
 * Set up sudoku main window
*/
sudoku::sudoku(QWidget *parent)
    : QMainWindow(parent)
{
    sudoku::isRunning = false;
    // layouts to be used
    sudoku::mainGrid = new QGridLayout;
    QGridLayout *sudokuGrid = new QGridLayout;
    QGridLayout *downGrid = new QGridLayout;
    QGridLayout *rightGrid = new QGridLayout;

    // initialize buttons and set up sudoku grid
    SetUpSudokuGrid(sudokuGrid);
    addLayoutToMainGrid(sudokuGrid, 0, 0, 1, 1);

    SetUpDownGrid(downGrid);
    addLayoutToMainGrid(downGrid, 1, 0, 1, 1);

    SetUpRightGrid(rightGrid);
    addLayoutToMainGrid(rightGrid, 2, 0, 1, 1);

    // set up central widget of the mainwindow
    QWidget *w = new QWidget;
    w->setLayout(mainGrid);
    this->setCentralWidget(w);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    //this->setGeometry(0, 0, 720, 480);
}

/*
 * Set up sudoku grid and saves the buttons into sudoku::buttons(QPushButtons(9x9))
*/
void sudoku::SetUpSudokuGrid(QGridLayout *grid)
{
    const QSize buttonSize = QSize(50,50);
    std::vector<std::vector<QPushButton*>> tempButtons(9, std::vector<QPushButton*>(9, NULL));
    std::vector<std::vector<int>> tempVals(9, std::vector<int>(9, 0));
    sudoku::sudokuValues = tempVals;
    sudoku::isButtonSelected = false;
    sudoku::prevButton = NULL;

    //std::vector<std::vector<int>> buttonsValues = generateValues();

    // save buttons into a vector
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::stringstream stream;
            stream << i;
            stream << j;
            QString text = QString::fromStdString(stream.str());

            QPushButton *b = new QPushButton();

            b->setText(text);
            b->setText(" ");
            b->setFixedSize(buttonSize);

            b->setStyleSheet("background-color: #FFFFFF; border-radius: 7px; border: 1px solid grey; font: bold 16px");
            //b->setAutoFillBackground(true);

            connect(b, &QPushButton::clicked, this, [this, b, i, j]{selectCell(b, i, j);});

            grid->addWidget(b, i, j, 1, 1);
            tempButtons[i][j] = b;
        }
    }
    sudoku::buttons = tempButtons;
    grid->setContentsMargins(0,0,0,0);
    grid->setSpacing(0);
    sudokuSeparators(grid);

}

/*
 * Adds the separators to the sudoku grid
*/
void sudoku::sudokuSeparators(QGridLayout *grid)
{
    for (int i = 1; i <= 2; i++)
    {
        QFrame *HLine = new QFrame;
        HLine->setFrameShape(QFrame::HLine);
        HLine->setLineWidth(2);
        // why all the strange numbers? when we pass a rowspan of 2 it creates the line in between the rows so we need to get back one line(3i-1)
        grid->addWidget(HLine, 3*i-1, 0, 2, 9);

        QFrame *VLine = new QFrame;
        VLine->setFrameShape(QFrame::VLine);
        VLine->setLineWidth(2);
        grid->addWidget(VLine, 0, 3*i, 9, 1);
    }
}

/*
 * This function add a Layout to the sudoku::mainGrid, given a row, col, rowspan and colspan
*/
void sudoku::addLayoutToMainGrid(QGridLayout *gridLayout, int row, int col, int rowspan, int colspan)
{
    QWidget *w = new QWidget;
    w->setLayout(gridLayout);
    sudoku::mainGrid->addWidget(w, row, col, rowspan, colspan);
}

void sudoku::SetUpDownGrid(QGridLayout *grid)
{
    QPushButton *generateButton = new QPushButton;
    connect(generateButton, &QPushButton::clicked, this, [this]{generateSudoku();});
    grid->addWidget(generateButton);
    generateButton->setText("Generate Sudoku");
}

void sudoku::SetUpRightGrid(QGridLayout *grid)
{
    sudoku::winningLabel = new QLabel();
    sudoku::winningLabel->setText("You havent win yet");
    grid->addWidget(winningLabel);
}

unsigned int sudoku::generateSeed()
{
    sudoku::seed = std::chrono::system_clock::now().time_since_epoch().count();
    return seed;
}

/*
 * Returns true if the value is valid in the matrix
 */
bool sudoku::checkValInMat(int val, int matrow, int matcol)
{
    for (int i = matrow; i < matrow+3; i++)
    {
        for (int j = matcol; j < matcol+3; j++)
        {
            //std::cout << "checking in i: " << i << " j: " << j << std::endl;
            //std::cout << "Comparing sud " << sudokuValues[i][j] << " with val " << val << std::endl;
            if (sudoku::sudokuValues[i][j] == val)
            {
                return false;
            }
        }
    }
    return true;
}

bool sudoku::checkValInRow(int val, int row)
{
    for (int c = 0; c < 9; c++)
    {
        if (sudokuValues[row][c] == val)
        {
            return false;
        }
    }
    return true;
}

bool sudoku::checkValInCol(int val, int col)
{
    for (int r = 0; r < 9; r++)
    {
        if (sudokuValues[r][col] == val)
        {
            return false;
        }
    }
    return true;
}

void sudoku::printSudoku()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << sudoku::sudokuValues[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

QString intToQString(int num)
{
    std::stringstream stream;
    stream << num;
    QString text = QString::fromStdString(stream.str());
    return text;
}

void sudoku::cleanButtons()
{
    sudoku::prevButton = NULL;
    sudoku::validButtons = std::vector<QPushButton*> (9, NULL);
    sudoku::goodButtons = std::vector<QPushButton*> (9, NULL);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku::buttons[i][j]->setText(" ");
            sudoku::buttons[i][j]->setStyleSheet("background-color: #FFFFFF; border-radius: 7px; border: 1px solid grey; font: bold 16px");
        }
    }
}

void sudoku::setButtons()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int val = sudoku::sudokuValues[i][j];
            if (val != 0)
            {
                sudoku::buttons[i][j]->setText(intToQString(val));
            }
        }
    }
}

bool sudoku::isSudokuValid()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku::sudokuValues[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

bool sudoku::hasEmptyCell()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            QString qs = sudoku::buttons[i][j]->text();
            std::string str = qs.toStdString();
            if (str.compare(" ") == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool sudoku::isCellValid(int val, int row, int col)
{
    return checkValInMat(val, floor(row/3) * 3, floor(col/3) * 3) && checkValInRow(val, row) && checkValInCol(val, col);
}

bool sudoku::fillValues()
{
    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // Si la celda está vacía
            if (sudoku::sudokuValues[row][col] == 0)
            {
                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(numbers.begin(), numbers.end(), g);
                for (int num = 0; num < 9; ++num)
                {
                    if (isCellValid(numbers[num], row, col))
                    {
                        sudoku::sudokuValues[row][col] = numbers[num];

                        // Llamada recursiva
                        if (fillValues()) {
                            //std::cout << "Added value " << numbers[num] << "at " << row << col << std::endl;
                            return true; // Si se pudo completar el sudoku
                        }

                        // Si no se pudo completar, deshacer la elección
                        sudoku::sudokuValues[row][col] = 0;
                    }
                }

                return false; // No se puede completar con el número actual
            }
        }
    }

    return true; // El sudoku está completo
}


void sudoku::removeElements(int difficulty)
{
    srand(time(NULL));
    while (difficulty != 0)
    {
        int row = rand()%9;
        int col = rand()%9;
        QString qs = sudoku::buttons[row][col]->text();
        std::string str = qs.toStdString();
        //std::cout << str << std::endl;
        if (str.compare(" ") != 0)
        {
            sudoku::buttons[row][col]->setText(" ");
            sudoku::validButtons.push_back(sudoku::buttons[row][col]);
            difficulty--;
        }
    }
}

void sudoku::generateSudoku()
{
    sudoku::isRunning = true;
    //unsigned int seed = generateSeed();
    std::vector<std::vector<int>> uwu(9, std::vector<int>(9, 0));
    sudoku::sudokuValues = uwu;
    sudoku::winningLabel->setText("You havent win yet");
    int difficulty = 20;
    //std::cout << "pos 00 = " << sudokuValues[0][0] << std::endl;
    cleanButtons();

    fillValues();
    setButtons();
    removeElements(difficulty);
    //setButtons();

}

void sudoku::selectCell(QPushButton *b, int row, int col)
{
    //std::cout << "Selectiong cell " << row << col << std::endl;
    if (!sudoku::isRunning)
    {
        return;
    }
    QString qs = b->text();
    std::string str = qs.toStdString();
    if (std::find(sudoku::validButtons.begin(), sudoku::validButtons.end(), b) == sudoku::validButtons.end())
    {
        return;
    }
    if (std::find(sudoku::goodButtons.begin(), sudoku::goodButtons.end(), b) != sudoku::goodButtons.end())
    {
        return;
    }
    if (sudoku::prevButton == NULL)
    {
        b->setStyleSheet("background-color: #C4C4C4; border-radius: 7px; border: 1px solid grey;");
        sudoku::prevButton = b;
        sudoku::isButtonSelected = true;
    }
    else if (b == sudoku::prevButton)
    {
        b->setStyleSheet("background-color: #FFFFFF; border-radius: 7px; border: 1px solid grey;");
        sudoku::prevButton = b;
        sudoku::isButtonSelected = false;
    }
    else
    {
        if (std::find(sudoku::goodButtons.begin(), sudoku::goodButtons.end(), sudoku::prevButton) != sudoku::goodButtons.end())
        {
            sudoku::prevButton->setStyleSheet("background-color: #FFFFFF; border-radius: 7px; border: 1px solid grey; color: #00FF00;");
        }
        else
        {
            sudoku::prevButton->setStyleSheet("background-color: #FFFFFF; border-radius: 7px; border: 1px solid grey; color: #FF0000;");
        }
        b->setStyleSheet("background-color: #C4C4C4; border-radius: 7px; border: 1px solid grey;");
        sudoku::prevButton = b;
        sudoku::isButtonSelected = true;
    }
    sudoku::prevButtonCoord[0] = row;
    sudoku::prevButtonCoord[1] = col;

}

void sudoku::keyPressEvent(QKeyEvent *event)
{
    if (!sudoku::isRunning)
    {
        return;
    }
    if (sudoku::isButtonSelected)
    {
        QString qs = sudoku::prevButton->text();
        std::string str = qs.toStdString();
        //std::cout << "button selected and input readed: " << num << std::endl;
        int num = event->key() - 48;
        if (num > 0 && num <= 9)
        {
            //std::cout << "keypressed " << num << std::endl;
            if (num == sudoku::sudokuValues[prevButtonCoord[0]][prevButtonCoord[1]])
            {
                sudoku::prevButton->setText(intToQString(num));
                sudoku::prevButton->setStyleSheet("background-color: #C4C4C4; border-radius: 7px; border: 1px solid grey; color: green;");
                sudoku::goodButtons.push_back(prevButton);
                isButtonSelected = false;
                if (!hasEmptyCell())
                {
                    sudoku::winningLabel->setText("YOU WIN. Re generate sudoku to play again");
                    sudoku::prevButton->setStyleSheet("background-color: #FFFFFF; border-radius: 7px; border: 1px solid grey; color: #0000FF");
                    //std::cout << "YOU HAVE WIN" << std::endl;
                }
            }
            else
            {
                sudoku::prevButton->setText(intToQString(num));
                sudoku::prevButton->setStyleSheet("background-color: #C4C4C4; border-radius: 7px; border: 1px solid grey; color: red;");
            }
        }
    }
}
