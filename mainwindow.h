#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);

signals:
    void sendkeypressSignal();

public slots:
    void show_Mousepressposition(QPoint& pos);
    void show_keypresstext();
};

#endif // MAINWINDOW_H
