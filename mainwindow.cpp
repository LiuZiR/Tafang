#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <vector>
#include "qpixmap.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::loadTowerPositions();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("C:/Users/86185/Documents/Tafang/Resources/map.jpg"));

    foreach (const Towerposition &towerPos, m_towerPositionsList)
        towerPos.draw(&painter);

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
