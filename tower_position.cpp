#include "tower_position.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qsize.h"

const QSize Towerposition::Size(44, 44);

Towerposition::Towerposition(QPoint pos,const QPixmap &sprite)
:m_pos(pos),m_hasTower(false),m_sprite(sprite)
{

}

 const QPoint Towerposition::getCenter() const
{
  QPoint offsetPoint(Size.width() / 2, Size.height() / 2);
  return m_pos + offsetPoint;
}
bool Towerposition::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + Size.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + Size.height());
    return isXInHere && isYInHere;
}
bool Towerposition::hasTower() const
{
   return m_hasTower;
}
void Towerposition::setHasTower(bool hasTower)
{
   m_hasTower=hasTower;
}
void Towerposition::draw(QPainter *painter) const
{
   painter->drawPixmap(m_pos.x(), m_pos.y(), m_sprite);
}



