#include <time.h>

#include "s21_smartcalc.h"

depositValues deposit_calc(double amount, int term, double rate, double taxRate,
                           int paymentPeriod, int capitalization,
                           char *replenishmentsList) {  // term in days
  depositValues result = {0};
  replenishmentsListValues amountList[100] = {0};
  dateStruct today = {0};
  dateStruct yesterday = {0};
  int replNumber = 0;
  result.finalAmount = amount;
  double InterestToPay = 0;
  replNumber = replenishmentsListParcer(replenishmentsList, amountList);
  getDay(&today, 0);
  int currentYear = today.year;
  double yearsInterest = 0;
  double yearsIncome = 0;
  for (int i = 1; i <= term; i++) {
    getDay(&today, i);
    if (today.year > currentYear) {
      yearsInterest += (yearsIncome - 75000);
      yearsIncome = 0;
    }
    getDay(&yesterday, i - 1);
    countCurrentSumm(&result.finalAmount, amountList, replNumber, yesterday);
    if (paymentPeriod == DAILY) {
      InterestToPay = dailyInterest(result.finalAmount, rate, today.year);
      interestCalc(capitalization, &result, InterestToPay, &yearsIncome);
    } else if (paymentPeriod == MONTHLY && today.day == 1) {
      InterestToPay =
          monthlyInterest(result.finalAmount, rate, today.year, yesterday.day);
      interestCalc(capitalization, &result, InterestToPay, &yearsIncome);
    }
    currentYear = today.year;
  }
  tax(&result, yearsInterest, taxRate, yearsIncome);
  return result;
}

void interestCalc(int capitalization, depositValues *result,
                  double InterestToPay, double *yearsIncome) {
  capitalizationFunc(capitalization, result, InterestToPay);
  result->totalInterestAmount += InterestToPay;
  *yearsIncome += InterestToPay;
}

void tax(depositValues *result, double yearsInterest, double taxRate,
         double yearsIncome) {
  result->taxAmount += yearsInterest * taxRate;
  if (yearsIncome > 75000) result->taxAmount += (yearsIncome - 75000) * taxRate;
  if (result->taxAmount < 0) result->taxAmount = 0;
}

int replenishmentsListParcer(char *replenishmentsList,
                             replenishmentsListValues *amountList) {
  int count = 0;
  while (*replenishmentsList) {
    amountList[count].day = strtol(replenishmentsList, &replenishmentsList, 10);
    replenishmentsList++;
    amountList[count].month =
        strtol(replenishmentsList, &replenishmentsList, 10);
    replenishmentsList++;
    amountList[count].year =
        strtol(replenishmentsList, &replenishmentsList, 10);
    replenishmentsList++;
    amountList[count].summ = strtod(replenishmentsList, &replenishmentsList);
    count++;
  }
  return count;
}

double dailyInterest(double currentSumm, double rate, int year) {
  double result = 0.0;
  result = currentSumm * rate / (365 + leapYear(year));
  return result;
}

double monthlyInterest(double currentSumm, double rate, int year,
                       int daysInMonth) {
  double result = 0.0;
  result = (currentSumm * rate / (365 + leapYear(year))) * daysInMonth;
  return result;
}

void countCurrentSumm(double *summ, replenishmentsListValues *amountList,
                      int replNumber, dateStruct today) {
  for (int i = 0; i < replNumber; i++) {
    if (today.day == amountList[i].day &&
        today.month + 1 == amountList[i].month &&
        today.year + 1900 == amountList[i].year)
      *summ += amountList[i].summ;
  }
}

void capitalizationFunc(int capitalization, depositValues *result,
                        double InterestToPay) {
  if (capitalization == WITHCAPITAL) {
    result->finalAmount += InterestToPay;
  }
}

void getDay(dateStruct *today, int term) {
  const time_t timer = time(NULL);
  struct tm *today_str = localtime(&timer);
  time_t next = mktime(today_str);
  today_str->tm_mday += term;
  next = mktime(today_str);
  today_str = localtime(&next);
  today->day = today_str->tm_mday;
  today->month = today_str->tm_mon;
  today->year = today_str->tm_year;
}

int leapYear(int year) {
  int res = 0;
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) res = 1;
  return res;
}