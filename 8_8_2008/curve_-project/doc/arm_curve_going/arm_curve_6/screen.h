#ifndef SCREEN_H
#define SCREEN_H

#include <qframe.h>
#include <qvector.h>
#include <qpixmap.h> 
#include <qpainter.h>

#define FrameWidth          3 
#define Step                5  
#define BaseFontHeight      20 
#define BaseLineLenght      5  
#define SpaceMargin         5


class QRect;
class QString;

class Screen : public QFrame {
        Q_OBJECT
public:
        Screen( QWidget *parent=0, const char *name=0, WFlags flags=0 );
        void animate( double y);
        void setXTitle( QString str );
        void setYTitle( QString str );
protected:
           void initNumber( void );
          void initCordinate( QPainter &p );
        void updateCurve( QPainter &p );
        virtual void showEvent ( QShowEvent * );
        virtual void hideEvent ( QHideEvent * );
        QSize minimumSize () const;
public:  
        double newY, oldY;
        int numXTicks, numYTicks;
        QVector< double > Yval;
        bool firstShow;
        int sec, min, hour;
        QPixmap saveBuffer, newBuffer, midBuffer;
        QRect rectCordinate;
        QRect fromSaveRect;
        QRect toNewRect;
        QRect rectYText;
        QRect rectXText;
        /*We use this painter to draw evering on the newbuffer.*/
        QPainter drawPainter;
        QString stringYTitle;
        QString stringXTitle;
};
#endif /*SCREEN_H*/
