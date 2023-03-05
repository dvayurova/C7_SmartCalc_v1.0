#include "graphwidget.h"
#include "ui_graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWidget)
{
    ui->setupUi(this);

//    double XBegin = -1; //Начало интервала, где рисуем график по оси Ox
//    double XEnd =  1; //Конец интервала, где рисуем график по оси Ox
//    double h = 0.01; //Шаг, с которым будем пробегать по оси Ox
//    int N = (XEnd - XBegin) / h + 2; //Вычисляем количество точек, которые будем отрисовывать
//    QVector<double> x(N), y(N); //Массивы координат точек

//    //Вычисляем наши данные
//    int i=0;
//    //Пробегаем по всем точкам
//    for (double X = XBegin; X <= XEnd; X += h) {
//      x[i] = X;
//      y[i] = X * X;//Формула нашей функции
//      i++;
//    }
//    ui->widget->clearGraphs();//Если нужно, но очищаем все графики

//    //Добавляем один график в widget
//    ui->widget->addGraph();

//    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
//    ui->widget->graph(0)->setData(x, y);

//    //Подписываем оси Ox и Oy
//    ui->widget->xAxis->setLabel("x");
//    ui->widget->yAxis->setLabel("y");

//    //Установим область, которая будет показываться на графике
//    ui->widget->xAxis->setRange(XBegin, XEnd);//Для оси Ox

//    //Для показа границ по оси Oy сложнее, так как надо по правильному
//    //вычислить минимальное и максимальное значение в векторах
//    double minY = y[0], maxY = y[0];
//    for (int i = 1; i < N; i++) {
//      if (y[i] < minY) minY = y[i];
//      if (y[i] > maxY) maxY = y[i];
//    }
//    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

//    //И перерисуем график на нашем widget
//    ui->widget->replot();


}

void GraphWidget::slot(double Xmin, double Xmax, double Ymin, double Ymax, char* str)
{
           h = 0.1;
           ui->widget->clearGraphs();
           ui->widget->xAxis->setRange(Xmin, Xmax);
           ui->widget->yAxis->setRange(Ymin, Ymax);

            for (X = Xmin; X <= Xmax; X += h) {
                double Y = s21_calculator(str, X);
                x.push_back(X);
                y.push_back(Y);
            }

           ui->widget->addGraph();
           ui->widget->graph(0)->addData(x, y);
           ui->widget->replot();
           x.clear();
           y.clear();
}

GraphWidget::~GraphWidget()
{
    delete ui;
}



