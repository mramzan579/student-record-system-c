/*
 * student_record_system.c
 * Student Record System in C  
 * Add the view_students() function so the user can
 * see all stored records in a clean formatted table
 * with a grade calculated from each student's marks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Constants ──────────────────────────────────────────────── */
#define MAX_STUDENTS  100
#define NAME_LEN       50
#define FILE_NAME     "students.txt"

/* ── Student struct ─────────────────────────────────────────── */
struct Student {
    int   id;
    char  name[NAME_LEN];
    int   age;
    float marks;
};

/* ── Global student list ────────────────────────────────────── */
struct Student students[MAX_STUDENTS];
int student_count = 0;

/* ================================================================
   clear_input_buffer()
   Drains leftover characters from stdin after every scanf.
================================================================ */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ================================================================
   show_menu()
   Prints the main menu options to the console.
================================================================ */
void show_menu(void)
{
    printf("\n========================================\n");
    printf("    STUDENT RECORD MANAGEMENT SYSTEM    \n");
    printf("========================================\n");
    printf("  1. Add Student\n");
    printf("  2. View All Students\n");
    printf("  3. Search Student by ID\n");
    printf("  4. Delete Student\n");
    printf("  5. Save Records to File\n");
    printf("  6. Exit\n");
    printf("========================================\n");
    printf("  Enter your choice: ");
}

/* ================================================================
   add_student()
   Adds a new student record to the students array.
   Reads ID, name, age, and marks from the user.
   Checks for duplicate IDs before saving.
================================================================ */
void add_student(void)
{
    int i;
    int new_id;

    if (student_count >= MAX_STUDENTS) {
        printf("\n  Record list is full! Cannot add more students.\n");
        return;
    }

    printf("\n--- Add New Student ---\n");

    printf("  Enter student ID : ");
    scanf("%d", &new_id);
    clear_input_buffer();

    for (i = 0; i < student_count; i++) {
        if (students[i].id == new_id) {
            printf("\n  ID %d already exists! Each student needs a unique ID.\n",
                   new_id);
            return;
        }
    }

    students[student_count].id = new_id;

    printf("  Enter name       : ");
    fgets(students[student_count].name, NAME_LEN, stdin);
    students[student_count].name[strcspn(students[student_count].name, "\n")] = '\0';

    printf("  Enter age        : ");
    scanf("%d", &students[student_count].age);
    clear_input_buffer();

    printf("  Enter marks      : ");
    scanf("%f", &students[student_count].marks);
    clear_input_buffer();

    student_count++;

    printf("\n  Student added successfully!\n");
    printf("  Total students: %d\n", student_count);
}

/* ================================================================
   view_students()
   Prints all student records in a clean formatted table.
   Calculates and displays a letter grade for each student
   based on their marks:
     90 and above  = A
     80 to 89      = B
     70 to 79      = C
     60 to 69      = D
     below 60      = F
   Uses %-Nd format specifiers to align columns neatly.
================================================================ */
void view_students(void)
{
    int  i;
    char grade;

    printf("\n--- All Student Records ---\n");

    /* Check if the list is empty */
    if (student_count == 0) {
        printf("  No records found. Add some students first.\n");
        return;
    }

    printf("  Total students: %d\n\n", student_count);

    /*
     * %-5s means: print a string, left-aligned, in 5 characters wide.
     * %-25s means: print a string, left-aligned, in 25 characters wide.
     * This keeps all columns lined up neatly in a table.
     */
    printf("  %-5s %-25s %-5s %-8s %s\n",
           "ID", "Name", "Age", "Marks", "Grade");
    printf("  --------------------------------------------------\n");

    /* Loop through every student and print one row per student */
    for (i = 0; i < student_count; i++) {

        /* Calculate grade from marks */
        if      (students[i].marks >= 90) grade = 'A';
        else if (students[i].marks >= 80) grade = 'B';
        else if (students[i].marks >= 70) grade = 'C';
        else if (students[i].marks >= 60) grade = 'D';
        else                              grade = 'F';

        /* Print one row — %.2f prints float with exactly 2 decimal places */
        printf("  %-5d %-25s %-5d %-8.2f %c\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].marks,
               grade);
    }

    printf("  --------------------------------------------------\n");
}

/* ── Main ───────────────────────────────────────────────────── */
int main(void)
{
    int choice;

    //welcome banner
    printf("========================================\n");
    printf("  STUDENT RECORD MANAGEMENT SYSTEM      \n");
    printf("========================================\n");
    printf("  Manage student records with ease.\n");
    printf("  Maximum capacity: %d students.\n", MAX_STUDENTS);

  //main loop   
    do {
        show_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                view_students();
                break;
            case 3:
                printf("\n  [Coming soon] Search Student\n");
                break;
            case 4:
                printf("\n  [Coming soon] Delete Student\n");
                break;
            case 5:
                printf("\n  [Coming soon] Save to File\n");
                break;
            case 6:
                printf("\n  Goodbye!\n");
                break;
            default:
                printf("\n  Invalid choice! Please enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}