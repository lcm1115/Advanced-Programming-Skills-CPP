#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QPushButton>
#include <QString>

class GridButton : public QPushButton
{
public:
    GridButton(int pos, QString text, QWidget* parent = 0);

    int getPos() const;

    void changeText(int value);

private:
    int _pos;
};

#endif // GRIDBUTTON_H
