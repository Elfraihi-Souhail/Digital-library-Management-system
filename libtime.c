#include "libtime.h"
int getMonthNumber(char *month) {
    char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    for (int i = 0; i < 16; i++) {
        if (strcmp(month, months[i]) == 0) {
            return i + 1;
        }
    }
    return 0;
}
char* current_time(char *thismoment) {
    time_t raw_time;
    struct tm *time_info;
    char currenttime[11];
    char monthstr[9];
    char monthnum[3];
    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(monthstr, sizeof(monthstr), "%B", time_info);
    strftime(currenttime, sizeof(currenttime), "%Y-  -%d", time_info);
    int monthnumber = getMonthNumber(monthstr);
    sprintf(monthnum, "%d", monthnumber);
    if (monthnum[1] == '\0')
    {
        currenttime[5] = '0';
        currenttime[6] = monthnum[0];
    }
    else
    {
        currenttime[5]= monthnum[0];
        currenttime[6]= monthnum[1];
    }
    strcpy(thismoment,currenttime);
    return thismoment;
}
bool is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int days_in_month(int year, int month) {
    int days_per_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // February has 29 days in a leap year
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days_per_month[month];
}
char add_days(char* date, int days)
{
    // Extract year
    char Y[5] = {0};
    strncpy(Y, date, 4);
    int year = atoi(Y);
    // Extract month
    char M[3] = {0};
    M[0] = date[5];
    M[1] = date[6];
    int month = atoi(M);
    // Extract day
    char D[3] = {0};
    D[0] = date[8];
    D[1] = date[9];
    int day = atoi(D);
    // Add days
    while (days > 0) {
        int days_this_month = days_in_month(year, month);
        int days_remaining = days_this_month - day;

        if (days <= days_remaining) {
            day += days;
            days = 0;
        } else {
            days -= (days_remaining + 1);
            day = 1;
            month++;

            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
    sprintf(date, "%04d-%02d-%02d", year, month, day);
    return *date;
}
int date_difference(int date1, int date2) {
    int year1 = date1 / 10000;
    int month1 = (date1 % 10000) / 100;
    int day1 = date1 % 100;
    int year2 = date2 / 10000;
    int month2 = (date2 % 10000) / 100;
    int day2 = date2 % 100;
    int total_days = 0;
    if (day2 < day1) {
        month2--;
        if (month2 == 0) {
            month2 = 12;
            year2--;
        }
        day2 += days_in_month(year2, month2);
    }
    total_days = day2 - day1;
    if (month2 < month1) {
        year2--;
        month2 += 12;
    }
    while (month1 < month2) {
        total_days += days_in_month(year1, month1);
        month1++;
    }
    while (year1 < year2) {
        if (is_leap_year(year1)) {
            total_days += 366;
        } else {
            total_days += 365;
        }
        year1++;
    }
    return total_days;
}
