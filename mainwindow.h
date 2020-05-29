#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qlist.h>
#include <tower_position.h>
#include <tower.h>
#include <waypoint.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    QList<Towerposition> m_towerPositionsList;
    QList<Tower *> m_towersList;
    QList<Waypoint*> m_waypointList;
    void loadTowerPositions();
    void mousePressEvent(QMouseEvent *event);
    void addWayPoints();
    bool canBuyTower() const;
};

#endif // MAINWINDOW_H
