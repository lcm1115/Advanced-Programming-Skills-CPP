#ifndef SKYSCRAPERS_H
#define SKYSCRAPERS_H

#include "borderlayout.h"
#include "gridbutton.h"
#include "skyscraperconfig.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <vector>

class Skyscrapers : public QWidget
{
    Q_OBJECT

public:
    Skyscrapers(QWidget *parent = nullptr);

private:
    void loadConfig(std::string filepath);

    std::vector<GridButton*> gridButtons;
    std::vector<QLabel*> labels;
    std::vector<SkyscraperConfig> history;
    QGridLayout* gridLayout;
    QHBoxLayout* topLayout;
    QPushButton* loadButton;
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
    void slotLoadButton();
};

#endif // SKYSCRAPERS_H
