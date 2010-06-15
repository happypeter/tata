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
    : QFrame( parent, name, flags | WNoAutoErase )  
{
        setLineWidth( FrameWidth );        
        setFrameStyle( Panel | Sunken );
        setBackgroundMode( PaletteBase );        
        setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
        firstShow = TRUE;
        
}

void Screen::showEvent( QShowEvent *e )
{
        if ( firstShow )
                initNumber();
        initCordinate( drawPainter );
}

QSize Screen::minimumSize () const
{
        return QSize( 20 * SpaceMargin,  20 * SpaceMargin );
}

void Screen::hideEvent( QHideEvent *e )
{
        firstShow = FALSE;
}

void Screen::setXTitle(  QString &str )
{
        stringXTitle = str;
}
void Screen::setYTitle( QString &str )
{
        stringYTitle = str;
}
void Screen::initNumber( )
{
        saveBuffer.resize( size() );     
        saveBuffer.fill( this, 0, 0 );                
        newBuffer.resize( size() );
        newBuffer.fill( this, 0, 0 ); 
        midBuffer.resize( size() );
        midBuffer.fill( this, 0, 0 );
        
        drawPainter.begin(&newBuffer);
        QRect newWindow = drawPainter.window();

        newY = 0;
        oldY =0; 

        sec = 0;
        min = 0;
        hour = 0;
        
        stringXTitle = QObject::tr( "Time (hh:mm:ss)" );
        Yval.push_back( (double)oldY );
               
/*曲线要在下面这个矩形里面*/
       
 rectCordinate.setRect( 
                        newWindow.topLeft().x()+FrameWidth + 2 * BaseFontHeight + 2 * BaseLineLenght, 
                newWindow.topLeft().y()+FrameWidth + 2 * SpaceMargin,
                newWindow.width() - 2 * ( FrameWidth + BaseFontHeight + BaseLineLenght + SpaceMargin ),
                newWindow.height() - 2 * ( FrameWidth + BaseFontHeight + BaseLineLenght + SpaceMargin ) );
               
 /*下面这几步是让矩形的高和宽变成5个像素的倍数，是为了好看点*/
        if ( 0 != ( rectCordinate.width() % (Step*Step) ) )
        {
                int x = rectCordinate.width() % ( Step * Step );        //( (int) sqrt( (float) Step ) );
                rectCordinate.setWidth( rectCordinate.width() - x+1 );
        }

        if ( 0 != ( rectCordinate.height() % (Step*Step) ) )
        {
                int y = rectCordinate.height() % (Step*Step);                                rectCordinate.setHeight( rectCordinate.height() - y+1 );
        }
        numXTicks = rectCordinate.width() / Step;
        numYTicks = rectCordinate.height() / Step;
                 /*rectYText是用写y轴标题的矩形范围*/
        rectYText.setRect( 
                        newWindow.topLeft().x() + FrameWidth,
                        newWindow.topLeft().y() + FrameWidth + 2 * SpaceMargin,
                        BaseFontHeight, rectCordinate.height() );
                 /*rectXText是用写x轴标题的矩形范围*/
        rectXText.setRect(
                rectCordinate.bottomLeft().x(), 
                newWindow.bottomLeft().y() - FrameWidth - BaseFontHeight,
                rectCordinate.width(), BaseFontHeight );
                /*fromSaveRect和toNewRect是用来剪切三张QPixmap上曲线的范围的矩形大小，可以显示曲线与坐标的移动*/
        fromSaveRect.setRect( 
                rectCordinate.topLeft().x() + Step,
                rectCordinate.topLeft().y() + 1,
                rectCordinate.width() - Step - 1,
                rectCordinate.height() + 2 * BaseLineLenght + BaseFontHeight );
        toNewRect.setRect(
                rectCordinate.topLeft().x() + 1,
                rectCordinate.topLeft().y() + 1,
                rectCordinate.width() - Step - 1,
                rectCordinate.height() + 2 * BaseLineLenght + BaseFontHeight );
        drawPainter.drawRect(toNewRect);
                
}

