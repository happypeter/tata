#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <QWidget>
#include <QFrame>
#include <QPixmap> 
#include <QPainter>
#include <QRect>
#include <QString>

#define FrameWidth          3 
#define Step                5  
#define BaseFontHeight      10
#define BaseLineLenght      5
#define SpaceMargin         5

class Screen : public QFrame
{
    Q_OBJECT
    
public:
    Screen( QWidget *parent = 0 );
   
    void animate( double y );
    void set_animate( bool b );
    void setXTitle( QString str );
    void setYTitle( QString str );
    void drawCurve();    
    void refreshPixmap();	   
protected:
    void initNumber(QPainter &painter);
    void drawCordinate(QPainter &painter);
//    virtual void showEvent ( QShowEvent * );
//    virtual void hideEvent ( QHideEvent * );
     void paintEvent( QPaintEvent * );
     void resizeEvent( QResizeEvent * );
     QSize minimumSizeHint() const;
	
private:  
    double Yold, Ynew;
    int numXTicks, numYTicks;
    bool firstShow, m_animate;
    QPixmap newPixmap,savePixmap,midPixmap;
    int sec, min, hour;
    QRect rectCordinate;
    QRect fromSaveRect;
    QRect toNewRect;
    QRect rectXText;
    QRect rectYText;
    QVector<double> Yval;
    QPainter painter;
    QString stringYTitle;
    QString stringXTitle;
};


#endif // SCREEN_HPP
