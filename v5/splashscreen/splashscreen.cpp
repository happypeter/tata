#include <qapplication.h>
#include <qpainter.h>
#include <qpixmap.h>
#include "splashscreen.h"

SplashScreen::SplashScreen( const QPixmap &pixmap )
        : QWidget( 0, 0, WStyle_Customize | WStyle_NoBorder ),
          pix( pixmap )
    {
        setErasePixmap( pix );
        resize( pix.size() );
       QRect scr = QApplication::desktop()->screenGeometry();
        move( scr.center() - rect().center() );
	QPixmap pix(pixmap);
	setBackgroundPixmap(pix);
        show();
       repaint();
    }

void SplashScreen::repaint()
{
	QWidget::repaint();
	QApplication::flush();
}

#if defined(Q_WS_X11)
void 	qt_wait_for_window_manager(QWidget *widget);
#endif

void SplashScreen::finish(QWidget *mainWin)
{
#if defined (Q_WS_X11)
	qt_wait_for_window_manager(mainWin);
#endif
	show();
	close();
}

