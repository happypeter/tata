#ifndef SCREEN_H
#define SCREEN_H

#include <qframe.h>
#include <qvector.h>
#include <qpixmap.h> 
#include <qpainter.h>

#define FrameWidth          3 
#define Step                5   //һ���ƶ���ʱ��ĳ��ȣ��������
#define BaseFontHeight      20 
#define BaseLineLenght      5   //���̶ȵĵ�λ����
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
