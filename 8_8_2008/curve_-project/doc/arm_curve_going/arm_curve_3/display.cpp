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
//#include <cstdlib>
#include <iostream>
using namespace std;


DisplayWidget::DisplayWidget( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
    timer = 0;

    QVBoxLayout *vbox = new QVBoxLayout( this, 10 );

    QHBoxLayout *hbox = new QHBoxLayout( vbox );
    screen1 = new Screen( this ); 
    screen2 = new Screen( this ); 
    screen3 = new Screen( this ); 
    vbox->addWidget( screen1 );
    vbox->addWidget( screen2 );
    vbox->addWidget( screen3 );
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
}

void DisplayWidget::start()
{
       printf("run slot\n");
}
void DisplayWidget::stop()
{
       printf("stop slot\n");
}

QSize DisplayWidget::sizeHint() const
{
        return QSize( 16 * Margin, 12 * Margin );
}

