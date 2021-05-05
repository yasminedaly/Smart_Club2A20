#include "choixupgrade.h"
#include "ui_choixupgrade.h"
#include "iostream"
using namespace std;

//_______________________________CHOIXUPGRADE_________________________________
/**
 * @brief ChoixUpgrade::ChoixUpgrade, constructor of choixUpgrade. Use to upgrade a pawn to an other piece
 * @param parent
 */
ChoixUpgrade::ChoixUpgrade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixUpgrade)
{
    ui->setupUi(this);
}

/**
 * @brief ChoixUpgrade::~ChoixUpgrade, desctructor of choixUpgrade
 */
ChoixUpgrade::~ChoixUpgrade()
{
    delete ui;
}

//_______________________________METHOD_________________________________
/**
 * @brief ChoixUpgrade::on_btn_reine_clicked, emit the signal btn_reine_clicked when the user choose to upgrade the pawn in a queen
 */
void ChoixUpgrade::on_btn_reine_clicked()
{
    emit btn_reine_clicked();
    this->close();
}

/**
 * @brief ChoixUpgrade::on_btn_tour_clicked, emit the signal btn_reine_clicked when the user choose to upgrade the pawn in a rook
 */
void ChoixUpgrade::on_btn_tour_clicked()
{
    emit btn_tour_clicked();
    this->close();
}

/**
 * @brief ChoixUpgrade::on_btn_fou_clicked, emit the signal btn_reine_clicked when the user choose to upgrade the pawn in a bishop
 */
void ChoixUpgrade::on_btn_fou_clicked()
{
    emit btn_fou_clicked();
    this->close();
}

/**
 * @brief ChoixUpgrade::on_btn_cavalier_clicked, emit the signal btn_reine_clicked when the user choose to upgrade the pawn in a knigth
 */
void ChoixUpgrade::on_btn_cavalier_clicked()
{
    emit btn_cavalier_clicked();
    this->close();
}
