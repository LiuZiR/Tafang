#include "bullet.h"
#include <qpoint.h>
#include <qpixmap.h>
#include <mainwindow.h>
#include <enemy.h>
#include <tower.h>
#include <QPropertyAnimation>
#include <qsize.h>

const QSize Bullet::m_size(8,8);

Bullet::Bullet(QPoint startPos,QPoint targetPos,int damage
               ,Enemy* target,MainWindow *game,const QPixmap &sprite)
    :m_startPos(startPos)
    ,m_targetPos(targetPos)
    ,m_currentPos(startPos)
    ,m_sprite(sprite)
    ,m_target(target)
    ,m_game(game)
    ,m_damage(damage)
{

}
void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos,m_sprite);
}
void Bullet::move()
{
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
    animation->start();
}
void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos=pos;
}
void Bullet::hitTarget()
{
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamaged(m_damage);
    m_game->removedBullet(this);
    printf("1");
}
