#include "screen.h"

#include <qevent.h>
#include <qrect.h>
#include <qsize.h>
#include <qstring.h>
#include <iostream>
using namespace std;
#include <qwmatrix.h> 
#include <qfont.h>
#include <qpen.h>

Screen::Screen(  QWidget *parent, const char *name, WFlags flags )
    : QFrame( parent, name, flags )  
{
        setLineWidth( FrameWidth );        
        setFrameStyle( Panel | Sunken );
        setBackgroundMode( PaletteBase );        

        
}

