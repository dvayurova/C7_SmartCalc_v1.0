#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

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
  connect(ui->PushButtonPi, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
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
  connect(ui->PushButtonEqual, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonDot, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAC, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonDel, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonSign, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonGraph, SIGNAL(clicked()), this,
          SLOT(GraphingButtonPressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString display_value = ui->lineEdit->text();
  QString x_value = ui->lineEdit_X->text();
  QByteArray ds = display_value.toLocal8Bit();
  char *str = ds.data();
  double x = x_value.toDouble();
  if (button_text == "DEL") {
    if (ui->lineEdit->hasFocus()) {
      QString tmp = ui->lineEdit->text();
      tmp.chop(1);
      ui->lineEdit->setText(tmp);
    } else if (ui->lineEdit_X->hasFocus()) {
      QString tmp = ui->lineEdit_X->text();
      tmp.chop(1);
      ui->lineEdit_X->setText(tmp);
    }
  } else if (button_text == "AC") {
    if (ui->lineEdit->hasFocus()) {
      ui->lineEdit->clear();
    } else if (ui->lineEdit_X->hasFocus()) {
      ui->lineEdit_X->clear();
    }
  } else {
    if (ui->lineEdit->hasFocus()) {
      ui->lineEdit->setText(ui->lineEdit->text() += button_text);
    } else if (ui->lineEdit_X->hasFocus()) {
      ui->lineEdit_X->setText(ui->lineEdit_X->text() += button_text);
    }
  }
  if (button_text == "=") {
    QString str_res = QString::number(s21_calculator(str, x), 'g', 16);
    ui->lineEdit->setText(str_res);
  }
}

void MainWindow::GraphingButtonPressed() { graph.show(); }
