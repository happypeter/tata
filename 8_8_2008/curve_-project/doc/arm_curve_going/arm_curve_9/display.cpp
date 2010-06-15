#include "display.h"
#include "screen.h"

#include <qlayout.h>
#include <qtimer.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qpushbutton.h>
#include <qfile.h>
#include <iostream>
using namespace std;


DisplayWidget::DisplayWidget( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
    timer = 0;

    QVBoxLayout *vbox = new QVBoxLayout( this, 10 );

    QHBoxLayout *hbox = new QHBoxLayout( vbox );
    screen1 = new Screen( this ); 
        screen1->setYTitle( QObject::tr( "Vlure 1" ) );
        vbox->addWidget( screen1 );
    lineEdit = new QLineEdit(this);
        lineEdit->setReadOnly( TRUE );
        hbox->addWidget( lineEdit );


        startButton = new QPushButton( this );
        startButton->setText( tr( "&Start" ) );
        stopButton = new QPushButton( this );
        stopButton->setText( tr( "Sto&p" ) );
        hbox->addWidget( startButton );
        hbox->addWidget( stopButton );
        connect( startButton, SIGNAL( clicked () ), SLOT( start() ) );
        connect( stopButton, SIGNAL( clicked () ), SLOT( stop() ) );
        time = 0;
        yval = 0.0;
        readFile();
}
void DisplayWidget::run()
{
    if ( !timer ) {
        timer = new QTimer( this );
        connect( timer, SIGNAL( timeout() ), SLOT( tick() ) );
    }

    timer->start( 1000 );
}


void DisplayWidget::tick()
{
        yval = readCurveData();
            screen1->animate( yval );
           lineEdit->setText( QString::number( yval ) );
}

void DisplayWidget::start()
{
        run();
}
void DisplayWidget::stop()
{
        timer->stop();
}

QSize DisplayWidget::sizeHint() const
{
        return QSize( 16 * Margin, 12 * Margin );
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
double DisplayWidget::readCurveData( )
{
        QString tempStr;
        double tempData;
        

        tempStr =(QString) *it;
        tempData = tempStr.toDouble();
        
        if (it != strlist.end())
        {        
                ++it; 
        }
        else
        {
                it = strlist.begin();
                  
        }
               return tempData;
}
