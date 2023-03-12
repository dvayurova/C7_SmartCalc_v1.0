#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

    graph = new GraphWidget;
    connect(this, &MainWindow::signal, graph, &GraphWidget::slot);

  ui->lineEdit->setPlaceholderText("0.00");
ui->lineEdit->setFocus();
   ui->radioButtonAnnuitet->setChecked(true);

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
  connect(ui->pushButtonCreditCalc, SIGNAL(clicked()), this, SLOT(CreditCalc()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString numbers = "0123456789.- ";
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->setText(ui->lineEdit->text() += button_text);
    if ((button_text == "acos") || (button_text == "asin")|| (button_text == "atan") || (button_text == "cos") ||
                (button_text == "sin") || (button_text == "tan") || (button_text == "log") || (button_text == "ln") || (button_text == "sqrt") || (button_text == "^"))
           ui->lineEdit->setText(ui->lineEdit->text() += "(");
  } else if (ui->lineEdit_X->hasFocus() && numbers.contains(button_text, Qt::CaseInsensitive)) {
    ui->lineEdit_X->setText(ui->lineEdit_X->text() += button_text);
  }
}

void MainWindow::GraphingButtonPressed() {
    graph->show();
    double Xmin = ui->lineEditXmin->text().toDouble();
    double Xmax = ui->lineEditXmax->text().toDouble();
    double Ymin = ui->lineEditYmin->text().toDouble();
    double Ymax = ui->lineEditYmax->text().toDouble();
    QString display_value = ui->lineEdit->text();
    QByteArray ds = display_value.toLocal8Bit();
    char *str = ds.data();
    emit signal(Xmin, Xmax, Ymin, Ymax, str);
}

void MainWindow::ButtonEqualPressed() {
  QString display_value = ui->lineEdit->text();
  display_value.remove(" ");
  qDebug() << display_value;
  QByteArray ds = display_value.toLocal8Bit();
  char *str = ds.data();
  QString x_value = ui->lineEdit_X->text();
  double x = x_value.toDouble();
  if(validation(str, x) == 1){
      double result = s21_calculator(str, x);
      QString str_res = QString::number(result, 'g', 16);
      if(isnan(result) || isinf(result)) {
          ui->lineEdit->setText("ERROR! INCORRECT EXPRESSION");
      } else {
          ui->lineEdit->setText(str_res);
      }
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

void MainWindow::CreditCalc() {

    double amount = ui->lineEditLoanSum->text().toDouble();
    int term = ui->lineEditTerm->text().toInt();
    double rate = ui->lineEditRate->text().toDouble();
    int type = 0;
    if(ui->radioButtonAnnuitet->isChecked() == true) {
        type = ANNUITY;
    }
    if(ui->radioButtonDifferent->isChecked() == true) {
        type = DIFFER;
    }
    if(ui->comboBoxTerm->currentText() == "лет") {
        term *= 12;
    }
creditValues creditStruct = credit_calc(amount, term, rate/100,
                                        type);
if(type == DIFFER) {
    ui->labelPayment->setText(QString::number(creditStruct.monthlyPaymentFirst, 'f', 2) + " ... " + QString::number(creditStruct.monthlyPaymentLast, 'f', 2) + " руб.");
}
if(type == ANNUITY) {
    ui->labelPayment->setText(QString::number(creditStruct.monthlyPayment, 'f', 2) + " руб.");
}
ui->labelOverpay->setText(QString::number(creditStruct.overPayment, 'f', 2) + " руб.");
ui->labelTotal->setText(QString::number(creditStruct.totalPayment, 'f', 2) + " руб.");

}
