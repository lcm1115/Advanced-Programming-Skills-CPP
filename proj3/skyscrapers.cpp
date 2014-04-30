#include "skyscrapers.h"

#include "backtrack.h"
#include "borderlayout.h"
#include "gridbutton.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <vector>

using std::vector;

#include <iostream>
using namespace std;

Skyscrapers::Skyscrapers(QWidget *parent) :
    QWidget(parent),
    config(5, clues) {
    setWindowTitle("Skyscrapers - Liam Morris");
    // Create top buttons
    checkButton = new QPushButton("Check", this);
    clearButton = new QPushButton("Clear", this);
    hintButton = new QPushButton("Hint", this);
    solveButton = new QPushButton("Solve", this);
    tryButton = new QPushButton("Try", this);
    undoButton = new QPushButton("Undo", this);
    top = new QWidget(this);
    topLayout = new QHBoxLayout(top);
    topLayout->addWidget(clearButton);
    topLayout->addWidget(undoButton);
    topLayout->addWidget(hintButton);
    topLayout->addWidget(checkButton);
    topLayout->addWidget(tryButton);
    topLayout->addWidget(solveButton);
    connect(checkButton, SIGNAL(clicked()), this, SLOT(slotCheckButton()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(slotClearButton()));
    connect(hintButton, SIGNAL(clicked()), this, SLOT(slotHintButton()));
    connect(solveButton, SIGNAL(clicked()), this, SLOT(slotSolveButton()));
    connect(tryButton, SIGNAL(clicked()), this, SLOT(slotTryButton()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(slotUndoButton()));

    vector<QLabel*> labels;
    labels.push_back(new QLabel());
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("1"));
    labels.push_back(new QLabel("4"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("4"));
    labels.push_back(new QLabel("3"));
    labels.push_back(new QLabel("1"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("1"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("3"));
    labels.push_back(new QLabel("3"));
    labels.push_back(new QLabel("3"));
    labels.push_back(new QLabel("5"));
    labels.push_back(new QLabel("1"));
    labels.push_back(new QLabel("2"));
    labels.push_back(new QLabel("2"));

    for (QLabel* label : labels) {
        label->setAlignment(Qt::AlignCenter);
        label->setMinimumSize(65, 65);
        label->setMaximumSize(65, 65);
        QFont font = label->font();
        font.setPointSize(24);
        label->setFont(font);
    }

    // Create grid
    grid = new QWidget(this);
    gridLayout = new QGridLayout(grid);
    gridLayout->addWidget(labels.at(0), 0, 0);
    gridLayout->addWidget(labels.at(0), 0, 6);
    gridLayout->addWidget(labels.at(0), 6, 0);
    gridLayout->addWidget(labels.at(0), 6, 6);
    for (int i = 1; i <= 5; ++i) {
        gridLayout->addWidget(labels.at(i), 0, i);
    }
    for (int i = 1; i <= 5; ++i) {
        gridLayout->addWidget(labels.at(i + 5), 6, i);
    }
    for (int i = 1; i <= 5; ++i) {
        gridLayout->addWidget(labels.at(i + 10), i, 0);
    }
    for (int i = 1; i <= 5; ++i) {
        gridLayout->addWidget(labels.at(i + 15), i, 6);
    }
    for (int i = 0; i < 25; ++i) {
        GridButton* button = new GridButton(i, nullptr, this);
        QFont font = button->font();
        font.setPointSize(20);
        button->setFont(font);
        button->setMinimumSize(65, 65);
        button->setMaximumSize(65, 65);
        connect(button, SIGNAL(clicked()), this, SLOT(slotGridButton()));
        gridButtons.push_back(button);
        gridLayout->addWidget(button,  i / 5 + 1, i % 5 + 1);
    }

    // Create main window
    mainWindow = new BorderLayout(this);
    mainWindow->addWidget(top, BorderLayout::North);
    mainWindow->addWidget(grid, BorderLayout::Center);
    setLayout(mainWindow);
    setFixedSize(600, 600);
}

void Skyscrapers::slotCheckButton() {
    config.setPos();
    QMessageBox* box = new QMessageBox(this);
    box->setWindowTitle("Board Validity");
    box->setText(config.isValid() && config.isGoal() ? "The board configuration is a solution." : "The board configuration is not a solution.");
    box->setVisible(true);
}

void Skyscrapers::slotClearButton() {
    config.clear();
    history.clear();
    for (GridButton* gb : gridButtons) {
        gb->setText(nullptr);
    }
}

void Skyscrapers::slotHintButton() {
    config.setPos();
    Backtrack<SkyscraperConfig> b(config);
    SkyscraperConfig solution = b.solve();
    if (solution.isFailure()) {
        QMessageBox* box = new QMessageBox(this);
        box->setWindowTitle("Board Invalid");
        box->setText("Solution not reachable from current configuration.");
        box->setVisible(true);
    } else {
        int row = config.getRow();
        if (row == 5) return;
        int col = config.getCol();
        int pos = row * 5 + col;
        int value = solution.getValueAtPos(pos);
        history.push_back(config);
        config.setValueAtPos(value, pos);
        gridButtons.at(pos)->changeText(config.getValueAtPos(pos));
    }
}

void Skyscrapers::slotSolveButton() {
    history.push_back(config);
    config.clear();
    config.setPos();
    Backtrack<SkyscraperConfig> b(config);
    config = b.solve();
    for (int i = 0; i < 25; ++i) {
        gridButtons.at(i)->changeText(config.getValueAtPos(i));
    }
}

void Skyscrapers::slotTryButton() {
    QMessageBox* box = new QMessageBox(this);
    box->setWindowTitle("Board Validity");
    box->setText(config.isValid() ? "The board configuration is valid." : "The board configuration is invalid.");
    box->setVisible(true);
}

void Skyscrapers::slotUndoButton() {
    if (history.size() > 0) {
        config = history.back();
        history.pop_back();

        for (int i = 0; i < 25; ++i) {
            gridButtons.at(i)->changeText(config.getValueAtPos(i));
        }
    }
}

void Skyscrapers::slotGridButton() {
    history.push_back(config);
    GridButton* button = (GridButton*) sender();
    config.clickPos(button->getPos());
    button->changeText(config.getValueAtPos(button->getPos()));
}
