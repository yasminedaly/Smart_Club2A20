#include "sudoku_solver.h"
#include "ui_sudoku_solver.h"
#include <QIntValidator>
#include <QMessageBox>
#include <cmath>
#include <QTimer>
#include <QApplication>
#include <QProcess>

const int N=9;
const int sqrtN=sqrt(N);
QLineEdit *cells[9][9];
QString cellstyle[9][9];
int origgrid[N][N];
bool method=NULL;                           //true if Solve, false if Instant Solve

Sudoku_Solver::Sudoku_Solver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku_Solver)
{
    ui->setupUi(this);


    for(int i=1;i<82;i++){
        QString name = "lineEdit_" + QString::number(i);
        QLineEdit *member = Sudoku_Solver::findChild<QLineEdit*>(name);
        member->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]\\d{0}"),this));
        cells[(i-1)/9][(i-1)%9] = member;
        cellstyle[(i-1)/9][(i-1)%9] = member->styleSheet();
    }


    connect(ui->Solve, SIGNAL(released()), this, SLOT(SolvePressed()));
    connect(ui->SolveIns, SIGNAL(released()), this, SLOT(SolveInsPressed()));
    connect(ui->Reset, SIGNAL(released()), this, SLOT(ResetPressed()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearPressed()));

}

Sudoku_Solver::~Sudoku_Solver()
{
    delete ui;
}

inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

//checks if the given number can be assigned to a currently empty cell
//by checking uniqueness in it's row, column, and subgrid
bool isValid(int grid[N][N],int row,int col,int num){
    for(int j=0;j<N;j++){                       //check row
        if(grid[row][j]==num){
            return false;
        }
    }
    for(int i=0;i<N;i++){                       //check column
        if(grid[i][col]==num){
            return false;
        }
    }
    int boxrow=row/sqrtN;
    int boxcol=col/sqrtN;
    for(int p=0;p<sqrtN;p++){                       //check box
        for(int q=0;q<sqrtN;q++){
            if(grid[sqrtN*boxrow+p][sqrtN*boxcol+q]==num){
                return false;
            }
        }
    }
    return true;

}

bool isValid2(int grid[N][N],int row,int col,int num){
    for(int j=0;j<N;j++){                       //check row
        if(grid[row][j]==num){
            if(j==col){
                continue;
            }
            cells[row][j]->setStyleSheet("QLineEdit{border: 3px solid red;}");
            return false;
        }
    }
    for(int i=0;i<N;i++){                       //check column
        if(grid[i][col]==num){
            if(i==row){
                continue;
            }
            cells[i][col]->setStyleSheet("QLineEdit{border: 3px solid red;}");
            return false;
        }
    }
    int boxrow=row/sqrtN;
    int boxcol=col/sqrtN;
    for(int p=0;p<sqrtN;p++){                       //check box
        for(int q=0;q<sqrtN;q++){
            int x = sqrtN*boxrow+p;
            int y = sqrtN*boxcol+q;
            if(grid[x][y]==num){
                if(x==row && y==col){
                    continue;
                }
                cells[x][y]->setStyleSheet("QLineEdit{border: 3px solid red;}");
                return false;
            }
        }
    }
    return true;

}


//finds next empty cell returns false if not found
bool nextEmptycell(int grid[N][N],int& row, int& col){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(grid[i][j]==0){
                row=i;
                col=j;
                break;
            }
        }
        if(j!=N){                   //if found, break out of the loop
            break;
        }
    }
    if(i!=N&&j!=N){                 //if found, return true
        return true;
    }
    return false;                   //else false
}

bool checkInpValidity(int grid[N][N]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(!cells[i][j]->text().isEmpty()){
                if(!isValid2(grid,i,j,cells[i][j]->text().toInt())){
                    cells[i][j]->setStyleSheet("QLineEdit{border: 3px solid red;}");
                    return false;
                }
            }
        }
    }
    return true;
}

//takes a partially filled grid, and tries to solve it
bool solveSudoku(int grid[N][N]){
    if(method){
        int row,col;
        if(!nextEmptycell(grid,row,col)){        //if no empty cell left, return true
            return true;
        }
        int num;
        for(num=1;num<N+1;num++){
            if(isValid(grid,row,col,num)){       //Assign a valid number to the next Empty cell
                if(method){
                    grid[row][col]=num;
                    cells[row][col]->setText(QString::number(num));
                    cells[row][col]->setStyleSheet("QLineEdit{border: 3px solid green;}");
                    delay(100);
                }


                qApp->processEvents();

                if(!solveSudoku(grid)){          //solve the revised grid. If unable to solve,
                    if(method){
                        grid[row][col]=0;            //reassign the cell to 0
                        cells[row][col]->setText(QString::number(0));
                        cells[row][col]->setStyleSheet("QLineEdit{border: 3px solid red;}");
                        delay(100);
                    }

                    continue;                    //and try a different number
                }
                else{break;}
            }
        }
        if(num==N+1){                            //if no combination worked, return false
            return false;
        }
        return true;                             //otherwise true
    }
    return false;
}

bool solveSudokuIns(int grid[N][N]){
    int row,col;
    if(!nextEmptycell(grid,row,col)){        //if no empty cell left, return true
        return true;
    }
    int num;
    for(num=1;num<N+1;num++){
        if(isValid(grid,row,col,num)){       //Assign a valid number to the next Empty cell
            grid[row][col]=num;
            cells[row][col]->setText(QString::number(num));

            if(!solveSudokuIns(grid)){          //solve the revised grid. If unable to solve,
                grid[row][col]=0;               //reassign the cell to 0
                cells[row][col]->setText(QString::number(0));
                continue;                    //and try a different number
            }
            else{break;}
        }
    }
    if(num==N+1){                            //if no combination worked, return false
        return false;
    }
    return true;                             //otherwise true

}

void Sudoku_Solver::SolvePressed(){
    method = true;

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            cells[i][j]->setStyleSheet(cellstyle[i][j]);
        }
    }

    int grid[N][N];
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            grid[i][j] = cells[i][j]->text().toInt();
            origgrid[i][j] = grid[i][j];
        }
    }

    if(!checkInpValidity(grid)){
        QMessageBox::information(this, tr("Error"), tr("Invalid Input"));
        return;
    }

    if(!solveSudoku(grid)&&method){
        QMessageBox::information(this, tr("Error"), tr("Solution Doesn't Exist"));
    }
}

void Sudoku_Solver::SolveInsPressed(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            cells[i][j]->setStyleSheet(cellstyle[i][j]);
        }
    }

    if(method){
        method = false;
        int grid[N][N];
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                grid[i][j] = origgrid[i][j];
            }
        }
        if(!solveSudokuIns(grid)){
            QMessageBox::information(this, tr("Error"), tr("Solution Doesn't Exist1"));
        }
        return;
    }
    method = false;
    int grid[N][N];
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            origgrid[i][j] = cells[i][j]->text().toInt();
            grid[i][j] = origgrid[i][j];
        }
    }

    if(!checkInpValidity(grid)){
        QMessageBox::information(this, tr("Error"), tr("Invalid Input"));
        return;
    }

    if(!solveSudokuIns(grid)){
        QMessageBox::information(this, tr("Error"), tr("Solution Doesn't Exist2"));
    }

}

void Sudoku_Solver::ResetPressed(){
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void Sudoku_Solver::ClearPressed(){
    method = false;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(!cells[i][j]->text().isEmpty()){
                cells[i][j]->setText("");
                cells[i][j]->setStyleSheet(cellstyle[i][j]);
            }
        }
    }

}
