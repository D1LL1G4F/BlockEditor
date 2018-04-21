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
    central = new QWidget;
    createButtons();
    createMenu();
    createCanvas();
    // set default selected item as ITEM_AND
    selectItem(ITEM_AND);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(leftBar);
    layout->addWidget(scene);

    central->setLayout(layout);
    setCentralWidget(central);




}

int MainWindow::getSelectedItem()
{
    return selectedItem;
}

void MainWindow::saveScheme()
{

}

void MainWindow::deleteScheme()
{
    canvas->clear();

}

void MainWindow::loadScheme()
{

}

void MainWindow::selectItem(const int itemType)
{
    selectedItem = itemType;
    buttonAND->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonNAND->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonOR->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonXOR->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonADD->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonSUB->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonGT->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonLT->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonLinker->setStyleSheet("QPushButton{ background-color: lightgrey; }");

    switch (selectedItem) {
    case ITEM_ADD:
        buttonADD->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_AND:
        buttonAND->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_GT:
        buttonGT->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_LINKER:
        buttonLinker->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_LT:
        buttonLT->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_NAND:
        buttonNAND->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_OR:
        buttonOR->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_SUB:
        buttonSUB->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_XOR:
        buttonXOR->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    default:
        break;
    }
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

    leftBar = new QWidget;
    leftBar->setLayout(layout);
    leftBar->setMaximumWidth(150);
}

void MainWindow::createCanvas()
{
    canvas = new Canvas(this);
    canvas->setSceneRect(0, 0, 1000, 1000);

    scene = new QWidget;

    view = new QGraphicsView(canvas,scene);
    view->show();




}
