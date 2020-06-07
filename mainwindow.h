#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qlist.h>
#include <tower_position.h>
#include <tower.h>
#include <waypoint.h>
#include <enemy.h>

namespace Ui {
class MainWindow;
}
class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getHpDamage(){};
    void removedEnemy(Enemy *enemy);
    bool loadWave();
public slots:
    void updateMap();
private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    QList<Towerposition> m_towerPositionsList;
    QList<Tower *> m_towersList;
    QList<Waypoint*> m_waypointList;
    QList<Enemy *> m_enemyList;
    void loadTowerPositions();
    void mousePressEvent(QMouseEvent *event);
    void addWayPoints();
    bool canBuyTower() const;
    int m_waves;
    bool m_gameWin;
};
#endif // MAINWINDOW_H
