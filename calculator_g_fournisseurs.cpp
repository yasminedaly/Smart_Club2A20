#include <QtWidgets>

#include <cmath>

#include "button_g_fournisseurs.h"
#include "calculator_g_fournisseurs.h"

calculator_G_Fournisseurs::calculator_G_Fournisseurs(QWidget *parent)
: QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;
    display = new QLineEdit("0");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);



    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    button_G_Fournisseurs *pointButton = createButton(tr("."), SLOT(pointClicked()));
    button_G_Fournisseurs *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

    button_G_Fournisseurs *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    button_G_Fournisseurs *clearButton = createButton(tr("Clear"), SLOT(clear()));
    button_G_Fournisseurs *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));

    button_G_Fournisseurs *clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    button_G_Fournisseurs *readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    button_G_Fournisseurs *setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    button_G_Fournisseurs *addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    button_G_Fournisseurs *divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked()));
    button_G_Fournisseurs *timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked()));
    button_G_Fournisseurs *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    button_G_Fournisseurs *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    button_G_Fournisseurs *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    button_G_Fournisseurs *powerButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked()));
    button_G_Fournisseurs *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    button_G_Fournisseurs *equalButton = createButton(tr("="), SLOT(equalClicked()));



    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}



void calculator_G_Fournisseurs::digitClicked()
{
    button_G_Fournisseurs *clickedButton = qobject_cast<button_G_Fournisseurs *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}



void calculator_G_Fournisseurs::unaryOperatorClicked()

{
    button_G_Fournisseurs *clickedButton = qobject_cast<button_G_Fournisseurs *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}



void calculator_G_Fournisseurs::additiveOperatorClicked()

{
    button_G_Fournisseurs *clickedButton = qobject_cast<button_G_Fournisseurs *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();


    if (!pendingMultiplicativeOperator.isEmpty()) {

        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }


    if (!pendingAdditiveOperator.isEmpty()) {

        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }



    pendingAdditiveOperator = clickedOperator;


    waitingForOperand = true;
}


void calculator_G_Fournisseurs::multiplicativeOperatorClicked()
{
    button_G_Fournisseurs *clickedButton = qobject_cast<button_G_Fournisseurs *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}



void calculator_G_Fournisseurs::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void calculator_G_Fournisseurs::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}


void calculator_G_Fournisseurs::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}


void calculator_G_Fournisseurs::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}


void calculator_G_Fournisseurs::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}


void calculator_G_Fournisseurs::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}


void calculator_G_Fournisseurs::clearMemory()
{
    sumInMemory = 0.0;
}

void calculator_G_Fournisseurs::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void calculator_G_Fournisseurs::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void calculator_G_Fournisseurs::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}



button_G_Fournisseurs *calculator_G_Fournisseurs::createButton(const QString &text, const char *member)
{
    button_G_Fournisseurs *button = new button_G_Fournisseurs(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


void calculator_G_Fournisseurs::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}


bool calculator_G_Fournisseurs::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}
