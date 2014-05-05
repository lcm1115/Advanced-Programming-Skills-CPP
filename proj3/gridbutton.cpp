#include "gridbutton.h"

#include <QPushButton>
#include <QString>
#include <QWidget>

GridButton::GridButton(int pos, const QString& text, QWidget* parent)
    : QPushButton(text, parent),
      _pos(pos)
{
}

void GridButton::changeText(int value) {
    if (value == 0) {
        setText(nullptr);
    } else {
        setText(QString::number(value));
    }
}

int GridButton::getPos() const {
    return _pos;
}
