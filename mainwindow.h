#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qlist.h>
#include <tower_position.h>
#include <tower.h>
#include <waypoint.h>
#include <enemy.h>
#include <bullet.h>
class Tower;
namespace Ui {
class MainWindow;
}
class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;
class Bullet;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getHpDamage(){};
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    bool loadWave();
    QList<Enemy*> enemyList(){return m_enemyList;}
    void addBullet(Bullet* bullet);

public slots:
    void updateMap();
private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    QList<Towerposition> m_towerPositionsList;
    QList<Tower *> m_towersList;
    QList<Waypoint*> m_waypointList;
    QList<Enemy *> m_enemyList;
    QList<Bullet *> m_bulletList;
    void loadTowerPositions();
    void mousePressEvent(QMouseEvent *event);
    void addWayPoints();
    bool canBuyTower() const;
    int m_waves;
    bool m_gameWin;
    bool m_gameEnded;
};
#endif // MAINWINDOW_H
