#include <QApplication>
#include <QEvent>
#include <QSize>
#include <iostream>
#include <QFont>
#include <QPen>
#include <QStylePainter>

#include "screen.h"
using namespace std;

Screen::Screen( QWidget *parent )
    : QFrame( parent ),
      firstShow( true ),
      m_animate( false )
{
	setLineWidth( FrameWidth );        
	setFrameStyle( Panel | Sunken );
	setBackgroundRole( QPalette::Base );
	QPalette palette;
	palette.setColor( backgroundRole(), Qt::black);
	setPalette(palette);

        savePixmap=QPixmap( size() );
        savePixmap.fill( this, 0, 0 );
        midPixmap=QPixmap( size() );
        midPixmap.fill( this, 0, 0 );
	sec=0;
	min=0;
	hour=0;
//	refreshPixmap();
}

void Screen::set_animate( bool b )
{
    m_animate = b;
}

void Screen::paintEvent( QPaintEvent * /*event*/ )
{
/*   if( newPixmap.isNull() )
    {
	newPixmap = QPixmap( size() );
    }
    painter.begin( &newPixmap );

    initNumber();
    drawCordinate();

    if ( m_animate )
	drawCurve( );

    painter.end();*/

    QStylePainter painter1( this );
    painter1.drawPixmap( 0, 0, newPixmap);
}

void Screen::resizeEvent( QResizeEvent * /*event*/ )
{
     newPixmap = QPixmap( size() );
     newPixmap.fill(this,0,0);
     refreshPixmap();
 
}

void Screen::refreshPixmap()
{  
	if (! m_animate )
	{
		QPainter painter(&newPixmap);
		painter.initFrom(this);
		initNumber(painter);
		drawCordinate(painter); 
	}
	else
	{
		drawCurve();
	}
  	update();	    
}

QSize Screen::minimumSizeHint() const
{
	return QSize( 20 * SpaceMargin,  20 * SpaceMargin );
}

void Screen::setXTitle(  QString str )
{
	stringXTitle = str;
}

void Screen::setYTitle(  QString str )
{
	stringYTitle = str;
}

