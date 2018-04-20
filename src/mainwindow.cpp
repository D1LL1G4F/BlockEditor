#include "mainwindow.h"


MainWindow::MainWindow()
{
    createButtons();
    createMenu();
    createCanvas();
}

void MainWindow::saveScheme()
{

}

void MainWindow::deleteScheme()
{

}

void MainWindow::loadScheme()
{

}

void MainWindow::addBlock()
{

}

void MainWindow::addLinker()
{

}

void MainWindow::simulateAll()
{

}

void MainWindow::simulateStep()
{

}

void MainWindow::exit()
{

}

void MainWindow::createMenu()
{

}

void MainWindow::createButtons()
{
    buttonAND = new QPushButton("binary AND");
    buttonNAND = new QPushButton("binary NAND");
    buttonOR = new QPushButton("binary OR");
    buttonXOR = new QPushButton("binary XOR");
    buttonADD = new QPushButton("ADD");
    buttonSUB = new QPushButton("SUB");
    buttonGT = new QPushButton(">");
    buttonLT = new QPushButton("<");
    buttonLinker = new QPushButton("Linker");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(buttonAND);
    layout->addWidget(buttonNAND);
    layout->addWidget(buttonOR);
    layout->addWidget(buttonXOR);
    layout->addWidget(buttonADD);
    layout->addWidget(buttonSUB);
    layout->addWidget(buttonGT);
    layout->addWidget(buttonLT);
    layout->addWidget(buttonLinker);

    QWidget *central = new QWidget;
    central->setLayout(layout);
    setCentralWidget(central);
}

void MainWindow::createCanvas()
{

}
