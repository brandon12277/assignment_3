#include <stdio.h>

struct Time {
    int hours;
    int minutes;
    int seconds;
};

struct Time addTime(struct Time time1, struct Time time2) {
    struct Time result;

    result.seconds = time1.seconds + time2.seconds;
    result.minutes = time1.minutes + time2.minutes + result.seconds / 60;
    result.hours = time1.hours + time2.hours + result.minutes / 60;

    result.seconds %= 60;
    result.minutes %= 60;

    return result;
}

int main() {
    struct Time time1, time2, sum;

    printf("Enter the first time (hours minutes seconds): ");
    scanf("%d %d %d", &time1.hours, &time1.minutes, &time1.seconds);

    printf("Enter the second time (hours minutes seconds): ");
    scanf("%d %d %d", &time2.hours, &time2.minutes, &time2.seconds);
    
    sum = addTime(time1, time2);

    printf("Sum of times: %d hours %d minutes %d seconds\n", sum.hours, sum.minutes, sum.seconds);

    return 0;
}
