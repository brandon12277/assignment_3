#include <stdio.h>

#define MAX_STUDENTS 66
#define MAX_NAME_LENGTH 50

struct Student {
    char name[MAX_NAME_LENGTH];
    int roll;
    int marks[5];
    int totalMarks;
    float averageMarks;
};

int main() {
    FILE *file = fopen("student.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    struct Student students[MAX_STUDENTS];

    for (int i = 0; i < MAX_STUDENTS; ++i) {
        fscanf(file, "%s %d", students[i].name, &students[i].roll);

        students[i].totalMarks = 0;

        for (int j = 0; j < 5; ++j) {
            fscanf(file, "%d", &students[i].marks[j]);
            students[i].totalMarks += students[i].marks[j];
        }

        students[i].averageMarks = (float)students[i].totalMarks / 5.0;
    }

    fclose(file);

    // Print the results
    printf("%-20s%-10s%-10s%-10s%-10s%-10s%-10s\n", "Name", "Roll", "Subject1", "Subject2", "Subject3", "Subject4", "Subject5");
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        printf("%-20s%-10d%-10d%-10d%-10d%-10d%-10d\n", students[i].name, students[i].roll,
               students[i].marks[0], students[i].marks[1], students[i].marks[2], students[i].marks[3], students[i].marks[4]);
    }

    printf("\n%-20s%-10s%-10s\n", "Name", "Total", "Average");
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        printf("%-20s%-10d%-10.2f\n", students[i].name, students[i].totalMarks, students[i].averageMarks);
    }

    return 0;
}