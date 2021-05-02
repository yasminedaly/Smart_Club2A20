#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);          // Initialize the player
    m_player->setMedia(QUrl("http://radio.rathumakara.com:8000/rathumakara.mp3"));//Set the default playing stream
    m_player->setVolume(70);                    // Set the volume for playing tracks
    ui->volumedial->setValue(70);

    // connect the control buttons to the control slots
    connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);

}

Widget::~Widget()
{
    delete ui;
    delete m_player;
}

void Widget::on_volumedial_valueChanged(int value)
{
    m_player->setVolume(value);//adjust player volume
    QString vol = QString::number(value);//convert volume value integer to string
    ui->volumeLabel->setText("Volume : "+vol+"%");//display current volume
}

void Widget::on_kissButton_clicked()
{
    m_player->stop();//stop current playback
    m_player->setMedia(QUrl("http://s3.voscast.com:8404/;stream1472803644663/1"));//set new stream url
    m_player->play();//start playing selected channel
    ui->statuslabel->setText("Now Playing : Kiss FM");//
}

void Widget::on_rathumakaraButton_clicked()
{
    m_player->stop();
    m_player->setMedia(QUrl("http://radio.rathumakara.com:8000/rathumakara.mp3"));
    m_player->play();
    ui->statuslabel->setText("Now Playing : RathuMakara FM");
}


void Widget::on_siyathaButton_clicked()
{
    m_player->stop();
    m_player->setMedia(QUrl("http://s3.voscast.com:8408/.mp3"));
    m_player->play();
    ui->statuslabel->setText("Now Playing : Siyatha FM");
}

void Widget::on_nethButton_clicked()
{
    m_player->stop();
    m_player->setMedia(QUrl("http://69.46.24.226:7669/stream"));
    m_player->play();
    ui->statuslabel->setText("Now Playing : Neth FM");
}

void Widget::on_rhythmworldButton_clicked()
{
    m_player->stop();
    m_player->setMedia(QUrl("http://live.tnlrn.com:8030/live.mp3"));
    m_player->play();
    ui->statuslabel->setText("Now Playing : Rhythm World");
}

void Widget::on_lakhandaButton_clicked()
{
    m_player->stop();
    m_player->setMedia(QUrl("https://cp12.serverse.com/proxy/itnfm?mp=/stream"));
    m_player->play();
    ui->statuslabel->setText("Now Playing : Lakhanda");
}
