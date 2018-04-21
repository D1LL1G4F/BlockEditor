#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QSignalMapper>
#include <QAction>
#include <vector>
#include <QDebug>
#include "canvas.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

   static const int ITEM_AND;
   static const int ITEM_NAND;
   static const int ITEM_OR;
   static const int ITEM_XOR;
   static const int ITEM_ADD;
   static const int ITEM_SUB;
   static const int ITEM_GT;
   static const int ITEM_LT;
   static const int ITEM_LINKER;

   int getSelectedItem();

private slots:

   void saveScheme();
   void deleteScheme();
   void loadScheme();
   void selectItem(int);
   void simulateAll();
   void simulateStep();



private:
   void createMenu();
   void createButtons();
   void createCanvas();

   int selectedItem;

   Canvas *canvas;

   QGraphicsView *view;
   QMenu *load;
   std::vector<QAction*> savedSchemes;
   QAction *save;
   QAction *del;
   QAction *simAll;
   QAction *simStep;
   QPushButton *buttonAND;
   QPushButton *buttonOR;
   QPushButton *buttonXOR;
   QPushButton *buttonNAND;
   QPushButton *buttonADD;
   QPushButton *buttonSUB;
   QPushButton *buttonGT;
   QPushButton *buttonLT;
   QPushButton *buttonLinker;

};

#endif // MAINWINDOW_H
