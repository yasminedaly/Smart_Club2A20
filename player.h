#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMouseEvent>

namespace Ui {
class player;
}

class player : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

    enum MouseType {
        None = 0,
        Top,
        Bottom,
        Left,
        Right,
        Move
    };

public:
    explicit player(QWidget *parent = 0);
    ~player();
    QPoint previousPosition() const;

public slots:
    void setPreviousPosition(QPoint previousPosition);

signals:
    void previousPositionChanged(QPoint previousPosition);

private slots:
    void on_btn_add_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::player *ui;
    QStandardItemModel  *m_playListModel;
    QMediaPlayer        *m_player;
    QMediaPlaylist      *m_playlist;

    MouseType m_leftMouseButtonPressed;
    QPoint m_previousPosition;

    MouseType checkResizableField(QMouseEvent *event);
};

#endif // PLAYER_H
