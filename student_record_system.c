/*
 * student_record_system.c
 * Student Record System — Commit 2
 * Add the add_student() function so the user can
 * store a new student record with ID, name, age, and marks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Constants ──────────────────────────────────────────────── */
#define MAX_STUDENTS  100
#define NAME_LEN       50
#define FILE_NAME     "students.txt"

// Student struct
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
   Checks for duplicate IDs before saving — every student
   must have a unique ID number.
   Checks if the array is full before adding.
================================================================ */
void add_student(void)
{
    int i;
    int new_id;

    /* Stop if maximum capacity is reached */
    if (student_count >= MAX_STUDENTS) {
        printf("\n  Record list is full! Cannot add more students.\n");
        return;
    }

    printf("\n--- Add New Student ---\n");

    /* Read the student ID */
    printf("  Enter student ID : ");
    scanf("%d", &new_id);
    clear_input_buffer();

    /* Check if this ID already exists in the array.
       Every student must have a unique ID — no duplicates allowed. */
    for (i = 0; i < student_count; i++) {
        if (students[i].id == new_id) {
            printf("\n  ID %d already exists! Each student needs a unique ID.\n",
                   new_id);
            return;
        }
    }

    /* ID is unique — save it */
    students[student_count].id = new_id;

    /* Read student name using fgets — handles names with spaces */
    printf("  Enter name       : ");
    fgets(students[student_count].name, NAME_LEN, stdin);
    students[student_count].name[strcspn(students[student_count].name, "\n")] = '\0';

    /* Read age */
    printf("  Enter age        : ");
    scanf("%d", &students[student_count].age);
    clear_input_buffer();

    /* Read marks — uses %f because marks is a float */
    printf("  Enter marks      : ");
    scanf("%f", &students[student_count].marks);
    clear_input_buffer();

    /* Increment counter — record is now officially saved */
    student_count++;

    printf("\n  Student added successfully!\n");
    printf("  Total students: %d\n", student_count);
}

// ── Main
int main(void)
{
    int choice;

    /* Welcome banner */
    printf("========================================\n");
    printf("  STUDENT RECORD MANAGEMENT SYSTEM      \n");
    printf("========================================\n");
    printf("  Manage student records with ease.\n");
    printf("  Maximum capacity: %d students.\n", MAX_STUDENTS);

    /* Main loop */
    do {
        show_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                printf("\n  [Coming soon] View All Students\n");
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