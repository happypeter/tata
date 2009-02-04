#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <QWidget>
#include <QFrame>
#include <QPixmap> 
#include <QPainter>

#define FrameWidth          3 
#define Step                5  
#define BaseFontHeight      20 
#define BaseLineLenght      5  
#define SpaceMargin         5

class QRect;
class QString;

class Screen : public QFrame
{
    Q_OBJECT
    
public:
    Screen( QWidget *parent = 0 );
    Screen( const Screen& );

    void animate( double y );
    void set_animate( bool b );
    void setXTitle( QString str );
    void setYTitle( QString str );
    double Yold, Ynew;
    
protected:
    void initNumber( void );
    void initCordinate( );
    void updateCurve( );
//    virtual void showEvent ( QShowEvent * );
//    virtual void hideEvent ( QHideEvent * );
    virtual void paintEvent( QPaintEvent * );
    virtual void resizeEvent( QResizeEvent * );
    QSize minimumSize () const;
	
public:  
    double newY, oldY;
    int numXTicks, numYTicks;
    bool firstShow, m_animate;
    int sec, min, hour;
    QPixmap m_pixmap;
    QRect rectCordinate;
    QRect fromSaveRect;
    QRect toNewRect;
    QRect rectYText;
    QRect rectXText;
    
    // We use this painter to draw evering on the newbuffer
    QPainter painter;
    QString stringYTitle;
    QString stringXTitle;
};


#endif // SCREEN_HPP
