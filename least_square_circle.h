#ifndef LEAST_SQUARE_CIRCLE_H
#define LEAST_SQUARE_CIRCLE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include<QPixmap>
#include<QImage>
#include<QPainter>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
#include <QKeyEvent>
#include <QDebug>
#define grid_size 20
using namespace std;

class Least_square_circle : public QLabel
{
     Q_OBJECT
public:
    Least_square_circle(QWidget *parent=0);
    void point_toggle(QImage &image_grid,QPoint &p1);
    void ls_circle(QImage &image_grid);
    void init_grid();
    void init_window();
    void reset_window(QImage &image_grid);
    QImage img;
private:

    struct grid{
        int start_gridx,start_gridy;
        int end_gridx,end_gridy;
        int x_inc,y_inc;
        int x_grid[grid_size],y_grid[grid_size];
    }grid_elements;


protected:
    void mousePressEvent(QMouseEvent *mouse_event);

signals:
   void sendMousepressPosition(QPoint&);
};

#endif // LEAST_SQUARE_CIRCLE_H
