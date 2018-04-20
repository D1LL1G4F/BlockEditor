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

void MainWindow::createMenu()
{
    save = menuBar()->addAction(tr("&Save Scheme"));
    save->setShortcuts(QKeySequence::Save);
    save->setStatusTip(tr("saves current scheme for later usage"));
    connect(save, &QAction::triggered, this, &MainWindow::saveScheme);

    del = menuBar()->addAction(tr("&Delete Scheme"));
    del->setShortcuts(QKeySequence::Delete);
    del->setStatusTip(tr("resets current scheme to clear space"));
    connect(del, &QAction::triggered, this, &MainWindow::deleteScheme);

    load = menuBar()->addMenu(tr("Load Scheme"));

    simAll = menuBar()->addAction(tr("&Simulate all"));
    simAll->setShortcuts(QKeySequence::InsertParagraphSeparator);
    simAll->setStatusTip(tr("executes simulation of whole scheme"));
    connect(simAll, &QAction::triggered, this, &MainWindow::simulateAll);

    simStep = menuBar()->addAction(tr("&Simulate step"));
    simStep->setShortcuts(QKeySequence::MoveToNextChar);
    simStep->setStatusTip(tr("performs single step of simulation"));
    connect(simStep, &QAction::triggered, this, &MainWindow::simulateStep);

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
