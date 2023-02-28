#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphwidget.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#ifdef __cplusplus
extern "C"
{
#endif
#include "s21_smartcalc.h"
#ifdef __cplusplus
}
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GraphWidget graph;

private slots:
    void ButtonPressed();
    void ButtonDelPressed();
    void ButtonACPressed();
    void GraphingButtonPressed();
};

#endif // MAINWINDOW_H
