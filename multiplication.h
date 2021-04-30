#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <QMainWindow>

namespace Ui {
class multiplication;
}

class multiplication: public QMainWindow
{
    Q_OBJECT

public:
    explicit multiplication(QWidget *parent = 0);
    ~multiplication();


private:
    Ui::multiplication *ui;

private slots:

    void btnStart_click();
    void btnSubmit_click();
    int calculate(int n1, int n2);
    void randomise();
    void reset();
    void validate(int userInput, int result);

};

#endif // MULTIPLICATION_H
