#include "skyscrapers.h"

#include "backtrack.h"
#include "borderlayout.h"
#include "gridbutton.h"

#include <fstream>
#include <QFileDialog>
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
    config(true) {
    setWindowTitle("Skyscrapers - Liam Morris");
    // Create top buttons
    loadButton = new QPushButton("Load", this);
    checkButton = new QPushButton("Check", this);
    checkButton->setEnabled(false);
    clearButton = new QPushButton("Clear", this);
    clearButton->setEnabled(false);
    hintButton = new QPushButton("Hint", this);
    hintButton->setEnabled(false);
    solveButton = new QPushButton("Solve", this);
    solveButton->setEnabled(false);
    tryButton = new QPushButton("Try", this);
    tryButton->setEnabled(false);
    undoButton = new QPushButton("Undo", this);
    undoButton->setEnabled(false);
    top = new QWidget(this);
    topLayout = new QHBoxLayout(top);
    topLayout->addWidget(loadButton);
    topLayout->addWidget(clearButton);
    topLayout->addWidget(undoButton);
    topLayout->addWidget(hintButton);
    topLayout->addWidget(checkButton);
    topLayout->addWidget(tryButton);
    topLayout->addWidget(solveButton);
    connect(checkButton, SIGNAL(clicked()), this, SLOT(slotCheckButton()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(slotClearButton()));
    connect(hintButton, SIGNAL(clicked()), this, SLOT(slotHintButton()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(slotLoadButton()));
    connect(solveButton, SIGNAL(clicked()), this, SLOT(slotSolveButton()));
    connect(tryButton, SIGNAL(clicked()), this, SLOT(slotTryButton()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(slotUndoButton()));

    // Create grid
    grid = new QWidget(this);
    gridLayout = new QGridLayout(grid);

    // Create main window
    mainWindow = new BorderLayout(this);
    mainWindow->addWidget(top, BorderLayout::North);
    mainWindow->addWidget(grid, BorderLayout::Center);
    setLayout(mainWindow);
    setFixedSize(600, 600);
}

void Skyscrapers::loadConfig(string filepath) {
    ifstream input(filepath, ifstream::in);
    int n;
    input >> n;

    labels.clear();
    labels.push_back(new QLabel(this));
    for (int i = 0; i < 4 * n; ++i) {
        QLabel* label = new QLabel(this);
        label->setAlignment(Qt::AlignCenter);
        label->setMinimumSize(65, 65);
        label->setMaximumSize(65, 65);
        QFont font = label->font();
        font.setPointSize(24);
        label->setFont(font);
        labels.push_back(label);
    }

    // Create grid
    QLayoutItem* item;
    while (item = gridLayout->takeAt(0)) {
        delete item;
    }
    gridLayout->addWidget(labels.at(0), 0, 0);
    gridLayout->addWidget(labels.at(0), 0, n + 1);
    gridLayout->addWidget(labels.at(0), n + 1, 0);
    gridLayout->addWidget(labels.at(0), n + 1, n + 1);
    for (int i = 1; i <= n; ++i) {
        gridLayout->addWidget(labels.at(i), 0, i);
    }
    for (int i = 1; i <= n; ++i) {
        gridLayout->addWidget(labels.at(i + n), i, 0);
    }
    for (int i = 1; i <= n; ++i) {
        gridLayout->addWidget(labels.at(i + 2 * n), i, n + 1);
    }
    for (int i = 1; i <= n; ++i) {
        gridLayout->addWidget(labels.at(i + 3 * n), n + 1, i);
    }

    gridButtons.clear();
    for (int i = 0; i < n * n; ++i) {
        GridButton* button = new GridButton(i, nullptr, this);
        QFont font = button->font();
        font.setPointSize(20);
        button->setFont(font);
        button->setMinimumSize(65, 65);
        button->setMaximumSize(65, 65);
        button->setEnabled(false);
        connect(button, SIGNAL(clicked()), this, SLOT(slotGridButton()));
        gridButtons.push_back(button);
        gridLayout->addWidget(button,  i / n + 1, i % n + 1);
    }

    history.clear();
    checkButton->setEnabled(true);
    clearButton->setEnabled(true);
    hintButton->setEnabled(true);
    solveButton->setEnabled(true);
    tryButton->setEnabled(true);
    undoButton->setEnabled(false);
    for (auto button : gridButtons) {
        button->setText(0);
        button->setEnabled(true);
    }

    vector<vector<int>> clues;

    int val;
    for (int i = 0; i < 4; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            input >> val;
            if (val != 0) {
                labels.at(i * n + j + 1)->setText(QString::number(val));
            } else {
                labels.at(i * n + j + 1)->setText(nullptr);
            }
            row.push_back(val);
        }
        clues.push_back(row);
    }

    vector<vector<int>> prefilled;
    int row, col;
    while (input >> row) {
        input >> col;
        input >> val;
        prefilled.push_back({ row, col, val });
        gridButtons.at(row * n + col)->setText(QString::number(val));
        gridButtons.at(row * n + col)->setEnabled(false);
    }

    input.close();

    SkyscraperConfig newConfig(n, clues, prefilled);
    config = newConfig;
}

void Skyscrapers::slotCheckButton() {
    config.setPos();
    QMessageBox* box = new QMessageBox(this);
    box->setWindowTitle("Board Validity");
    box->setText(config.isValid() && config.isGoal() ? "The board configuration is a solution." : "The board configuration is not a solution.");
    box->show();
}

void Skyscrapers::slotClearButton() {
    config.clear();
    history.clear();
    undoButton->setEnabled(false);
    for (int i = 0; i < config.getSize() * config.getSize(); ++i) {
        gridButtons.at(i)->changeText(config.getValueAtPos(i));
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
        box->show();
    } else {
        int n = config.getSize();
        int row = config.getRow();
        if (row == n) return;
        int col = config.getCol();
        int pos = row * n + col;
        int value = solution.getValueAtPos(pos);
        history.push_back(config);
        undoButton->setEnabled(true);
        config.setValueAtPos(value, pos);
        gridButtons.at(pos)->changeText(config.getValueAtPos(pos));
    }
}

void Skyscrapers::slotSolveButton() {
    config.setPos();
    Backtrack<SkyscraperConfig> b(config);
    SkyscraperConfig solution = b.solve();
    if (solution.isFailure()) {
        QMessageBox* box = new QMessageBox(this);
        box->setWindowTitle("Board Invalid");
        box->setText("Solution not reachable from current configuration.");
        box->show();
    } else {
        history.push_back(config);
        undoButton->setEnabled(true);
        config = solution;
        for (int i = 0; i < config.getSize() * config.getSize(); ++i) {
            gridButtons.at(i)->changeText(config.getValueAtPos(i));
        }
    }
}

void Skyscrapers::slotTryButton() {
    QMessageBox* box = new QMessageBox(this);
    box->setWindowTitle("Board Validity");
    box->setText(config.isValid() ? "The board configuration is valid." : "The board configuration is invalid.");
    box->show();
}

void Skyscrapers::slotUndoButton() {
    if (history.size() > 0) {
        config = history.back();
        history.pop_back();

        for (int i = 0; i < config.getSize() * config.getSize(); ++i) {
            gridButtons.at(i)->changeText(config.getValueAtPos(i));
        }
    }

    if (history.size() == 0) {
        undoButton->setEnabled(false);
    }
}

void Skyscrapers::slotGridButton() {
    history.push_back(config);
    undoButton->setEnabled(true);
    GridButton* button = (GridButton*) sender();
    config.clickPos(button->getPos());
    button->changeText(config.getValueAtPos(button->getPos()));
}

void Skyscrapers::slotLoadButton() {
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->exec();
    if (fileDialog->selectedFiles().size() > 0) {
        const QString& fp = fileDialog->selectedFiles().at(0);
        loadConfig(fp.toStdString());
    }
}
