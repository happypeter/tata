#include "display.h"


#include <qlayout.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <iostream>
using namespace std;


DisplayWidget::DisplayWidget( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
    
    QVBoxLayout *vbox = new QVBoxLayout( this, 10 );

    QHBoxLayout *hbox = new QHBoxLayout( vbox );
        lineEdit = new QLineEdit(this);
        lineEdit->setReadOnly( TRUE );
        hbox->addWidget( lineEdit );


        startButton = new QPushButton( this );
        startButton->setText( tr( "&Start" ) );
        stopButton = new QPushButton( this );
        stopButton->setText( tr( "Sto&p" ) );
   
        hbox->addWidget( startButton );
        hbox->addWidget( stopButton );

}


