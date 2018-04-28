#include "mainwindow.h"
#include "scheme.h"
#include <QMessageBox>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <QInputDialog>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <fstream>

namespace json = boost::property_tree;


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

QLabel *MainWindow::getOutputScr()
{
    return output;
}

void MainWindow::saveScheme()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Scheme"), "new_scheme.schm",tr("Scheme files (*.schm)"));

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, tr("BlockEditor error"), tr("File name cannot be empty"), QMessageBox::Cancel);
        return;
    }
    else {
            resetSim();
            json::ptree root;
            root = canvas->getScheme()->serializeToJson();
            json::write_json(fileName.toStdString(),root);
        }
}

void MainWindow::deleteScheme()
{
    canvas->clearAll();
}

void MainWindow::loadScheme()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load scheme"), "",tr("Scheme files (*.schm)"));

        if (fileName.isEmpty()) {
            QMessageBox::warning(this, tr("BlockEditor error"), tr("Cannot load selected file"), QMessageBox::Cancel);
            return;
        }
        else {
            json::ptree root;
            try {
                json::read_json(fileName.toStdString(),root);
                canvas->setScheme(root);
            }
            catch (std::exception const&  ex) {
                string str("Cannot load selected file ERR_INFO(" + string(ex.what()) + ")");
                QMessageBox::warning(this, tr("BlockEditor error"), tr(str.c_str()), QMessageBox::Cancel);
            }

        }
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
    buttonMover->setStyleSheet("QPushButton{ background-color: lightgrey; }");
    buttonDestructor->setStyleSheet("QPushButton{ background-color: lightgrey; }");

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
    case ITEM_MOVER:
        buttonMover->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    case ITEM_DESTRUCTOR:
        buttonDestructor->setStyleSheet("QPushButton{ background-color: lightblue; }");
        break;
    default:
        break;
    }
}

void MainWindow::simulateAll()
{
    while (!canvas->getScheme()->isSimulationFinished()) {
        simulateStep();
    }

}

void MainWindow::simulateStep()
{
    if (canvas->getScheme()->isSchemeLooped()) {
        QMessageBox::warning(this, tr("BlockEditor WARNING"), tr("Loops detected in scheme"), QMessageBox::Cancel);
    }
    if (canvas->getScheme()->isSimulationFinished()) {
        return;
    }
    std::vector<int> blocks;
    bool succ = true;
    try {
        blocks = canvas->getScheme()->simulateStep();
    }
    catch (char const *error) {
        succ = false;
        QMessageBox::warning(this, tr("BlockEditor WARNING"), tr(error), QMessageBox::Cancel);
    }
    if (succ) {
        for (int i = 0; i < canvas->getScheme()->getLastBlockIndex()+1; i++) {
            canvas->changeRectColor(i,QColor(0,0,0,255));
        }
        for (int block : blocks) {
            canvas->changeRectColor(block,QColor(255,0,0,255));
        }
    }
    if (canvas->getScheme()->isSimulationFinished()) {
        QString results = "";
        for (int block : blocks) {
            results += "Result: " + QString::number(canvas->getScheme()->getBlock(block)->getOutPort(0)->getValue()) + "\n";
        }
        output->setText(results);
    }
}

void MainWindow::resetSim()
{
    canvas->getScheme()->resetSimulation();
    output->setText("");
    for (int i = 0; i < canvas->getScheme()->getLastBlockIndex()+1; i++) {
        canvas->changeRectColor(i,QColor(0,0,0,255));
    }
    canvas->reloadScheme();
}

void MainWindow::createMenu()
{
    save = menuBar()->addAction("&Save Scheme");
    save->setShortcuts(QKeySequence::Save);
    save->setStatusTip("saves current scheme for later usage");
    connect(save, &QAction::triggered, this, &MainWindow::saveScheme);

    del = menuBar()->addAction(tr("&Delete Scheme"));
    del->setShortcuts(QKeySequence::Delete);
    del->setStatusTip(tr("resets current scheme to clear space"));
    connect(del, &QAction::triggered, this, &MainWindow::deleteScheme);

    load = menuBar()->addAction(tr("&Load scheme"));
    load->setShortcuts(QKeySequence::Open);
    load->setStatusTip(tr("load scheme from file"));
    connect(load, &QAction::triggered, this, &MainWindow::loadScheme);

    simAll = menuBar()->addAction(tr("&Simulate all"));
    simAll->setShortcuts(QKeySequence::InsertParagraphSeparator);
    simAll->setStatusTip(tr("executes simulation of whole scheme"));
    connect(simAll, &QAction::triggered, this, &MainWindow::simulateAll);

    simStep = menuBar()->addAction(tr("&Simulate step"));
    simStep->setShortcuts(QKeySequence::MoveToNextChar);
    simStep->setStatusTip(tr("performs single step of simulation"));
    connect(simStep, &QAction::triggered, this, &MainWindow::simulateStep);

    simReset = menuBar()->addAction(tr("&Reset simulation"));
    simReset->setShortcuts(QKeySequence::MoveToNextChar);
    simReset->setStatusTip(tr("reset simulation process"));
    connect(simReset, &QAction::triggered, this, &MainWindow::resetSim);
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
    buttonMover = new QPushButton("Mover");
    connect(buttonMover, SIGNAL(clicked()), signalMapper, SLOT(map()));
    buttonDestructor = new QPushButton("Destructor");
    connect(buttonDestructor, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper -> setMapping (buttonAND, ITEM_AND);
    signalMapper -> setMapping (buttonNAND, ITEM_NAND);
    signalMapper -> setMapping (buttonOR, ITEM_OR);
    signalMapper -> setMapping (buttonXOR, ITEM_XOR);
    signalMapper -> setMapping (buttonADD, ITEM_ADD);
    signalMapper -> setMapping (buttonSUB, ITEM_SUB);
    signalMapper -> setMapping (buttonGT, ITEM_GT);
    signalMapper -> setMapping (buttonLT, ITEM_LT);
    signalMapper -> setMapping (buttonLinker, ITEM_LINKER);
    signalMapper -> setMapping (buttonMover, ITEM_MOVER);
    signalMapper -> setMapping (buttonDestructor, ITEM_DESTRUCTOR);

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(selectItem(int)));

    output = new QLabel(tr(""));
    output->setStyleSheet("QLabel {background-color: #ffffff;}");

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
    layout->addWidget(buttonMover);
    layout->addWidget(buttonDestructor);
    layout->addWidget(output);

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
