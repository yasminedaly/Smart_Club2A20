#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QMainWindow>
//

//! [0]
class AnalogClock : public QWidget
{
    Q_OBJECT

public:
    AnalogClock(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};
//! [0]

#endif
