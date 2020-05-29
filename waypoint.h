#ifndef WAYPOINT_H
#define WAYPOINT_H
#include <qpoint.h>
#include <qpainter.h>
class Waypoint
{
public:
    Waypoint(QPoint pos);
    void setNextWayPoint(Waypoint *nextpoint);
    QPoint pos() ;
    Waypoint* nextWayPoint() ;
    void draw(QPainter *painter) const;
private:
    QPoint m_pos;
    Waypoint * m_nextWayPoint;

};

#endif // WAYPOINT_H
