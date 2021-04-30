#ifndef PUZZLE_MAIN_WINDOW_G_FOURNISSEURS_H
#define PUZZLE_MAIN_WINDOW_G_FOURNISSEURS_H

#include <QPixmap>
#include <QMainWindow>


class Pieces_G_Fournisseurs;
class Puzzle_G_Fournisseurs;

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

class Puzzle_Main_Window_G_fournisseurs: public QMainWindow
{
    Q_OBJECT
public:
    Puzzle_Main_Window_G_fournisseurs(QWidget *parent = 0);
    void loadImage(const QString &path);

public slots:
    void openImage();
    void setupPuzzle();

private slots:
    void setCompleted();

private:
    void setupMenus();
    void setupWidgets();

    QPixmap puzzleImage;
    Pieces_G_Fournisseurs *piecesList;
    Puzzle_G_Fournisseurs *puzzleWidget;
};

#endif // PUZZLE_MAIN_WINDOW_G_FOURNISSEURS_H
