#include "digitalclock.h"

#include <QTime>
#include <QTimer>

//! [0]
DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);

    showTime();

    setWindowTitle(tr("Digital Clock"));
    resize(400, 200);
}
//! [0]

//! [1]
void DigitalClock::showTime()
//! [1] //! [2]
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    display(text);
}
//! [2]