void Screen::initCordinate( QPainter &pCordinate )/初始化坐标系
{
  if ( firstShow )
  {        
        pCordinate.setPen( Qt::blue );
        pCordinate.drawRect( rectCordinate );
        
        /*画y轴的刻度、坐标值和标题*/
        int y0 = rectCordinate.bottomLeft().y();
        int x0 = rectCordinate.bottomLeft().x();
        int yText = 0;
        int xText= 0;
        for (int j = 0; j <= numYTicks; j ++ )
        {
                pCordinate.drawLine( x0 - BaseLineLenght, y0, x0, y0 );
                if (0 == j % Step )
                {
                        pCordinate.drawLine( x0 - 2 * BaseLineLenght, y0, x0 - BaseLineLenght, y0 );
                        pCordinate.save();
                        pCordinate.setPen( QPen( blue, 1, DotLine) );
                        pCordinate.drawLine( x0 , y0, rectCordinate.bottomRight().x(), y0 );
                        pCordinate.restore();
                        pCordinate.setPen( Qt::black );

                        
                        pCordinate.drawText( 
                                x0 - 2 * BaseLineLenght - BaseFontHeight,
                                y0 - 2 * BaseFontHeight + 5 * Step, 
                                BaseFontHeight, BaseFontHeight + Step, 
                                AlignCenter , QString::number( yText) );
                                yText ++;
                        pCordinate.setPen( Qt::blue );
                }
                y0 -= Step;
        }
        
        /*画y轴的标题*/
        pCordinate.save();

        QRect tempYText( 
                rectYText.topLeft().x(), rectYText.topLeft().y(),
                rectYText.height(), rectYText.height() );
        pCordinate.setViewport( tempYText );
        QRect rectYViewport = pCordinate.viewport();
        pCordinate.setWindow( -(int)rectYViewport.width()/2, -(int)rectYViewport.height()/2,
        rectYViewport.width(), rectYViewport.height() );
        QRect rectYWindow = pCordinate.window();
        QRect rectDrawText( 
                rectYWindow.topLeft().x(),
                -(int)rectYText.width()/2,
                rectYText.height(), 
                rectYText.width() );
        pCordinate.rotate(-90.0);
        double dy = ( rectYWindow.width() - rectDrawText.height() ) / 2;
        dy = dy > 0 ? dy : ( -dy );
        pCordinate.translate( 0, -dy );
        pCordinate.drawText( 
                rectDrawText.topLeft().x(), 
                rectDrawText.topLeft().y(), 
                rectDrawText.width(), 
                rectDrawText.height(),
                AlignCenter, stringYTitle );
        pCordinate.restore();

        /*画x轴的刻度和标题*/
        pCordinate.setPen( Qt::blue );
        y0 = rectCordinate.bottomLeft().y();
        for ( int i = 0; i <= numXTicks; i ++ )
        {
                pCordinate.drawLine( x0 , y0, x0, y0 + BaseLineLenght );
                if ( 0 == i % (2*Step) )
                {
                     pCordinate.save();
                     pCordinate.setPen( QPen( blue, 1, DotLine) );
                     pCordinate.drawLine( x0 , rectCordinate.bottomLeft().y(), 
                     x0 , rectCordinate.topLeft().y() );
                     pCordinate.restore();
                }

                x0 += Step;
        }
        
        /*画x轴的标题*/
        pCordinate.drawText(
                               rectXText.topLeft().x(), rectXText.topLeft().y(),
                       rectXText.width(), rectXText.height(),
                       AlignCenter, stringXTitle );
                        
  }
         /*将初始化好的坐标系复制到Screen部件上*/
          bitBlt( this, 0, 0, &newBuffer, 0, 0, newBuffer.width(), newBuffer.height() );
        
}



