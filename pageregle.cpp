#include "pageregle.h"
#include "ui_pageregle.h"

//_______________________________PAGEREGLE_________________________________
/**
 * @brief pageRegle::pageRegle, constructor of the rules page
 * @param parent
 */
pageRegle::pageRegle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pageRegle)
{
    ui->setupUi(this);
}

/**
 * @brief pageRegle::~pageRegle, destructor of the rules page
 */
pageRegle::~pageRegle()
{
    delete ui;
}

//_______________________________METHOD_________________________________

/**
 * @brief pageRegle::on_pushButton_clicked, return to the main menu when the button exit is pressed
 */
void pageRegle::on_pushButton_clicked()
{
    MainMenu menu;
    menu.exec();
    this->close();
}

/**
 * @brief pageRegle::on_pushButton_2_clicked, show the next rules pages when the user clicked on the next button
 */
void pageRegle::on_pushButton_2_clicked()
{
    ui->label->setPixmap(QPixmap(":/images/game//game/regle2.PNG"));

}

/**
 * @brief pageRegle::on_pushButton_3_clicked, show the previous rules pages when the user clicked on the previous button
 */
void pageRegle::on_pushButton_3_clicked()
{
    ui->label->setPixmap(QPixmap(":/images/game//game/regle1.PNG"));
}
