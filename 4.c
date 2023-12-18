#include <stdio.h>


struct DATE {
    int day;
    int month;
    int year;
};


int isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int isValidDate(struct DATE date) {
  
    if (date.year < 1 || date.year > 9999) {
        return 0; // Invalid year
    }

  
    if (date.month < 1 || date.month > 12) {
        return 0; // Invalid month
    }

  
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.month == 2 && isLeapYear(date.year)) {
        daysInMonth[2] = 29; 
    }

    if (date.day < 1 || date.day > daysInMonth[date.month]) {
        return 0; 
    }

    return 1;
}

int compareDates(struct DATE date1, struct DATE date2) {
    if (!isValidDate(date1) || !isValidDate(date2)) {
        return -1; 
    }

    if (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year) {
        return 0; 
    } else {
        return 1; 
    }
}

int main() {
    struct DATE date1, date2;


    printf("Enter the first date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &date1.day, &date1.month, &date1.year);

    printf("Enter the second date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &date2.day, &date2.month, &date2.year);

   
    int result = compareDates(date1, date2);

    if (result == -1) {
        printf("At least one of the entered dates is invalid.\n");
    } else if (result == 0) {
        printf("Dates are equal.\n");
    } else {
        printf("Dates are unequal.\n");
    }

    return 0;
}
