/****************************************************************************
** $Id: qt/examples/popup/popup.h   2.3.7   edited 2001-01-26 $
**
** Definition of something or other
**
** Created : 979899
**
** Copyright (C) 1997 by Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef POPUP_H
#define POPUP_H
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "./splash/display.h"


class DisplayWidget;

 class Frame : public QFrame
 {
     Q_OBJECT
 public:
     Frame( QWidget *parent=0, const char*  name=0);

 protected:

 private slots:
	void button1Clicked();
	 void button3Clicked();
     
private:
	QPushButton *button1;
	QPushButton *button2;
	QPushButton *button3;
	DisplayWidget *display;       
 };

#endif
