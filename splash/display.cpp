#include <QTextStream>
#include <QLayout>
#include <QFrame>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QPushButton>
#include <QTimer>
#include <QFile>
#include <QPainter>
#include <iostream>

#include "display.h"

using namespace std;
                                                                                
QStringList strlist;
QStringList ::Iterator it;

DisplayWidget::DisplayWidget()
    :  QWidget()
{
	QGridLayout *layout = new QGridLayout;

	lineEdit = new QLineEdit;
	lineEdit->setReadOnly( TRUE );
	layout->addWidget( lineEdit, 0, 0 );

	screen1 = new Screen; 
	layout->addWidget( screen1, 1, 0, 1, 3 ); 

     	startButton = new QPushButton;
	startButton->setText(tr("Start"));
	stopButton = new QPushButton;
	stopButton->setText( tr( "Stop" ) );
	layout->addWidget( startButton, 0, 1 );
	layout->addWidget( stopButton , 0, 2 );

	setLayout(layout);
	connect( startButton, SIGNAL( clicked () ), SLOT( start() ) );
	connect( stopButton, SIGNAL( clicked () ), SLOT( stop() ) );
	QString str;
	str="Y value";
	screen1->setYTitle(str);
	time = 0;
	yval = 0.0;
//	setBackgroundColor(blue);
	readFile();
}

void DisplayWidget::run()
{
	timer = new QTimer( this );
	connect( timer, SIGNAL( timeout() ), SLOT( tick() ) );
      	timer->start( 500 );
}

void DisplayWidget::tick()
{       
	yval = readCurveData();
//	cout<<"yval--------"<<yval<<endl;
	 screen1->animate(yval);
	lineEdit->setText( QString::number( yval ) );      

	screen1->refreshPixmap();
}

void DisplayWidget::stop()
{
	timer->stop();
	screen1->set_animate( false );
//	close();
}

void DisplayWidget::start()
{
	screen1->set_animate( true );
	run();
}

QSize DisplayWidget::sizeHint() const
{
	return QSize( 16 * Margin, 12 * Margin );
}

void DisplayWidget::readFile()
{
        QFile file("in.txt");
        file.open( QIODevice::ReadOnly );

        QTextStream in(&file);      
        str = in.read(1000);
	strlist = str.split(" ");
        it = strlist.begin();
}

double DisplayWidget::readCurveData()
{
        QString tempStr;
        double tempDate;
        
      tempStr =(QString) *it;
      tempDate = tempStr.toDouble();
       if (it != strlist.end()-1)
        {        
                ++it;
            }

        else
        {
                it = strlist.begin();

           }
                return tempDate;
}