void Screen::animate( double y )
{
        
        newY = y;
        if ( (int) Yval.size() <= (int) width() / 4 )
        {
                Yval.append( newY );
        } else {
                Yval.erase( Yval.begin() );
                Yval.append( newY );
        }
        
        updateCurve( drawPainter);

}
/*更新曲线，实现曲线和坐标的移动*/
void Screen::updateCurve( QPainter &pDrawCurve)
{
/*设计思路：三个QPixmap，其中newBuffer是用于画图和复制给Screen的，saveBuffer是用于保存上次newBuffer，midBuffer从saveBuffer中将需要往前移动的部分剪切到自己上面，最后newBuffer从midBuffer上将移动的部分加上需要的空白复制到自己绘图矩形内，实现了曲线和坐标向前移动，最后在空白出画上最新的坐标，曲线和时间*/
        copyBlt ( &saveBuffer, 0, 0,&newBuffer, 0, 0, newBuffer.width(), newBuffer.height() );
        copyBlt ( &midBuffer, toNewRect.topLeft().x(), toNewRect.topLeft().y(),
                             &saveBuffer, fromSaveRect.topLeft().x(), fromSaveRect.topLeft().y(), 
                     fromSaveRect.width(), fromSaveRect.height() );
        copyBlt ( &newBuffer, rectCordinate.topLeft().x()+1, rectCordinate.topLeft().y()+1,
                     &midBuffer, rectCordinate.topLeft().x()+1, rectCordinate.topLeft().y()+1, 
                      rectCordinate.width()-2, fromSaveRect.height() );
        

        QValueVector<double>::iterator Yit = Yval.end();
        double Ynew, Yold;
        int Xnew, Xold;
        Ynew = rectCordinate.bottomRight().y() - *(--Yit) - 1;
        Xnew = rectCordinate.bottomRight().x() -1;
        Yold = rectCordinate.bottomRight().y() - *(--Yit) - 1;
        Xold = rectCordinate.bottomRight().x() - Step;
        
        
        
        /*画移动后空白处的横坐标和刻度*/
        pDrawCurve.setPen( Qt::blue );
        pDrawCurve.drawLine( 
                toNewRect.bottomRight().x(), rectCordinate.bottomRight().y(),
                rectCordinate.bottomRight().x(), rectCordinate.bottomRight().y() );                pDrawCurve.drawLine(                
                toNewRect.bottomRight().x(), rectCordinate.bottomRight().y(),
                toNewRect.bottomRight().x(), rectCordinate.bottomRight().y() + BaseLineLenght );
        
        /*draw the dotline in the horizontal direction*/
        int y0 = rectCordinate.bottomRight().y();
        static bool drawDotLine = FALSE;
        pDrawCurve.save();
        if ( drawDotLine )
        {
                for (int j =0; j < (numYTicks /5 -1 ); j++)
                {
                      y0 -= 5*Step;
                     pDrawCurve.setPen( QPen( blue, 1, DotLine) );
                     pDrawCurve.drawLine( toNewRect.bottomRight().x() , y0, 
                             rectCordinate.bottomRight().x(), y0 );
                }
        }
        pDrawCurve.restore();
        drawDotLine = !drawDotLine;

        /*draw the calibration values of x-axis*/
        static int numX = 0;
        if ( 0 == numX % (2*Step) )
        {
                /*以hh:mm:ss的格式画时间*/
                int low = hour % 10;
                int high = hour / 10;
                QString timeString;        
                timeString += ( QString( "%1%2:").arg(high).arg(low) );
                low = min % 10;
                high = min / 10;
                timeString += ( QString( "%1%2:").arg(high).arg(low) );
                low = sec % 10;
                high = sec / 10;
                timeString += ( QString( "%1%2").arg(high).arg(low) );                

                /*draw the long calibration */
                pDrawCurve.drawLine( 
                        toNewRect.bottomRight().x(), 
                        rectCordinate.bottomRight().y() + BaseLineLenght,
                        toNewRect.bottomRight().x(), 
                        rectCordinate.bottomRight().y() + 2 * BaseLineLenght );

                /*draw the dotline in the vertical direction*/
                pDrawCurve.save();
                pDrawCurve.setPen( QPen( blue, 1, DotLine) );
                pDrawCurve.drawLine( 
                        toNewRect.bottomRight().x(), 
                        rectCordinate.bottomRight().y(), 
                        toNewRect.topRight().x(),
                        rectCordinate.topRight().y() );
                pDrawCurve.restore();
        
                /*draw the calibration values of x-axis*/
                if ( 0 == numX % (4*Step) )
                {
                       pDrawCurve.drawLine( 
                        toNewRect.bottomRight().x(), 
                        rectCordinate.bottomRight().y() + 2*BaseLineLenght,
                        toNewRect.bottomRight().x(), 
                        rectCordinate.bottomRight().y() + 3 * Step );
                        
                     pDrawCurve.setPen( Qt::black );
                                /*画时间的矩形范围*/
                    QRect rectCValue(
                        toNewRect.bottomRight().x() - 9 * Step,
                        toNewRect.bottomRight().y() - BaseFontHeight+2,
                        10 * Step, 
                        BaseFontHeight);
                     pDrawCurve.drawText( 
                        rectCValue.topLeft().x(), 
                        rectCValue.topLeft().y(), 
                        rectCValue.width(), 
                                rectCValue.height(),
                        AlignRight | Qt::AlignHCenter, 
                        timeString );
                }
                sec += 10;
                if ( 60 == sec )
                {
                        sec = 0;
                        min += 1;
                        if ( 60 == min )
                        {
                                min = 0;
                                hour += 1;
                                if ( 60 == hour )
                                        hour = 0;
                        }
                }
                

        }
        numX ++;
        if ( numX >= 100 )
                numX = 0;
        

        /*更新曲线，便且将曲线复制到Screen上显示*/
        pDrawCurve.setPen( Qt::black );
        pDrawCurve.drawLine( Xold, (int)Yold, Xnew, (int)Ynew );
        bitBlt( this, 0, 0, &newBuffer, 0, 0, newBuffer.width(), newBuffer.height() );
        
}
