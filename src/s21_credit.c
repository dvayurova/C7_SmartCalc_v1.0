#include "s21_smartcalc.h"

creditValues credit_calc(double amount, int term, double rate,
                         int type) { // term in month
  creditValues creditResult = {0};
  if (type == ANNUITY) {
    rate /= 12;
    creditResult.monthlyPayment =
        amount * ((rate * pow((1 + rate), term)) / (pow((1 + rate), term) - 1));
    creditResult.overPayment = creditResult.monthlyPayment * term - amount;
    creditResult.totalPayment = amount + creditResult.overPayment;
  }
  if (type == DIFFER) {
    double monthPrincipalPay = 0;
    monthPrincipalPay = amount / term;
    for (int i = 0; i < term; i++) {
      creditResult.monthlyPayment =
          (amount - (monthPrincipalPay * i)) * rate / 12 + monthPrincipalPay;
      creditResult.totalPayment += creditResult.monthlyPayment;
    }
    creditResult.monthlyPaymentFirst =
        (amount - (monthPrincipalPay * 0)) * rate / 12 + monthPrincipalPay;
    creditResult.monthlyPaymentLast =
        (amount - (monthPrincipalPay * (term - 1))) * rate / 12 +
        monthPrincipalPay;
    creditResult.overPayment = creditResult.totalPayment - amount;
  }
  printf("\n  creditResult.monthlyPayment = %f, monthlyPaymentFirst = %f, "
         "monthlyPaymentLast = %f\n overpayment = "
         "%f\n "
         "total_payment= %f",
         creditResult.monthlyPayment, creditResult.monthlyPaymentFirst,
         creditResult.monthlyPaymentLast, creditResult.overPayment,
         creditResult.totalPayment);
  if (term <= 0 || rate <= 0) {
    memset(&creditResult, '0', sizeof(creditResult));
  }
  return creditResult;
}