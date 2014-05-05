#include "skyscrapers.h"

#include <QApplication>
#include <QMessageBox>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Skyscrapers w;
    w.show();
    QMessageBox* instructions = new QMessageBox(&w);
    instructions->setWindowTitle("Instructions");
    instructions->setText("Skyscrapers Instructions:\n\n"
                          "1. The board state consists of a NxN grid of numbers "
                          "ranging from 1-N. Each number represents the "
                          "height of a skyscraper at that position.\n"
                          "2. Along each side of the board are numbers. What "
                          "each of these numbers represents is the number of "
                          "skyscrapers visible from that position. Skyscrapers "
                          "are visible if there are no taller skyscrapers in "
                          "front.\n"
                          "3. A skyscraper can be placed in a locatio by "
                          "clicking the location. Clicking the location "
                          "increments the height at that location by 1.\n"
                          "4. A solution to the puzzle is one which adheres "
                          "to the numbers on the sides and in which each "
                          "number appears only once in each row and column.");
    instructions->show();

    return a.exec();
}
