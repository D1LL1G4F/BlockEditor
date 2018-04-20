#include "mainwindow.h"

const int MainWindow::ITEM_AND = 0;
const int MainWindow::ITEM_NAND = 1;
const int MainWindow::ITEM_OR = 2;
const int MainWindow::ITEM_XOR = 3;
const int MainWindow::ITEM_ADD = 4;
const int MainWindow::ITEM_SUB = 5;
const int MainWindow::ITEM_GT = 6;
const int MainWindow::ITEM_LT = 7;
const int MainWindow::ITEM_LINKER = 8;


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

void MainWindow::selectItem(const int itemType)
{
    selectedItem = itemType;
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
    QSignalMapper* signalMapper = new QSignalMapper (this);

    buttonAND = new QPushButton("binary AND");
    connect(buttonAND, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonNAND = new QPushButton("binary NAND");
    connect(buttonNAND, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonOR = new QPushButton("binary OR");
    connect(buttonOR, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonXOR = new QPushButton("binary XOR");
    connect(buttonXOR, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonADD = new QPushButton("ADD");
    connect(buttonADD, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonSUB = new QPushButton("SUB");
    connect(buttonSUB, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonGT = new QPushButton(">");
    connect(buttonGT, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonLT = new QPushButton("<");
    connect(buttonLT, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonLinker = new QPushButton("Linker");
    connect(buttonLinker, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper -> setMapping (buttonAND, ITEM_AND);
    signalMapper -> setMapping (buttonNAND, ITEM_NAND);
    signalMapper -> setMapping (buttonOR, ITEM_OR);
    signalMapper -> setMapping (buttonXOR, ITEM_XOR);
    signalMapper -> setMapping (buttonADD, ITEM_ADD);
    signalMapper -> setMapping (buttonSUB, ITEM_SUB);
    signalMapper -> setMapping (buttonGT, ITEM_GT);
    signalMapper -> setMapping (buttonLT, ITEM_LT);
    signalMapper -> setMapping (buttonLinker, ITEM_LINKER);

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(selectItem(int))) ;

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
