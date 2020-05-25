#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H
#include "qpainter.h"
#include "qpoint.h"
#include "qpixmap.h"

class Towerposition
{
public:
    Towerposition(QPoint pos,const QPixmap &sprite=QPixmap("C:/Users/86185/Documents/Tafang/Resources/keng.png"));
    void setHasTower(bool hasTower = true);
    bool hasTower() const;
    const QPoint getCenter() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) const;

 private:
    QPoint   m_pos;
    bool     m_hasTower;
    QPixmap  m_sprite;
    static const QSize Size;
};

#endif // TOWER_POSITION_H
