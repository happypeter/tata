#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include <QRect>
#include <QSize>
#include <QString>
#include <iostream>
#include <QFont>
#include <QPen>

#include "screen.hpp"

using namespace std;

Screen::Screen( QWidget *parent )
	: QFrame( parent ),
	firstShow( true ),
	m_animate( false )
{
	setLineWidth( FrameWidth );        
	setFrameStyle( Panel | Sunken );
	setBackgroundRole( QPalette::Base );
	firstShow = true;
	QPalette palette;
	palette.setColor( backgroundRole(), Qt::black);
	setPalette(palette);
}


void Screen::set_animate( bool b )
{
	m_animate = b;
}
void Screen::paintEvent( QPaintEvent *e )
{
	cout << "Screen::paintEvent...\n" << endl;
	if( m_pixmap.isNull() )
	{
		m_pixmap = QPixmap( size() );
	}
	painter.begin( &m_pixmap );
	if(firstShow)
	{	
		firstShow=false;
		initNumber();
		initCordinate();
	}
	if( m_animate )
	{	
		cout << "m_animate==true, running updateCurve\n" << endl;
		updateCurve( );
	}
	painter.end();
	// copy backing pixmap to screen
	QPainter painter( this );
	painter.drawPixmap( 0, 0, m_pixmap );
}

void Screen::resizeEvent( QResizeEvent *e )
{
//	cout << "Screen::resizeEvent.....\n";
	m_pixmap = QPixmap( size() );
	m_pixmap.fill();
	update();
}

QSize Screen::minimumSize () const
{
	return QSize( 20 * SpaceMargin,  20 * SpaceMargin );
}

void Screen::setXTitle(  QString str )
{
	stringXTitle = str;
}
void Screen::setYTitle( QString str )
{
	stringYTitle = str;
}

void Screen::initNumber( )
{
	cout<<"initNumber()"<<endl;
	QRect newWindow = painter.window();
	newY = 0;
	oldY =0;
	sec = 0;
	min = 0;
	hour = 0;

    	stringXTitle = QObject::tr( "Time (hh:mm:ss)" );
	//rectCordinate is the rect area of the Cordinate, including the axises.
	rectCordinate.setRect( 	newWindow.topLeft().x()+FrameWidth + 2 * BaseFontHeight 
				+ 2 * BaseLineLenght,newWindow.topLeft().y() 
				+ FrameWidth + 2 * SpaceMargin,
				newWindow.width() 
				- 2 * ( FrameWidth + BaseFontHeight + BaseLineLenght + SpaceMargin),
				newWindow.height() 
				- 2 * ( FrameWidth + BaseFontHeight + BaseLineLenght + SpaceMargin ) );
           
	if ( 0 != ( rectCordinate.width() % (Step*Step) ) )
	{
		int x = rectCordinate.width() % ( Step * Step );     
		rectCordinate.setWidth( rectCordinate.width() - x+1 );
	}

	if ( 0 != ( rectCordinate.height() % (Step*Step) ) )
	{
		int y = rectCordinate.height() % (Step*Step);                                
		rectCordinate.setHeight( rectCordinate.height() - y+1 );
	}
	numXTicks = rectCordinate.width() / Step;
	numYTicks = rectCordinate.height() / Step;   
	
	rectYText.setRect( 
			newWindow.topLeft().x() + FrameWidth,
			newWindow.topLeft().y() + FrameWidth + 2 * SpaceMargin,
			BaseFontHeight, rectCordinate.height() );
           
	rectXText.setRect(
			rectCordinate.bottomLeft().x(), 
			newWindow.bottomLeft().y() - FrameWidth - BaseFontHeight,
			rectCordinate.width(), BaseFontHeight );
           
	fromSaveRect.setRect( 
			rectCordinate.topLeft().x() + Step,
			rectCordinate.topLeft().y() + 1,
			rectCordinate.width() - Step - 1,
			rectCordinate.height() + 2 * BaseLineLenght + BaseFontHeight );
	toNewRect.setRect(
	//toNewRect is the rect area we cut and moved left
		rectCordinate.topLeft().x() + 1,
		rectCordinate.topLeft().y() + 1,
		rectCordinate.width() - Step - 1,
		rectCordinate.height() + 2 * BaseLineLenght + BaseFontHeight );
//peter	painter.drawRect(toNewRect);
}

