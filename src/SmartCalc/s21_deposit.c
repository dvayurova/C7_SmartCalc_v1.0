#include "s21_smartcalc.h"
#include <time.h>

depositValues deposit_calc(double amount, int term, double rate, double taxRate,
                           int paymentPeriod, int capitalization,
                           char *replenishmentsList) { // term in days
  depositValues creditResult = {0};
  replenishmentsListValues amountList[100] = {0};
  dateStruct today = {0};
  int replenishmentsNumber = 0;
  double currentSumm = amount;
  replenishmentsNumber =
      replenishmentsListParcer(replenishmentsList, amountList);
  getDay(&today, 0);
  //   int currentYear = today.year;
  //   double yearsInterest = 0;
  for (int i = 0; i < term; i++) {
    getDay(&today, i);
    // if (today.year > currentYear) {
    //   yearsInterest = creditResult.totalInterestAmount;
    //   printf("\n yearsInterest = %f", yearsInterest);
    // }
    printf("\n Date: %d.%d.%d\n", today.day, today.month, today.year);
    countCurrentSumm(&currentSumm, amountList, replenishmentsNumber, today);
    creditResult.totalInterestAmount +=
        dailyInterest(currentSumm, rate, today.year);
    // currentYear = today.year;
  }
  printf("\n tax = %f", (creditResult.totalInterestAmount - 75000) * taxRate);
  return creditResult;
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
  //   printf("\n currentSumm = %f, dailyInterest = %f", currentSumm, result);
  return result;
}

void countCurrentSumm(double *summ, replenishmentsListValues *amountList,
                      int replenishmentsNumber, dateStruct today) {
  for (int i = 0; i < replenishmentsNumber; i++) {
    if (today.day == amountList[i].day && today.month == amountList[i].month &&
        today.year == amountList[i].year)
      *summ += amountList[i].summ;
  }
}

void getDay(dateStruct *today, int term) {
  const time_t timer = time(NULL);
  struct tm *today_str = localtime(&timer);
  today_str->tm_mon += 1;
  today_str->tm_year += 1900;
  //   printf("\n TODAY: %d.%d.%d\n", today_str->tm_mday, today_str->tm_mon,
  //          today_str->tm_year);
  today_str->tm_mday += term;
  time_t next = mktime(today_str);
  today_str = localtime(&next);
  //   printf("\n TODAY_AFTER: %d.%d.%d\n", today_str->tm_mday,
  //   today_str->tm_mon,
  //          today_str->tm_year);
  today->day = today_str->tm_mday;
  today->month = today_str->tm_mon;
  today->year = today_str->tm_year;
}

int leapYear(int year) {
  int res = 0;
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    res = 1;
  return res;
}

int main() {
  //   printf("\n\nDate: %d.%d.%d\n", now->tm_mday, now->tm_mon, now->tm_year);

  char addSummDate[] = "14/03/2023	+1000	18/04/2023	+5000";
  //   replenishmentsListValues amountList[100] = {0};
  //   int count = replenishmentsListParcer(addSummDate, amountList);
  //   for (int i = 0; i < count; i++) {
  //     printf("\n amountList.day[%d] = %d, amountList.month[%d] = %d, "
  //            "amountList.year[%d] = %d,  amountList.summ[%d] = %f  \n",
  //            i, amountList[i].day, i, amountList[i].month, i,
  //            amountList[i].year, i, amountList[i].summ);
  //   }

  //   const time_t timer = time(NULL);
  //   struct tm *today = localtime(&timer);
  //   today->tm_mday = amountList[0].day;
  //   today->tm_mon = amountList[0].month;
  //   today->tm_year = amountList[0].year;

  //   printf("Date: %d.%d.%d\n", today->tm_mday, today->tm_mon,
  //   today->tm_year); today->tm_mday += 35; time_t next = mktime(today); today
  //   = localtime(&next); printf("Date2: %d.%d.%d\n", today->tm_mday,
  //   today->tm_mon, today->tm_year); double summ = 100000;
  //   countCurrentSumm(&summ, amountList, count);
  //   printf("\n current summ = %f", summ);
  //   printf("\n dailyInterest = %f", dailyInterest(summ, 0.1, 2023));
  depositValues creditResult = {0};
  creditResult = deposit_calc(1000000, 293, 0.1, 0.13, 1, 0, addSummDate);
  printf("\n totalInterestAmount = %f", creditResult.totalInterestAmount);
  return 0;
}