#include "display.h"
#include <qtextstream.h>
#include <qlayout.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qfile.h>
#include <qpainter.h>
#include <iostream>
#include "./xpm/good.xpm"
#include "./xpm/start.xpm"
using namespace std;
                                                                             
                                                                                
QStringList strlist;
QStringList ::Iterator it;

DisplayWidget::DisplayWidget():QWidget()//0,0,WStyle_Customize|WStyle_NoBorder)
{
	QVBoxLayout *vbox = new QVBoxLayout( this, 10 );
	QHBoxLayout *hbox = new QHBoxLayout( vbox );
	lineEdit = new QLineEdit(this);
	lineEdit->setReadOnly( TRUE );
	hbox->addWidget( lineEdit );
	screen1 = new Screen( this ); 
	vbox->addWidget( screen1 ); 
     	startButton = new QPushButton( this );
//	startButton->setPixmap(QPixmap(start_xpm));
	startButton->setText(tr("Start"));
	stopButton = new QPushButton( this );
	stopButton->setText( tr( "Stop" ) );
	hbox->addWidget( startButton );
	hbox->addWidget( stopButton );
	peter_fullscreenshow();
	connect( startButton, SIGNAL( clicked () ), SLOT( start() ) );
	connect( stopButton, SIGNAL( clicked () ), SLOT( stop() ) );
	time = 0;
	yval = 0.0;
//	setBackgroundColor(blue);
	readFile();
}

void DisplayWidget::run()
{
	timer = new QTimer( this );
	connect( timer, SIGNAL( timeout() ), SLOT( tick() ) );                      	timer->start( 500 );
}                                                                        
                                                                                
void DisplayWidget::tick()
{       
	yval = readCurveData();
	screen1->animate( yval );
	lineEdit->setText( QString::number( yval ) );
}

void DisplayWidget::stop()
{
	timer->stop();
	close();
}
                                                                                

void DisplayWidget::start()
{

	run();
}

QSize DisplayWidget::sizeHint() const
{
	return QSize( 16 * Margin, 12 * Margin );
}                                                                                
void DisplayWidget::peter_fullscreenshow()
{
	showFullScreen();
}

void DisplayWidget::readFile()
{
        QFile file("in.txt");
        file.open(IO_ReadOnly);
        QTextStream in(&file);      
        str = in.read();
	strlist = QStringList::split(" ", str);
        it = strlist.begin();


}
double DisplayWidget::readCurveData()
{
        QString tempStr;
        double tempDate;
        
      tempStr =(QString) *it;
      tempDate = tempStr.toDouble();
       if (it != strlist.end())
        {        
                ++it;
        }

        else
        {
                it = strlist.begin();
        }
                return tempDate;
}
