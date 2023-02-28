#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    ~GraphWidget();

private:
    Ui::GraphWidget *ui;
};

#endif // GRAPHWIDGET_H