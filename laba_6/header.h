#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    unsigned int id;
    char* first_name;
    char* last_name;
    char* group;
    unsigned char* grades;
    int grades_count;
} Student;

typedef struct {
    Student* students;
    int count;
    int capacity;
} StudentDatabase;

typedef enum {
    SUCCESS,
    ERROR_OPEN_FILE,
    ERROR_MEMORY,
    ERROR_INVALID_INPUT,
    ERROR_NOT_FOUND
} return_code;

StudentDatabase* create_database();
return_code load_students_from_file(StudentDatabase* db, const char* filename);
return_code find_student_by_id(StudentDatabase* db, unsigned int id, Student** result);
return_code find_students_by_last_name(StudentDatabase* db, const char* last_name, Student*** results, int* count);
return_code find_students_by_first_name(StudentDatabase* db, const char* first_name, Student*** results, int* count);
return_code find_students_by_group(StudentDatabase* db, const char* group, Student*** results, int* count);
void sort_students_by_id(StudentDatabase* db);
void sort_students_by_last_name(StudentDatabase* db);
void sort_students_by_first_name(StudentDatabase* db);
void sort_students_by_group(StudentDatabase* db);
double calculate_student_average(const Student* student);
double calculate_overall_average(StudentDatabase* db);
return_code save_student_to_trace_file(const Student* student, const char* filename);
return_code save_top_students_to_trace_file(StudentDatabase* db, const char* filename);
void free_database(StudentDatabase* db);
int is_alpha_string(const char* str);

#endif
