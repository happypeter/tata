#ifndef SCREEN_H
#define SCREEN_H

#include <qframe.h>
//#include <qvaluevector.h>
#include <qpixmap.h> 
#include <qpainter.h>

#define FrameWidth          3 
#define Step                5    
#define SpaceMargin         5

class QString;

class Screen : public QFrame {
        Q_OBJECT
public:
        Screen( QWidget *parent=0, const char *name=0, WFlags flags=0 );
        
        
 };
#endif /*SCREEN_H*/
