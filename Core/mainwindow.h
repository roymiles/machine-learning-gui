#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QSlider>

#include "Graph/graphwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_addBlock_clicked();

    void on_zoomOut_clicked();

    void on_zoomIn_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;

    GraphWidget *graphWidget;
};

#endif // MAINWINDOW_H
