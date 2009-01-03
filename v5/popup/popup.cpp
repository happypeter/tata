/****************************************************************************
** $Id: qt/examples/popup/popup.cpp   2.3.7   edited 2001-06-12 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "popup.h"
#include <qapplication.h>
#include <qkeycode.h>
#include <qlayout.h>
#include <qpixmap.h>
#include <iostream>
using namespace std;
#include "./xpm/desktop.xpm"
#include "./xpm/wave.xpm"
#include "./xpm/setting.xpm"
#include "./xpm/analysis.xpm"
Frame::Frame(QWidget* parent, const char* name): QFrame(parent, name,WStyle_Customize|WStyle_NoBorder)
{
	button1 = new QPushButton( this);
	button2 = new QPushButton(this);
	button3 = new QPushButton(this);
	connect ( button1, SIGNAL( clicked() ), SLOT( button1Clicked() ) );
	connect ( button3, SIGNAL( clicked() ), SLOT( button3Clicked() ) );

	QBoxLayout * l = new QHBoxLayout( this );
        button1->setPixmap(QPixmap(wave_xpm));
	button1->setFlat(TRUE);
	button1->setBackgroundColor(black);
	button3->setPixmap(QPixmap(analysis_xpm));
	button3->setFlat(TRUE);
//	button3->setBackgroundColor(black);
	button3->setText(tr("Close"));
	button2->setPixmap(QPixmap(setting_xpm));
	button2->setFlat(TRUE);
        button2->setBackgroundColor(black);
	l->addWidget(button1);
	l->addWidget(button2);
	l->addWidget(button3);
	button1->resize(50,50);
        button2->resize(50,50);
        button2->resize(50,50);
	setBackgroundColor(black);

	l->activate();
	resize(320,240);
//	QPixmap pix(desktop_xpm);
//	setBackgroundPixmap(pix);
//	display=new DisplayWidget();
}

void Frame::button1Clicked()
{
	display=new DisplayWidget();
	display->peter_fullscreenshow();
}
                                                                                
void Frame::button3Clicked()
{
        close();
}
                                                                                


