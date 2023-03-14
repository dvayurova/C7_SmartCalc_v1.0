#include <time.h>

#include "s21_smartcalc.h"

depositValues deposit_calc(double amount, int term, double rate, double taxRate,
                           int paymentPeriod, int capitalization,
                           char *replenishmentsList) {  // term in days
  depositValues creditResult = {0};
  replenishmentsListValues amountList[100] = {0};
  dateStruct today = {0};
  dateStruct yesterday = {0};
  int replenishmentsNumber = 0;
  double currentSumm = amount;
  replenishmentsNumber =
      replenishmentsListParcer(replenishmentsList, amountList);
  getDay(&today, 0);
  int currentYear = today.year;
  double yearsInterest = 0;
  double yearsIncome = 0;
  for (int i = 1; i <= term; i++) {
    getDay(&today, i);
    if (today.year > currentYear) {
      yearsInterest += (yearsIncome - 75000);
      printf("\n yearsInterest = %f", yearsInterest * 0.13);
      yearsIncome = 0;
    }
    // printf("\n\n Date: %d.%d.%d\n", today.day, today.month + 1,
    //        today.year + 1900);
    getDay(&yesterday, i - 1);
    countCurrentSumm(&currentSumm, amountList, replenishmentsNumber, yesterday);
    creditResult.totalInterestAmount +=
        dailyInterest(currentSumm, rate, today.year);
    yearsIncome += dailyInterest(currentSumm, rate, today.year);
    // printf("\n creditResult.totalInterestAmount = %f",
    //        creditResult.totalInterestAmount);
    currentYear = today.year;
  }
  creditResult.taxAmount += yearsInterest * taxRate;
  if (yearsIncome > 75000)
    creditResult.taxAmount += (yearsIncome - 75000) * taxRate;
  printf("\n tax = %f", creditResult.taxAmount);
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
  // printf("\n dailyInterest = %f", result);
  return result;
}

void countCurrentSumm(double *summ, replenishmentsListValues *amountList,
                      int replenishmentsNumber, dateStruct today) {
  for (int i = 0; i < replenishmentsNumber; i++) {
    if (today.day == amountList[i].day &&
        today.month + 1 == amountList[i].month &&
        today.year + 1900 == amountList[i].year)
      *summ += amountList[i].summ;
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

int main() {
  //   printf("\n\nDate: %d.%d.%d\n", now->tm_mday, now->tm_mon, now->tm_year);

  char addSummDate[] =
      "24/03/2023	+1000000	18/05/2023	-500000";
  // char addSummDate[] = " ";
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
  creditResult = deposit_calc(2000000, 2000, 0.11, 0.13, 1, 0, addSummDate);
  printf("\n totalInterestAmount = %f", creditResult.totalInterestAmount);
  // long int s_time;
  // // Указатель, в который будет помещен адрес структуры с
  // // преобразованным временем
  // struct tm *m_time;

  // // Считываем текущее системное время
  // s_time = time(NULL);

  // // Преобразуем системное время в локальное
  // m_time = localtime(&s_time);

  // // С помощью функции asctime преобразуем локальное время в строку
  // // и выводим результат на консоль
  // printf("Время : %s\n", asctime(m_time));
  return 0;
}