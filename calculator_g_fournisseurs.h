#ifndef CALCULATOR_G_FOURNISSEURS_H
#define CALCULATOR_G_FOURNISSEURS_H
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class button_G_Fournisseurs;

class calculator_G_Fournisseurs : public QWidget
{
    Q_OBJECT
public:
    calculator_G_Fournisseurs(QWidget *parent = 0);


private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();
private:


    button_G_Fournisseurs *createButton(const QString &text, const char *member);
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);



    double sumInMemory;

    double sumSoFar;

    double factorSoFar;

    QString pendingAdditiveOperator;

    QString pendingMultiplicativeOperator;

    bool waitingForOperand;

    QLineEdit *display;


    enum { NumDigitButtons = 10 };
    button_G_Fournisseurs *digitButtons[NumDigitButtons];
};

#endif // CALCULATOR_G_FOURNISSEURS_H
