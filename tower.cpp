#include "tower.h"
#include "mainwindow.h"
#include <qpixmap.h>
#include <qpainter.h>
#include <qsize.h>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::Size(44, 44);

Tower::Tower(QPoint pos,const QPixmap &sprite)
:m_pos(pos),m_sprite(sprite)
{
  m_attackRange=100;
}


void Tower::draw_range(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);
    static const QPoint offsetPoint(-Size.width()/2,-Size.height()/2);
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint,m_sprite);
    painter->restore();
}
