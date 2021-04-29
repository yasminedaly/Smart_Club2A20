#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Sudoku_Solver; }
QT_END_NAMESPACE

class Sudoku_Solver : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku_Solver(QWidget *parent = nullptr);
    ~Sudoku_Solver();

private:
    Ui::Sudoku_Solver *ui;

private slots:
    void SolvePressed();
    void SolveInsPressed();
    void ResetPressed();
    void ClearPressed();
};
#endif // SUDOKU_SOLVER_H
