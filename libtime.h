#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

int getMonthNumber(char *month);
char* current_time(char *thismoment);
bool is_leap_year(int year);
int days_in_month(int year, int month);
char add_days(char* date, int days);
int date_difference(int date1, int date2);