#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPalette>
#include <iostream>

#include "popup.h"

using namespace std;

Frame::Frame(QWidget* parent, const char* name)
	:  QFrame(parent, Qt::FramelessWindowHint)
{
	button1 = new QPushButton;
	button2 = new QPushButton;
	button3 = new QPushButton;

	connect ( button1, SIGNAL( clicked() ), SLOT( button1Clicked() ) );
	connect ( button2, SIGNAL( clicked() ), SLOT( button2Clicked() ) );
	connect ( button3, SIGNAL( clicked() ), SLOT( button3Clicked() ) );

	QHBoxLayout * l = new QHBoxLayout( this );
	m_processFileReader = new QProcess(this);

        button1->setText(tr("Start"));
	button2->setText(tr("FileReader"));
	button3->setText(tr("Close"));
	button1->setFlat(TRUE);
	button2->setFlat(TRUE);
	button3->setFlat(TRUE);

	QPalette palette;
	palette.setColor( button1->backgroundRole(), Qt::black );
	button1->setPalette( palette );
	button2->setPalette( palette );
	button3->setPalette( palette );

	l->addWidget(button1);
	l->addWidget(button2);
	l->addWidget(button3);

	button1->resize(50,50);
	button2->resize(50,50);
	button2->resize(50,50);

	setPalette( palette );

	setLayout( l );

// center Frame widget on the desktop
	QRect scr_size = QApplication::desktop()->screenGeometry();
	move( scr_size.width()/2 - size().width()/2,
	      scr_size.height()/2 - size().height()/2 );

	resize(640,480);

//	QPixmap pix(desktop_xpm);
//	setBackgroundPixmap(pix);
//	display = new DisplayWidget;
}
Frame::~Frame()
{
	if(m_processFileReader)
	{
		delete m_processFileReader;
	}
}
void Frame::button1Clicked()
{
	display=new DisplayWidget;
	display->show();
//	display->peter_fullscreenshow();
}
                                                                                
void Frame::button2Clicked()
{
	QString program = "/bin/ls";
	QStringList arguments;
	arguments << "-l";
	m_processFileReader->start(program, arguments);

}
                                                                                
void Frame::button3Clicked()
{
	close();
}


