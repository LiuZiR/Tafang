#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <vector>
#include "qpixmap.h"
#include <qpoint.h>
#include <QMouseEvent>
#include <enemy.h>
#include <qtimer.h>
#include <qobject.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_waves(0),
    m_playerHp(5),
    m_playerGold(1000)
{
    ui->setupUi(this);
    MainWindow::loadTowerPositions();
    MainWindow::addWayPoints();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    loadWave();
}
void MainWindow::addBullet(Bullet* bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}
void MainWindow::removedBullet(Bullet* bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);
    delete bullet;
}
static const int Towercost=200;

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   static int type=0;
   QPoint pressPos = event->pos();
   if(50<pressPos.x()&&pressPos.x()<100&&50<pressPos.y()&&pressPos.y()<100)
   {
       type=0;
   }
   if(400<pressPos.x()&&pressPos.x()<450&&50<pressPos.y()&&pressPos.y()<100)
   {
       type=1;
   }
   auto it = m_towerPositionsList.begin();
   while(it != m_towerPositionsList.end())
   {
       if(canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
       {
           it->setHasTower();
           Tower *tower = new Tower(it->Center(),this);
           tower->setType(type);
           m_towersList.push_back(tower);
           m_playerGold-=Towercost;
           update();
           break;
       }
       ++it;
   }
}
void MainWindow::awardGold(int gold)
{
    m_playerGold += gold;
}
void MainWindow::updateMap()
{
    foreach(Enemy *enemy, m_enemyList)
        enemy->move();
    foreach(Tower *tower,m_towersList)
        tower->checkEnemyinRange();
    update();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty())
    {
        ++m_waves;
        if(!loadWave())
        {
            m_gameWin = true;
        }
    }
}
bool MainWindow::loadWave()
{
    if(m_waves >= 6)
       return false;
    Waypoint* startWayPoint = m_waypointList[0];
    int enemyStartInterval[]={100,600,1100,1600,2100,2600};
    for(int i=0;i < 6; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint,this,m_waves);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "you lose!":"you win";
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
    }

    painter.drawPixmap(0, 0, QPixmap(":/Resources/map.jpg"));
    painter.setPen(QPen(Qt::white));
    painter.drawText(QRect(400, 25, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
    painter.drawText(QRect(30, 25, 100, 25), QString("HP : %1").arg(m_playerHp));
    painter.drawText(QRect(200, 25, 200, 25), QString("GOLD : %1").arg(m_playerGold));
    painter.drawPixmap(50,50,QPixmap(":/Resources/greenBottle.png"));
    painter.drawPixmap(400,50,QPixmap(":/Resources/bottle.png"));
    foreach (const Towerposition &towerPos, m_towerPositionsList)
        towerPos.draw(&painter);
    foreach (Tower *tower, m_towersList)
        tower->draw_range(&painter);

    foreach(Enemy* enemy, m_enemyList)
        enemy->draw(&painter);
    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);
}

bool MainWindow::canBuyTower() const
{

    if(m_playerGold >= Towercost)
        return true;
    else {
        return false;
    }
}

void MainWindow::getHpDamage()
{
    m_playerHp-=1;
    if(m_playerHp<=0)
       m_gameEnded=true;
}
void MainWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(250, 360),
        QPoint(175, 360),
        QPoint(185, 500),
        QPoint(250, 500),

        QPoint(190, 632),
        QPoint(260, 632),
        QPoint(190, 685),
        QPoint(260, 685),

        QPoint(404, 288),
        QPoint(404, 400),
        QPoint(315, 500),
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
    m_towerPositionsList.push_back(Towerposition(pos[i]));
}
void MainWindow::addWayPoints()
{
    Waypoint *waypoint1=new Waypoint(QPoint(250,170));
    m_waypointList.push_back(waypoint1);
    Waypoint *waypoint2=new Waypoint(QPoint(250,315));
    waypoint1->setNextWayPoint(waypoint2);
    m_waypointList.push_back(waypoint2);
    Waypoint *waypoint3=new Waypoint(QPoint(350,315));
    waypoint2->setNextWayPoint(waypoint3);
    m_waypointList.push_back(waypoint3);
    Waypoint *waypoint4=new Waypoint(QPoint(350,450));
    m_waypointList.push_back(waypoint4);
    waypoint3->setNextWayPoint(waypoint4);
    Waypoint *waypoint5=new Waypoint(QPoint(135,450));
    m_waypointList.push_back(waypoint5);
    waypoint4->setNextWayPoint(waypoint5);
    Waypoint *waypoint6=new Waypoint(QPoint(135,590));
    m_waypointList.push_back(waypoint6);
    waypoint5->setNextWayPoint(waypoint6);
    Waypoint *waypoint7=new Waypoint(QPoint(350,590));
    m_waypointList.push_back(waypoint7);
    waypoint6->setNextWayPoint(waypoint7);
    Waypoint *waypoint8=new Waypoint(QPoint(350,775));
    m_waypointList.push_back(waypoint8);
    waypoint7->setNextWayPoint(waypoint8);
    Waypoint *waypoint9=new Waypoint(QPoint(185,775));
    m_waypointList.push_back(waypoint9);
    waypoint8->setNextWayPoint(waypoint9);
    Waypoint *waypoint10=new Waypoint(QPoint(185,850));
    m_waypointList.push_back(waypoint10);
    waypoint9->setNextWayPoint(waypoint10);
}
