/*! \file      mainwindow.h
 *  \brief     header file for MainWindow class
 *  \author    Matej Knazik
 *  \date      2018
 */

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

//!  MainWindow class
/*!
  A frontend class representing main UI window (derivate of QMainWindow)
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor
    /*!
      Constructor for MainWindow.
    */
   MainWindow();

   //! constant for AND block
   static const int ITEM_AND = 0;

   //! constant for NAND block
   static const int ITEM_NAND = 1;

   //! constant for OR block
   static const int ITEM_OR = 2;

   //! constant for XOR block
   static const int ITEM_XOR = 3;

   //! constant for ADD block
   static const int ITEM_ADD = 4;

   //! constant for SUB block
   static const int ITEM_SUB = 5;

   //! constant for ">" block
   static const int ITEM_GT = 6;

   //! constant for "<" block
   static const int ITEM_LT = 7;

   //! constant for LINKER
   static const int ITEM_LINKER = 8;

   //! constant for Mover selection
   static const int ITEM_MOVER = 9;

   //! constant for Delete selection
   static const int ITEM_DESTRUCTOR = 10;

   //! return type of currently selected button
   /*!
       \return int representation of selected item
   */
   int getSelectedItem();

   //! Return output screen to display results and other dialogs
   /*!
       \return QLabel of output screen label
   */
   QLabel *getOutputScr();

private slots:

   //! JSON export to file
   void saveScheme();
   //! clears canvas and scheme
   void deleteScheme();
   //! load json representation of scheme
   void loadScheme();
   //! change selected item
   void selectItem(int);
   //! performs simulation of whole scheme
   void simulateAll();
   //! perfroms simulation of singe step in scheme
   void simulateStep();
   //! resets simulation to default state
   void resetSim();



private:

   //! menu creator
   void createMenu();

   //! button bar creator
   void createButtons();

   //! canvas creator
   void createCanvas();

   //! current selected item
   int selectedItem;

   //! central widget
   QWidget *central;
   //! left bar widget
   QWidget *leftBar;
   //! scene widget
   QWidget *scene;

   //! canvas widget
   Canvas *canvas;

   //! view window for canvas
   QGraphicsView *view;

   // top menu bar //

   QAction *save;
   QAction *del;
   QAction *load;
   QAction *simAll;
   QAction *simStep;
   QAction *simReset;

   // ////////////// //


   // left buttons bar //

   QPushButton *buttonAND;
   QPushButton *buttonOR;
   QPushButton *buttonXOR;
   QPushButton *buttonNAND;
   QPushButton *buttonADD;
   QPushButton *buttonSUB;
   QPushButton *buttonGT;
   QPushButton *buttonLT;
   QPushButton *buttonLinker;
   QPushButton *buttonMover;
   QPushButton *buttonDestructor;

   // //////////////// //

   //! output dialog screen
   QLabel *output;


};

#endif // MAINWINDOW_H
