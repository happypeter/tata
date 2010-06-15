#include "display.h"
#include <qlayout.h>
#include <qpushbutton.h>
using namespace std;


DisplayWidget::DisplayWidget( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
    
    QVBoxLayout *vbox = new QVBoxLayout( this, 10 );

    QHBoxLayout *hbox = new QHBoxLayout( vbox );
    
        startButton = new QPushButton( this );
        hbox->addWidget( startButton );
       
}
