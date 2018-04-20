#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

private slots:

   void saveScheme();
   void deleteScheme();
   void loadScheme();
   void addBlock();
   void addLinker();
   void simulateAll();
   void simulateStep();
   void exit();



private:
   void createMenu();
   void createButtons();
   void createCanvas();

   QMenu *loadMenu;
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