void Screen::initCordinate()
{
	cout<<"void Screen::initCordinate()"<<endl;    
	painter.setPen( Qt::blue );
	painter.drawRect( rectCordinate );
	//one debugging trick is you can comment out the above line, 
	//then you can see what is the real area of rectCordinate 	
	int y0 = rectCordinate.bottomLeft().y();
	int x0 = rectCordinate.bottomLeft().x();
	int yText = 0;
//	int xText= 0;
        for (int j=0; j<=numYTicks; j++ )
        {
                painter.drawLine( x0-BaseLineLenght, y0, x0, y0 );
                if (0==j%Step )
                {
                        painter.drawLine( x0 - 2 * BaseLineLenght, y0, x0 - BaseLineLenght, y0 );
                        painter.save();
                        painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
                        painter.drawLine( x0 , y0, rectCordinate.bottomRight().x(), y0 );
                        painter.restore();
                        painter.setPen( Qt::red );
                        painter.drawText( x0 - 2 * BaseLineLenght - BaseFontHeight ,
                        			y0 - 2 * BaseFontHeight + 5 * Step ,
                        			BaseFontHeight ,
                        			BaseFontHeight + Step ,
                        			Qt::AlignCenter ,
                        			QString::number( yText) );
                        yText ++;
                        painter.setPen( Qt::blue );
                }
                y0 -= Step;
        }
        
        painter.save();

        QRect tempYText( 
                rectYText.topLeft().x(), rectYText.topLeft().y(),
                rectYText.height(), rectYText.height() );
        painter.setViewport( tempYText );
        QRect rectYViewport = painter.viewport();
        painter.setWindow( -(int)rectYViewport.width()/2, -(int)rectYViewport.height()/2,
        rectYViewport.width(), rectYViewport.height() );
        QRect rectYWindow = painter.window();
        QRect rectDrawText( 
                rectYWindow.topLeft().x(),
                -(int)rectYText.width()/2,
                rectYText.height(), 
                rectYText.width() );
        painter.rotate(-90.0);
        double dy = ( rectYWindow.width() - rectDrawText.height() ) / 2;
        dy = dy > 0 ? dy : ( -dy );
        painter.translate( 0, -dy );
        painter.drawText( 
                rectDrawText.topLeft().x(), 
                rectDrawText.topLeft().y(), 
                rectDrawText.width(), 
                rectDrawText.height(),
                Qt::AlignCenter, stringYTitle );
        painter.restore();

      
        painter.setPen( Qt::blue );
        y0 = rectCordinate.bottomLeft().y();
        for ( int i = 0; i <= numXTicks; i ++ )
        {
                painter.drawLine( x0 , y0, x0, y0 + BaseLineLenght );
                if ( 0 == i % (2*Step) )
                {
                     painter.save();
                     painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
                     painter.drawLine( x0 , rectCordinate.bottomLeft().y(), 
                     x0 , rectCordinate.topLeft().y() );
                     painter.restore();
                }

                x0 += Step;
        }
        
         painter.drawText( rectXText.topLeft().x(), rectXText.topLeft().y(),
 	                          rectXText.width(), rectXText.height(),
 	                          Qt::AlignCenter, stringXTitle );

}



void Screen::animate( double y )
{
        
	Ynew=y;
	/*       
	if ( (int) Yval.size() <= (int) width() / 4 )
	{
		Yval.append( newY );
	} 
	else 
	{
		Yval.erase( Yval.begin() );
		Yval.append( newY );
	//the y here is the value in in.txt, so when animate() is executed, the value
	//in in.txt become a element of vector Yval.
	}        
	*/
}

