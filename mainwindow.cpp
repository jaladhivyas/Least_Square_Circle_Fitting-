#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Signals and slots for key and mouse press positions
    connect(this,SIGNAL(sendkeypressSignal()),this,SLOT(show_keypresstext()));
    connect(ui->display_image,SIGNAL(sendMousepressPosition(QPoint&)),this,SLOT(show_Mousepressposition(QPoint&)));

    // Initialize grid points and image
    ui->display_image->img= QImage(ui->display_image->size().width(), ui->display_image->size().height(),QImage::Format_RGB32);
    ui->display_image->init_grid();
    ui->display_image->reset_window(ui->display_image->img);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // If Key G is pressed, then  show the the circle
    if(event->key() == Qt::Key_G)
        ui->display_image->ls_circle(ui->display_image->img);

    // If Key C is pressed, then reset the window
    if(event->key() == Qt::Key_C)
        ui->display_image->reset_window(ui->display_image->img);

}

void MainWindow::show_Mousepressposition(QPoint &pos)
{
    // toggle the image grid points
    ui->display_image->point_toggle(ui->display_image->img,pos);
}

void MainWindow::show_keypresstext()
{

}


MainWindow::~MainWindow()
{
    delete ui;
}
