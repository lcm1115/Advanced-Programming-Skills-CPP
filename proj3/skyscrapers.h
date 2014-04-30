#ifndef SKYSCRAPERS_H
#define SKYSCRAPERS_H

#include "borderlayout.h"
#include "gridbutton.h"
#include "skyscraperconfig.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

class Skyscrapers : public QWidget
{
    Q_OBJECT

public:
    Skyscrapers(QWidget *parent = nullptr);

private:
    std::vector<std::vector<int>> clues = { { 2, 1, 4, 2, 2 },
                                            { 2, 1, 2, 3, 3 },
                                            { 3, 5, 1, 2, 2 },
                                            { 4, 3, 1, 2, 2 } };
    std::vector<GridButton*> gridButtons;
    std::vector<SkyscraperConfig> history;
    QGridLayout* gridLayout;
    QHBoxLayout* topLayout;
    QPushButton* checkButton;
    QPushButton* clearButton;
    QPushButton* hintButton;
    QPushButton* solveButton;
    QPushButton* tryButton;
    QPushButton* undoButton;
    QWidget* grid;
    QWidget* top;
    BorderLayout* mainWindow;
    SkyscraperConfig config;

private slots:
    void slotCheckButton();
    void slotClearButton();
    void slotHintButton();
    void slotSolveButton();
    void slotTryButton();
    void slotUndoButton();
    void slotGridButton();
};

#endif // SKYSCRAPERS_H
