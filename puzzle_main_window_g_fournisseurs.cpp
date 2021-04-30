#include "puzzle_main_window_g_fournisseurs.h"


#include "puzzle_g_fournisseurs.h"
#include "pieces_g_fournisseurs.h"

#include <QtWidgets>
#include <stdlib.h>
Puzzle_Main_Window_G_fournisseurs::Puzzle_Main_Window_G_fournisseurs(QWidget *parent)
: QMainWindow(parent)
{
    setupMenus();
    setupWidgets();

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Puzzle"));
}
void Puzzle_Main_Window_G_fournisseurs::openImage()
{
    const QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                                     tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
        loadImage(fileName);
}

void Puzzle_Main_Window_G_fournisseurs::loadImage(const QString &fileName)
{
    QPixmap newImage;
    if (!newImage.load(fileName)) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded."),
                             QMessageBox::Close);
        return;
    }
    puzzleImage = newImage;
    setupPuzzle();
}

void Puzzle_Main_Window_G_fournisseurs::setCompleted()
{
    QMessageBox::information(this, tr("Puzzle Completed"),
                             tr("Congratulations! You have completed the puzzle!\n"
                                "Click OK to start again."),
                             QMessageBox::Ok);

    setupPuzzle();
}

void Puzzle_Main_Window_G_fournisseurs::setupPuzzle()
{
    int size = qMin(puzzleImage.width(), puzzleImage.height());
    puzzleImage = puzzleImage.copy((puzzleImage.width() - size)/2,
        (puzzleImage.height() - size)/2, size, size).scaled(puzzleWidget->width(),
            puzzleWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    piecesList->clear();

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            int pieceSize = puzzleWidget->pieceSize();
            QPixmap pieceImage = puzzleImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            piecesList->addPiece(pieceImage, QPoint(x, y));
        }
    }

    qsrand(QCursor::pos().x() ^ QCursor::pos().y());

    for (int i = 0; i < piecesList->count(); ++i) {
        if (int(2.0*qrand()/(RAND_MAX+1.0)) == 1) {
            QListWidgetItem *item = piecesList->takeItem(i);
            piecesList->insertItem(0, item);
        }
    }

    puzzleWidget->clear();
}

void Puzzle_Main_Window_G_fournisseurs::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &Puzzle_Main_Window_G_fournisseurs::openImage);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    gameMenu->addAction(tr("&Restart"), this, &Puzzle_Main_Window_G_fournisseurs::setupPuzzle);
}

void Puzzle_Main_Window_G_fournisseurs::setupWidgets()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    puzzleWidget = new Puzzle_G_Fournisseurs(400);

    piecesList = new Pieces_G_Fournisseurs(puzzleWidget->pieceSize(), this);


    connect(puzzleWidget, &Puzzle_G_Fournisseurs::puzzleCompleted,
            this, &Puzzle_Main_Window_G_fournisseurs::setCompleted, Qt::QueuedConnection);

    frameLayout->addWidget(piecesList);
    frameLayout->addWidget(puzzleWidget);
    setCentralWidget(frame);
}
