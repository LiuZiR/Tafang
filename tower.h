#ifndef TOWER_H
#define TOWER_H
#include <qpoint.h>
#include <qpixmap.h>
class Tower
{
public:
    Tower(QPoint pos,const QPixmap &sprite=QPixmap(":/Resources/atower.png"));
    void draw_range(QPainter *painter);
protected:

    static const QSize Size;
    QPoint m_pos;
    int m_attackRange;
    double m_damage;
    int m_firerate;
    QPixmap  m_sprite;

};

#endif // TOWER_H
