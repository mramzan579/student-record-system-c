/*
 * student_record_system.c
 * Student Record System 
 * Set up the project structure, define the Student struct,
 * and build the main menu system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants 
#define MAX_STUDENTS  100          /* maximum students allowed   */
#define NAME_LEN       50          /* maximum length of a name   */
#define FILE_NAME     "students.txt"  /* output file name        */

//Student struct
/* Groups all information about one student into a single unit.
   This is the core data structure of the entire program. */
struct Student {
    int   id;
    char  name[NAME_LEN];
    int   age;
    float marks;   /* float stores decimal values like 85.5 */
};

/* ── Global student list ────────────────────────────────────── */
struct Student students[MAX_STUDENTS];  /* holds all records     */
int student_count = 0;                  /* how many are stored   */

/* ================================================================
   clear_input_buffer()
   Drains leftover characters from stdin after every scanf.
   Prevents input bugs when switching between numbers and strings.
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
   Called at the start of every loop in main().
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

// Main 
int main(void)
{
    int choice;

    /* Welcome banner */
    printf("========================================\n");
    printf("  STUDENT RECORD MANAGEMENT SYSTEM      \n");
    printf("========================================\n");
    printf("  Manage student records with ease.\n");
    printf("  Maximum capacity: %d students.\n", MAX_STUDENTS);

    /* Main loop — keeps running until user picks Exit */
    do {
        show_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("\n  [Coming soon] Add Student\n");
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