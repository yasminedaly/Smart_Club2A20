#include "camera.h"
#include "ui_camera.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

Camera::Camera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);
    mCamera= new QCamera (this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera, this);
    mLayout = new QVBoxLayout;
    mOpcionesMenu = new QMenu ("Opciones",this);
    mEncenderAction = new QAction ("Ouvrir Caméra",this);
    mApagarAction = new QAction ("Figer",this);
    mCapturarAction = new QAction ("Prendre une photo",this);

    mOpcionesMenu->addActions({mEncenderAction,mApagarAction,mCapturarAction});
    ui->options->setMenu (mOpcionesMenu);
    mCamera->setViewfinder(mCameraViewfinder);
    mLayout->addWidget(mCameraViewfinder);
    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);

    connect (mEncenderAction,&QAction::triggered, [&] () {    mCamera->start();    });
    connect (mApagarAction,&QAction::triggered, [&] () {
    mCamera->stop();
    });
    connect (mCapturarAction,&QAction::triggered, [&] () {
    auto filename = QFileDialog::getSaveFileName(this, "Capture","/","Imagen(*.jpg;*.jpeg)");
    if (filename.isEmpty() )
    {
       return;
    }
    mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageEncoderSettings;
    imageEncoderSettings.setCodec("image/jpeg");
    imageEncoderSettings.setResolution(1600,1200);
    mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(filename);
    mCamera->unlock();
    });


}

Camera::~Camera()
{
    delete ui;
}
