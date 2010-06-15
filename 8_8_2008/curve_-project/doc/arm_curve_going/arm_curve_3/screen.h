#ifndef SCREEN_H
#define SCREEN_H

#include <qframe.h>
#include <qvector.h>
#include <qpixmap.h> 
#include <qpainter.h>

#define FrameWidth          3 
#define Step                5   //一次移动的时候的长度，五个像素
#define BaseFontHeight      20 
#define BaseLineLenght      5   //画刻度的单位长度
#define SpaceMargin         5


class QRect;
class QString;

class Screen : public QFrame {
        Q_OBJECT
public:
        Screen( QWidget *parent=0, const char *name=0, WFlags flags=0 );
        void setXTitle( QString &str );
        void setYTitle( QString &str );
};
#endif /*SCREEN_H*/
