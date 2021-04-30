#ifndef BUTTON_G_FOURNISSEURS_H
#define BUTTON_G_FOURNISSEURS_H

#include <QToolButton>
class button_G_Fournisseurs : public QToolButton
{
    Q_OBJECT
public:
    explicit button_G_Fournisseurs(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const override;
};

#endif // BUTTON_G_FOURNISSEURS_H
