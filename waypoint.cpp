#include "waypoint.h"
#include <qpoint.h>
#include <qpainter.h>
#include <qcolor.h>

Waypoint::Waypoint(QPoint pos)
:m_pos(pos),m_nextWayPoint(NULL)
{
}
void Waypoint::setNextWayPoint(Waypoint *nextpoint)
{
    m_nextWayPoint=nextpoint;
}
QPoint Waypoint::pos(){return m_pos;}

Waypoint* Waypoint::nextWayPoint(){return m_nextWayPoint;}

void Waypoint::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QColor(0, 255, 0));
    painter->drawEllipse(m_pos, 6, 6);
    painter->drawEllipse(m_pos, 2, 2);

    if (m_nextWayPoint)
        painter->drawLine(m_pos, m_nextWayPoint->m_pos);
    painter->restore();
}
