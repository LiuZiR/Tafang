#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <vector>
#include "qpixmap.h"
#include <qpoint.h>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::loadTowerPositions();
    MainWindow::addWayPoints();
}
bool MainWindow::canBuyTower() const
{
    return true;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
   QPoint pressPos = event->pos();
   auto it = m_towerPositionsList.begin();
   while(it != m_towerPositionsList.end())
   {
       if(canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
       {
           it->setHasTower();
           Tower *tower = new Tower(it->Center());
           m_towersList.push_back(tower);
           update();
           break;
       }
       ++it;
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/Resources/map.jpg"));

    foreach (const Towerposition &towerPos, m_towerPositionsList)
        towerPos.draw(&painter);
    foreach (Tower *tower, m_towersList)
        tower->draw_range(&painter);
    foreach(Waypoint *waypoint, m_waypointList)
        waypoint->draw(&painter);
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
    Waypoint *waypoint1=new Waypoint(QPoint(185,850));
    m_waypointList.push_back(waypoint1);
    Waypoint *waypoint2=new Waypoint(QPoint(185,775));
    waypoint1->setNextWayPoint(waypoint2);
    m_waypointList.push_back(waypoint2);
    Waypoint *waypoint3=new Waypoint(QPoint(350,775));
    waypoint2->setNextWayPoint(waypoint3);
    m_waypointList.push_back(waypoint3);
    Waypoint *waypoint4=new Waypoint(QPoint(350,590));
    m_waypointList.push_back(waypoint4);
    waypoint3->setNextWayPoint(waypoint4);
    Waypoint *waypoint5=new Waypoint(QPoint(135,590));
    m_waypointList.push_back(waypoint5);
    waypoint4->setNextWayPoint(waypoint5);
    Waypoint *waypoint6=new Waypoint(QPoint(135,450));
    m_waypointList.push_back(waypoint6);
    waypoint5->setNextWayPoint(waypoint6);
    Waypoint *waypoint7=new Waypoint(QPoint(350,450));
    m_waypointList.push_back(waypoint7);
    waypoint6->setNextWayPoint(waypoint7);
    Waypoint *waypoint8=new Waypoint(QPoint(350,315));
    m_waypointList.push_back(waypoint8);
    waypoint7->setNextWayPoint(waypoint8);
    Waypoint *waypoint9=new Waypoint(QPoint(250,315));
    m_waypointList.push_back(waypoint9);
    waypoint8->setNextWayPoint(waypoint9);
    Waypoint *waypoint10=new Waypoint(QPoint(250,170));
    m_waypointList.push_back(waypoint10);
    waypoint9->setNextWayPoint(waypoint10);
}
