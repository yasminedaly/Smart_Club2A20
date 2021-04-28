#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_volumedial_valueChanged(int value);

    void on_kissButton_clicked();

    void on_rathumakaraButton_clicked();

    void on_siyathaButton_clicked();

    void on_nethButton_clicked();

    void on_rhythmworldButton_clicked();

    void on_lakhandaButton_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer        *m_player;          // Track player
};

#endif // WIDGET_H