void Screen::initNumber(QPainter &painter)
{  
	QRect newWindow = painter.window();
	stringXTitle = QObject::tr( "Time (hh:mm:ss)" );
	rectCordinate.setRect( newWindow.left()+FrameWidth + 2 * BaseFontHeight 
			+ 2 * BaseLineLenght,newWindow.top() + FrameWidth 
			+ 2 * SpaceMargin,newWindow.width() 
			- 2 * ( FrameWidth + BaseFontHeight + BaseLineLenght + SpaceMargin) ,
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
	numXTicks = (rectCordinate.width()-1) / Step;
	numYTicks = (rectCordinate.height()-1) / Step;
           
	rectYText.setRect( 
		newWindow.left() + FrameWidth-10,
		newWindow.top() + FrameWidth + 2 * SpaceMargin,
		BaseFontHeight+5, rectCordinate.height() );
	rectXText.setRect(
		rectCordinate.left(), 
		newWindow.bottom() - FrameWidth - BaseFontHeight,
		rectCordinate.width(), BaseFontHeight );
           
	fromSaveRect.setRect( 
		rectCordinate.left() + Step,
		rectCordinate.top() + 1,
		rectCordinate.width() - Step - 1, 
		rectCordinate.height() + 2 * BaseLineLenght + 2*BaseFontHeight);
	toNewRect.setRect(
		rectCordinate.left() + 1,
		rectCordinate.top() + 1,
		rectCordinate.width() - Step - 1,
		rectCordinate.height() + 2 * BaseLineLenght +2* BaseFontHeight);
}

void Screen::drawCordinate(QPainter &painter)
{
	if ( firstShow )
	{        
		int y0 = rectCordinate.bottom();
		int x0 = rectCordinate.left();
		int yText = 0;

		for (int j=0; j<=numYTicks; j++ )
        	{    
			painter.setPen(QPen(Qt::blue,1,Qt::SolidLine) );    
			painter.drawLine( x0-BaseLineLenght, y0, x0, y0 );
			if (j%Step==0)
			{
				painter.drawLine( x0-2*BaseLineLenght, y0, x0-BaseLineLenght, y0 );
                        
				if(j==0)
				{
					painter.drawLine( x0 , y0, rectCordinate.right(), y0 );
				}
				if(j==numYTicks)
				{
					painter.drawLine( x0 , rectCordinate.top(),
				 rectCordinate.right(), rectCordinate.top() );}
                       else{
			painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
                        painter.drawLine( x0 , y0, rectCordinate.right(), y0 ); }
   
			painter.setPen( Qt::red );
                        painter.drawText( x0 - 3 * BaseLineLenght - BaseFontHeight ,
                        			y0 -2* BaseFontHeight+ 3* Step ,
                        			BaseFontHeight+3 ,
                        			BaseFontHeight + Step ,
                        			Qt::AlignCenter|Qt::AlignTop ,
                        			QString::number( yText) );
                        yText ++;
                        painter.setPen( Qt::blue );
                }
                y0 -= Step;
        }
	
	painter.save();	
	QRect tempYText( 
                rectYText.left(), rectYText.top(),
                rectYText.height(), rectYText.height() );
        painter.setViewport( tempYText );
        QRect rectYViewport = painter.viewport();
        painter.setWindow( -(int)rectYViewport.width()/2, -(int)rectYViewport.height()/2,
        rectYViewport.width(), rectYViewport.height() );
        QRect rectYWindow = painter.window();
        QRect rectDrawText( 
                rectYWindow.left(),
                -(int)rectYText.width()/2,
                rectYText.height(), 
                rectYText.width() );
        painter.rotate(-90.0);
        double dy = ( rectYWindow.width() - rectDrawText.height() ) / 2;
        dy = dy > 0 ? dy : ( -dy );
        painter.translate( 0, -dy );
        painter.drawText( 
                rectDrawText.left(), 
                rectDrawText.top(), 
                rectDrawText.width()+5, 
                rectDrawText.height()+5,
                Qt::AlignHCenter, stringYTitle );
        painter.restore();
       
        painter.setPen( Qt::blue );
        y0=rectCordinate.bottom(); 
        for ( int i = 0; i <= numXTicks; i ++ )
        {
              painter.setPen(QPen(Qt::blue,1,Qt::SolidLine) );  
	      painter.drawLine( x0 , y0, x0, y0 + BaseLineLenght );
                if ( 0 == i % (2*Step) )
                {
               	   if(i==0){
			 painter.drawLine( x0, y0, x0, rectCordinate.top());}
		   if(i==numXTicks){
			 painter.drawLine( rectCordinate.right(),y0, 
			        	rectCordinate.right(),rectCordinate.top());}
	            else{
		     painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
                     painter.drawLine( x0, rectCordinate.bottom(), 
                    		 x0, rectCordinate.top()); }
                    
                }

                x0 += Step;
        }
        
         painter.drawText( rectXText.left(), rectXText.top(),
 	                          rectXText.width(), rectXText.height()+5,
 	                          Qt::AlignCenter, stringXTitle );                     
  }

}

void Screen::animate( double y )
{
	double newY;  
	newY = y;
	if ( (int) Yval.size() <= (int) width() / 4 )
	{    
		Yval.append( newY );
	} 
	else 
	{
		Yval.erase( Yval.begin() );
		Yval.append( newY );
	}

}

void Screen::drawCurve()
{  
	QPainter painterSave;
	painterSave.begin(&savePixmap);
        painterSave.drawPixmap(0,0,newPixmap);
	painterSave.end();
        
	QPainter painterMid;
	painterMid.begin(&midPixmap);
        painterMid.drawPixmap(toNewRect.left(),toNewRect.top(),savePixmap,
		fromSaveRect.left(),fromSaveRect.top(),fromSaveRect.width(), fromSaveRect.height());
	painterMid.end();

	QPainter painter;
        painter.begin(&newPixmap);
        painter.drawPixmap(rectCordinate.left()+1,rectCordinate.top()+1,midPixmap,rectCordinate.left()+1, 
		rectCordinate.top()+1, rectCordinate.width()-2, fromSaveRect.height());

	int Xnew, Xold;
	QVector<double>::iterator Yit = Yval.end();

        Ynew = rectCordinate.bottom() - *(--Yit) - 1;
        Xnew = rectCordinate.right() -1;
        Xold = rectCordinate.right() - Step;

        painter.setPen( Qt::blue );
        painter.drawLine( toNewRect.right(), rectCordinate.bottom(),
			  rectCordinate.right(), rectCordinate.bottom());                
	painter.drawLine( toNewRect.right(), rectCordinate.bottom(),
			  toNewRect.right(), rectCordinate.bottom() + BaseLineLenght );

       // draw the dotline in the horizontal direction 
        int y0 = rectCordinate.bottom();

        static bool drawDotLine = FALSE;

        if ( drawDotLine )
        {
                for (int j =0; j < (numYTicks /5 -1 ); j++)
                {
		    y0 -= 5*Step;
                     painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
                     painter.drawLine( toNewRect.right() , y0, 
                             rectCordinate.right(), y0 );
                }
        }
        
        drawDotLine = !drawDotLine;

        //draw the calibration values of x-axis
        static int numX = 0;
	if(numX==0)
	Yold= rectCordinate.bottom()-5*Step;

      /*static int sec=0; min=0; hour=0;*/
        if (  numX % (2*Step)==0)
        {
               
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
	   
		//draw the long calibration 
		painter.drawLine( 
                    toNewRect.right(), 
                    rectCordinate.bottom() + BaseLineLenght,
                    toNewRect.right(), 
                    rectCordinate.bottom() + 2 * BaseLineLenght );

		//draw the dotline in the vertical direction
            
		painter.setPen( QPen( Qt::blue, 1, Qt::DotLine) );
		painter.drawLine( 
                    toNewRect.right(), 
                    rectCordinate.bottom(), 
                    toNewRect.right(),
                    rectCordinate.top() );
                
		//draw the calibration values of x-axis
		if (  numX % (4*Step)==0)
		{
			painter.drawLine( 
				toNewRect.right(), 
				rectCordinate.bottom() + 2*BaseLineLenght,
				toNewRect.right(), 
				rectCordinate.bottom() + 3 * Step );
                
		painter.setPen( Qt::blue );
       
		QRect rectCValue(
		    toNewRect.right() - 9 * Step,
		    toNewRect.bottom() -2* BaseFontHeight,
		    10 * Step, 
		    BaseFontHeight+2);

		painter.drawText( 
		    rectCValue.left(), 
		    rectCValue.top(), 
		    rectCValue.width(), 
		    rectCValue.height(),
		    Qt::AlignLeft, 
		    timeString );
            }
	  
          sec += 10;  
            if ( sec==60 )
            {
                sec = 0;
                min += 1;
                if ( min == 60 )
                {
                    min = 0;
                    hour += 1;
                    if ( hour == 60 )
                        hour = 0;
                }
            }         
     }
      
	  numX ++;
       
     if ( numX >= 100 )
             numX = 0;
     
        painter.setPen( Qt::red );
        painter.drawLine( Xold, (int)Yold, Xnew, (int)Ynew );

        Yold = Ynew; 
	painter.end();
	   
}




