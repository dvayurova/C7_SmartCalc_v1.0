#include "smartcalc.h"

void credit_calc(double amount, int term, double rate,
                 int type) { // term in month
  rate /= 12;
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
  if (type == ANNUITY) {
    monthly_payment =
        amount * ((rate * pow((1 + rate), term)) / (pow((1 + rate), term) - 1));
    overpayment = monthly_payment * term - amount;
    total_payment = amount + overpayment;
  }
  printf("\n  monthly_payment = %f\n overpayment = %f\n total_payment= %f",
         monthly_payment, overpayment, total_payment);
}