#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

    graph = new GraphWidget;
    connect(this, &MainWindow::signal, graph, &GraphWidget::slot);

  ui->lineEdit->setPlaceholderText("0.00");



  connect(ui->PushButton0, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton1, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton2, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton3, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton4, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton5, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton6, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton7, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton8, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton9, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonBracOpen, SIGNAL(clicked()), this,
          SLOT(ButtonPressed()));
  connect(ui->PushButtonBracClose, SIGNAL(clicked()), this,
          SLOT(ButtonPressed()));
  connect(ui->PushButtonX, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonCos, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAcos, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonSin, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAsin, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonMod, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonTan, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAtan, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonExp, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonLn, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonLog, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonSqrt, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonDiv, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonMult, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonMinus, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonPlus, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonEqual, SIGNAL(clicked()), this,
          SLOT(ButtonEqualPressed()));
  connect(ui->PushButtonDot, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAC, SIGNAL(clicked()), this, SLOT(ButtonACPressed()));
  connect(ui->PushButtonDel, SIGNAL(clicked()), this, SLOT(ButtonDelPressed()));
  connect(ui->PushButtonGraph, SIGNAL(clicked()), this,
          SLOT(GraphingButtonPressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString numbers = "0123456789.- ";
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->setText(ui->lineEdit->text() += button_text);
  } else if (ui->lineEdit_X->hasFocus() && numbers.contains(button_text, Qt::CaseInsensitive)) {
    ui->lineEdit_X->setText(ui->lineEdit_X->text() += button_text);
  }
}

void MainWindow::GraphingButtonPressed() {
    graph->show();
    QString minX = ui->lineEditXmin->text();
    double Xmin = minX.toDouble();
    QString maxX = ui->lineEditXmax->text();
    double Xmax = maxX.toDouble();
    QString minY = ui->lineEditYmin->text();
    double Ymin = minY.toDouble();
    QString maxY = ui->lineEditYmax->text();
    double Ymax = maxY.toDouble();
    QString display_value = ui->lineEdit->text();
    QByteArray ds = display_value.toLocal8Bit();
    char *str = ds.data();
    emit signal(Xmin, Xmax, Ymin, Ymax, str);
}

void MainWindow::ButtonEqualPressed() {
  QString display_value = ui->lineEdit->text();
  QByteArray ds = display_value.toLocal8Bit();
  char *str = ds.data();
  QString x_value = ui->lineEdit_X->text();
  double x = x_value.toDouble();
  if(validation(str, x) == 1){
      QString str_res = QString::number(s21_calculator(str, x), 'g', 16);
      ui->lineEdit->setText(str_res);
  } else {
        ui->lineEdit->setText("ERROR! INCORRECT EXPRESSION");
  }
}

void MainWindow::ButtonDelPressed() {
  if (ui->lineEdit->hasFocus()) {
    QString tmp = ui->lineEdit->text();
    tmp.chop(1);
    ui->lineEdit->setText(tmp);
  } else if (ui->lineEdit_X->hasFocus()) {
    QString tmp = ui->lineEdit_X->text();
    tmp.chop(1);
    ui->lineEdit_X->setText(tmp);
  }
}

void MainWindow::ButtonACPressed() {
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->clear();
  } else if (ui->lineEdit_X->hasFocus()) {
    ui->lineEdit_X->clear();
  }
}