void Screen::updateCurve()
{
//    cout<<"Ynew is now :"<<Ynew<<endl;
	QRectF target(
			rectCordinate.topLeft().x() + 1, 
			rectCordinate.topLeft().y() + 1, 
			rectCordinate.width() - Step - 1, 
			rectCordinate.height()+30);
	
	QRectF source(
                        rectCordinate.topLeft().x() + Step,
                        rectCordinate.topLeft().y() + 1, 
                        rectCordinate.width() - Step - 1, 
                        rectCordinate.height()+30);

  	painter.drawPixmap(target,m_pixmap, source);

        int Xnew, Xold;
        Ynew = rectCordinate.bottomRight().y() - Ynew - 1;
        Xnew = rectCordinate.bottomRight().x() -1;
	//"-1" to avoid the X-axis
        Yold = rectCordinate.bottomRight().y() - Yold- 1;
	//"-1" to avoid the Y-axis
        Xold = rectCordinate.bottomRight().x() - Step;

        painter.setPen( Qt::blue );
        painter.drawLine( toNewRect.bottomRight().x(), rectCordinate.bottomRight().y(),
			  rectCordinate.bottomRight().x(), rectCordinate.bottomRight().y() );                
	painter.drawLine( toNewRect.bottomRight().x(), rectCordinate.bottomRight().y(),
			  toNewRect.bottomRight().x(), rectCordinate.bottomRight().y() + BaseLineLenght );
        
        /*draw the dotline in the horizontal direction*/
        int y0 = rectCordinate.bottomRight().y();

        static bool drawDotLine = false;

        painter.save();
	if ( drawDotLine )
	{
		for (int j =0; j < (numYTicks /5 -1 ); j++)
		{
			y0 -= 5*Step;
			painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
			painter.drawLine( toNewRect.bottomRight().x() , y0, 
			rectCordinate.bottomRight().x(), y0 );
			//draw the X-axis dotline, it works perfectly
		}
	}
	painter.restore();
	drawDotLine = !drawDotLine;

        /*draw the calibration values of x-axis*/
	static int numX = 0;
	if ( 0 == numX % (2*Step) )
	{//since Step==5, so this block will be executed once every 10 times updateCurve() is called
               
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

		/*draw the long calibration---the little line right above the time string */
		painter.drawLine( 
				toNewRect.bottomRight().x(), 
				rectCordinate.bottomRight().y() + BaseLineLenght,
				toNewRect.bottomRight().x(), 
				rectCordinate.bottomRight().y() + 2 * BaseLineLenght );

		/*draw the dotline in the vertical direction*/
		painter.save();
		painter.setPen( QPen( Qt::yellow, 1, Qt::DotLine) );
		cout<<"draw the dotline in the vertical direction"<<endl;
		painter.drawLine( 
				toNewRect.bottomRight().x(), 
				rectCordinate.bottomRight().y(), 
				toNewRect.topRight().x(),
				rectCordinate.topRight().y() );
		painter.restore();

		/*draw the calibration values of x-axis*/
		if ( 0 == numX % (4*Step) )
		{//since Step==5, so this block will be executed once every 20 times updateCurve() is called
			painter.drawLine( 
				toNewRect.bottomRight().x(), 
				rectCordinate.bottomRight().y() + 2*BaseLineLenght,
				toNewRect.bottomRight().x(), 
				rectCordinate.bottomRight().y() + 3 * Step );
                
			painter.setPen( Qt::green );
			//display time in green
       
			QRect rectCValue(
				toNewRect.bottomRight().x() - 10 * Step,
				toNewRect.bottomRight().y() - BaseFontHeight+2,
				10 * Step, 
				BaseFontHeight );
			painter.drawText( 
				rectCValue.topLeft().x(), 
				rectCValue.topLeft().y(), 
				rectCValue.width(), 
				rectCValue.height(),
				Qt::AlignHCenter, 
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

	cout<<"rectCordinate.bottomRight().y()"<<rectCordinate.bottomRight().y()<<endl;
	cout<<"rectCordinate.topRight().y()"<<rectCordinate.topRight().y()<<endl;
	cout<<"Ynew:"<<Ynew<<endl;

        painter.setPen( Qt::red );
	painter.drawLine( Xold, (int)Yold, Xnew, (int)Ynew );
	Yold = rectCordinate.bottomRight().y() - Ynew - 1;
	//this line is used to update Yold with the used Ynew 
}




