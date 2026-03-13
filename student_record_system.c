/*
 * student_record_system.c
 * Student Record System 
 * Add search_student() to find a record by ID and
 * update_student() to edit an existing student's details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constants
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
    printf("  4. Update Student Record\n");
    printf("  5. Delete Student\n");
    printf("  6. Save Records to File\n");
    printf("  7. Exit\n");
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
   Prints all student records in a clean formatted table
   with a letter grade calculated from each student's marks.
================================================================ */
void view_students(void)
{
    int  i;
    char grade;

    printf("\n--- All Student Records ---\n");

    if (student_count == 0) {
        printf("  No records found. Add some students first.\n");
        return;
    }

    printf("  Total students: %d\n\n", student_count);

    printf("  %-5s %-25s %-5s %-8s %s\n",
           "ID", "Name", "Age", "Marks", "Grade");
    printf("  --------------------------------------------------\n");

    for (i = 0; i < student_count; i++) {

        if      (students[i].marks >= 90) grade = 'A';
        else if (students[i].marks >= 80) grade = 'B';
        else if (students[i].marks >= 70) grade = 'C';
        else if (students[i].marks >= 60) grade = 'D';
        else                              grade = 'F';

        printf("  %-5d %-25s %-5d %-8.2f %c\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].marks,
               grade);
    }

    printf("  --------------------------------------------------\n");
}

/* ================================================================
   search_student()
   Searches for a student by their ID number.
   Loops through the array and compares each ID.
   Prints the full record with grade if found.
================================================================ */
void search_student(void)
{
    int  i;
    int  search_id;
    int  found = 0;
    char grade;

    printf("\n--- Search Student by ID ---\n");

    if (student_count == 0) {
        printf("  No records to search. Add some students first.\n");
        return;
    }

    printf("  Enter student ID to search: ");
    scanf("%d", &search_id);
    clear_input_buffer();

    for (i = 0; i < student_count; i++) {
        if (students[i].id == search_id) {

            if      (students[i].marks >= 90) grade = 'A';
            else if (students[i].marks >= 80) grade = 'B';
            else if (students[i].marks >= 70) grade = 'C';
            else if (students[i].marks >= 60) grade = 'D';
            else                              grade = 'F';

            printf("\n  Student found:\n");
            printf("  ----------------------------------------\n");
            printf("    ID    : %d\n",   students[i].id);
            printf("    Name  : %s\n",   students[i].name);
            printf("    Age   : %d\n",   students[i].age);
            printf("    Marks : %.2f\n", students[i].marks);
            printf("    Grade : %c\n",   grade);
            printf("  ----------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n  No student found with ID %d.\n", search_id);
    }
}

/* ================================================================
   update_student()
   Finds a student by ID and lets the user update their
   name, age, and marks individually.
   The user can choose which fields to update and skip
   the rest by pressing Enter — keeping the old value.
   The ID is never changed — it is the unique identifier.
================================================================ */
void update_student(void)
{
    int   i;
    int   update_id;
    int   found = 0;
    char  temp_name[NAME_LEN];
    int   temp_age;
    float temp_marks;

    printf("\n--- Update Student Record ---\n");

    if (student_count == 0) {
        printf("  No records to update. Add some students first.\n");
        return;
    }

    /* Show all records first so user knows which ID to update */
    view_students();

    printf("\n  Enter student ID to update: ");
    scanf("%d", &update_id);
    clear_input_buffer();

    /* Find the student with this ID */
    for (i = 0; i < student_count; i++) {
        if (students[i].id == update_id) {

            found = 1;

            printf("\n  Updating Student ID: %d\n", update_id);
            printf("  Press Enter to keep the current value.\n\n");

            //update name
            printf("  Current name : %s\n", students[i].name);
            printf("  New name     : ");
            fgets(temp_name, NAME_LEN, stdin);
            temp_name[strcspn(temp_name, "\n")] = '\0';

            /* Only update if user typed something new */
            if (strlen(temp_name) > 0) {
                strcpy(students[i].name, temp_name);
            }

            //update age
            printf("  Current age  : %d\n", students[i].age);
            printf("  New age      : ");
            scanf("%d", &temp_age);
            clear_input_buffer();

            /* Only update if user entered a valid age */
            if (temp_age > 0) {
                students[i].age = temp_age;
            }

            //update marks
            printf("  Current marks: %.2f\n", students[i].marks);
            printf("  New marks    : ");
            scanf("%f", &temp_marks);
            clear_input_buffer();

            /* Only update if user entered a valid marks value */
            if (temp_marks >= 0) {
                students[i].marks = temp_marks;
            }

            printf("\n  Student record updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\n  No student found with ID %d.\n", update_id);
    }
}

//Main
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
            case 1: add_student();    break;
            case 2: view_students();  break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5:
                printf("\n  [Coming soon] Delete Student\n");
                break;
            case 6:
                printf("\n  [Coming soon] Save to File\n");
                break;
            case 7:
                printf("\n  Goodbye!\n");
                break;
            default:
                printf("\n  Invalid choice! Please enter 1 to 7.\n");
        }

    } while (choice != 7);

    return 0;
}