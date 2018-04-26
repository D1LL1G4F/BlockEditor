#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QSignalMapper>
#include <QAction>
#include <QWidget>
#include <vector>
#include <QDebug>
#include "canvas.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>


class Canvas;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

   static const int ITEM_AND = 0;
   static const int ITEM_NAND = 1;
   static const int ITEM_OR = 2;
   static const int ITEM_XOR = 3;
   static const int ITEM_ADD = 4;
   static const int ITEM_SUB = 5;
   static const int ITEM_GT = 6;
   static const int ITEM_LT = 7;
   static const int ITEM_LINKER = 8;

   int getSelectedItem();
   QLabel *getOutputScr();

private slots:

   void saveScheme();
   void deleteScheme();
   void loadScheme();
   void selectItem(int);
   void simulateAll();
   void simulateStep();
   void resetSim();



private:
   void createMenu();
   void createButtons();
   void createCanvas();

   int selectedItem;

   QWidget *central;
   QWidget *leftBar;
   QWidget *scene;

   Canvas *canvas;

   QGraphicsView *view;
   QMenu *load;
   std::vector<QAction*> savedSchemes;
   QAction *save;
   QAction *del;
   QAction *simAll;
   QAction *simStep;
   QAction *simReset;
   QPushButton *buttonAND;
   QPushButton *buttonOR;
   QPushButton *buttonXOR;
   QPushButton *buttonNAND;
   QPushButton *buttonADD;
   QPushButton *buttonSUB;
   QPushButton *buttonGT;
   QPushButton *buttonLT;
   QPushButton *buttonLinker;
   QLabel *output;


};

#endif // MAINWINDOW_H
