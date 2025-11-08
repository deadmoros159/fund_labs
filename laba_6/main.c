#include "header.h"

StudentDatabase* create_database() {
    StudentDatabase* db = (StudentDatabase*)malloc(sizeof(StudentDatabase));
    if (!db) return NULL;
    
    db->capacity = 10;
    db->count = 0;
    db->students = (Student*)malloc(db->capacity * sizeof(Student));
    if (!db->students) {
        free(db);
        return NULL;
    }
    
    return db;
}

return_code load_students_from_file(StudentDatabase* db, const char* filename) {
    if (!db || !filename) return ERROR_INVALID_INPUT;
    
    FILE* file = fopen(filename, "r");
    if (!file) return ERROR_OPEN_FILE;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (db->count >= db->capacity) {
            db->capacity *= 2;
            Student* new_students = (Student*)realloc(db->students, db->capacity * sizeof(Student));
            if (!new_students) {
                fclose(file);
                return ERROR_MEMORY;
            }
            db->students = new_students;
        }
        
        Student* student = &db->students[db->count];
        student->grades_count = 5;
        student->grades = (unsigned char*)malloc(student->grades_count * sizeof(unsigned char));
        if (!student->grades) {
            fclose(file);
            return ERROR_MEMORY;
        }
        
        char first_name[50], last_name[50], group[50];
        int scanned = sscanf(line, "%u %49s %49s %49s %hhu %hhu %hhu %hhu %hhu",
                           &student->id, first_name, last_name, group,
                           &student->grades[0], &student->grades[1],
                           &student->grades[2], &student->grades[3],
                           &student->grades[4]);
        
        if (scanned == 9 && is_alpha_string(first_name) && is_alpha_string(last_name)) {
            student->first_name = strdup(first_name);
            student->last_name = strdup(last_name);
            student->group = strdup(group);
            
            if (!student->first_name || !student->last_name || !student->group) {
                fclose(file);
                return ERROR_MEMORY;
            }
            
            db->count++;
        } else {
            free(student->grades);
        }
    }
    
    fclose(file);
    return SUCCESS;
}

int is_alpha_string(const char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha((unsigned char)str[i])) {
            return 0;
        }
    }
    return str[0] != '\0';
}

return_code find_student_by_id(StudentDatabase* db, unsigned int id, Student** result) {
    if (!db || !result) return ERROR_INVALID_INPUT;
    
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            *result = &db->students[i];
            return SUCCESS;
        }
    }
    
    return ERROR_NOT_FOUND;
}

return_code find_students_by_last_name(StudentDatabase* db, const char* last_name, Student*** results, int* count) {
    if (!db || !last_name || !results || !count) return ERROR_INVALID_INPUT;
    
    *count = 0;
    Student** found = (Student**)malloc(db->count * sizeof(Student*));
    if (!found) return ERROR_MEMORY;
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].last_name, last_name) == 0) {
            found[(*count)++] = &db->students[i];
        }
    }
    
    if (*count == 0) {
        free(found);
        return ERROR_NOT_FOUND;
    }
    
    *results = found;
    return SUCCESS;
}

return_code find_students_by_first_name(StudentDatabase* db, const char* first_name, Student*** results, int* count) {
    if (!db || !first_name || !results || !count) return ERROR_INVALID_INPUT;
    
    *count = 0;
    Student** found = (Student**)malloc(db->count * sizeof(Student*));
    if (!found) return ERROR_MEMORY;
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].first_name, first_name) == 0) {
            found[(*count)++] = &db->students[i];
        }
    }
    
    if (*count == 0) {
        free(found);
        return ERROR_NOT_FOUND;
    }
    
    *results = found;
    return SUCCESS;
}

return_code find_students_by_group(StudentDatabase* db, const char* group, Student*** results, int* count) {
    if (!db || !group || !results || !count) return ERROR_INVALID_INPUT;
    
    *count = 0;
    Student** found = (Student**)malloc(db->count * sizeof(Student*));
    if (!found) return ERROR_MEMORY;
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].group, group) == 0) {
            found[(*count)++] = &db->students[i];
        }
    }
    
    if (*count == 0) {
        free(found);
        return ERROR_NOT_FOUND;
    }
    
    *results = found;
    return SUCCESS;
}

int compare_by_id(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return (studentA->id > studentB->id) - (studentA->id < studentB->id);
}

int compare_by_last_name(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return strcmp(studentA->last_name, studentB->last_name);
}

int compare_by_first_name(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return strcmp(studentA->first_name, studentB->first_name);
}

int compare_by_group(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;
    return strcmp(studentA->group, studentB->group);
}

void sort_students_by_id(StudentDatabase* db) {
    if (db) qsort(db->students, db->count, sizeof(Student), compare_by_id);
}

void sort_students_by_last_name(StudentDatabase* db) {
    if (db) qsort(db->students, db->count, sizeof(Student), compare_by_last_name);
}

void sort_students_by_first_name(StudentDatabase* db) {
    if (db) qsort(db->students, db->count, sizeof(Student), compare_by_first_name);
}

void sort_students_by_group(StudentDatabase* db) {
    if (db) qsort(db->students, db->count, sizeof(Student), compare_by_group);
}

double calculate_student_average(const Student* student) {
    if (!student || student->grades_count == 0) return 0.0;
    
    double sum = 0;
    for (int i = 0; i < student->grades_count; i++) {
        sum += student->grades[i];
    }
    return sum / student->grades_count;
}

double calculate_overall_average(StudentDatabase* db) {
    if (!db || db->count == 0) return 0.0;
    
    double total_sum = 0;
    for (int i = 0; i < db->count; i++) {
        total_sum += calculate_student_average(&db->students[i]);
    }
    return total_sum / db->count;
}

return_code save_student_to_trace_file(const Student* student, const char* filename) {
    if (!student || !filename) return ERROR_INVALID_INPUT;
    
    FILE* file = fopen(filename, "w");
    if (!file) return ERROR_OPEN_FILE;
    
    double average = calculate_student_average(student);
    fprintf(file, "Student ID: %u\n", student->id);
    fprintf(file, "Name: %s %s\n", student->first_name, student->last_name);
    fprintf(file, "Group: %s\n", student->group);
    fprintf(file, "Average grade: %.2f\n", average);
    
    fclose(file);
    return SUCCESS;
}

return_code save_top_students_to_trace_file(StudentDatabase* db, const char* filename) {
    if (!db || !filename) return ERROR_INVALID_INPUT;
    
    FILE* file = fopen(filename, "w");
    if (!file) return ERROR_OPEN_FILE;
    
    double overall_average = calculate_overall_average(db);
    fprintf(file, "Overall average: %.2f\n\n", overall_average);
    fprintf(file, "Students with above average grades:\n");
    
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        double student_avg = calculate_student_average(&db->students[i]);
        if (student_avg > overall_average) {
            fprintf(file, "%s %s (Average: %.2f)\n", 
                    db->students[i].last_name, 
                    db->students[i].first_name, 
                    student_avg);
            found = 1;
        }
    }
    
    if (!found) {
        fprintf(file, "No students with above average grades found.\n");
    }
    
    fclose(file);
    return SUCCESS;
}

void free_database(StudentDatabase* db) {
    if (!db) return;
    
    for (int i = 0; i < db->count; i++) {
        free(db->students[i].first_name);
        free(db->students[i].last_name);
        free(db->students[i].group);
        free(db->students[i].grades);
    }
    
    free(db->students);
    free(db);
}

void print_menu() {
    printf("\n=== Student Management System ===\n");
    printf("1. Find student by ID\n");
    printf("2. Find students by last name\n");
    printf("3. Find students by first name\n");
    printf("4. Find students by group\n");
    printf("5. Sort students by ID\n");
    printf("6. Sort students by last name\n");
    printf("7. Sort students by first name\n");
    printf("8. Sort students by group\n");
    printf("9. Save student data to trace file\n");
    printf("10. Save top students to trace file\n");
    printf("11. Display all students\n");
    printf("0. Exit\n");
    printf("Choose option: ");
}

void display_student(const Student* student) {
    if (!student) return;
    
    printf("ID: %u, Name: %s %s, Group: %s, Grades: ",
           student->id, student->first_name, student->last_name, student->group);
    for (int i = 0; i < student->grades_count; i++) {
        printf("%u ", student->grades[i]);
    }
    printf("(Avg: %.2f)\n", calculate_student_average(student));
}

void display_students(StudentDatabase* db) {
    if (!db || db->count == 0) {
        printf("No students to display.\n");
        return;
    }
    
    printf("\n=== All Students (%d) ===\n", db->count);
    for (int i = 0; i < db->count; i++) {
        display_student(&db->students[i]);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Failed format\n");
        return 1;
    }
    
    StudentDatabase* db = create_database();
    if (!db) {
        printf("Error of creating database\n");
        return 1;
    }
    
    return_code result = load_students_from_file(db, argv[1]);
    if (result != SUCCESS) {
        printf("Error of loading students from file\n");
        free_database(db);
        return 1;
    }
    
    printf("Loaded %d students from %s\n", db->count, argv[1]);
    
    char trace_file[256] = "trace.txt";
    if (argc >= 3) {
        strcpy(trace_file, argv[2]);
    }
    
    int choice;
    char input[100];
    
    do {
        print_menu();
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        choice = atoi(input);
        
        switch (choice) {
            case 1: {
                printf("Enter student ID: ");
                if (fgets(input, sizeof(input), stdin)) {
                    unsigned int id = (unsigned int)atoi(input);
                    Student* student;
                    result = find_student_by_id(db, id, &student);
                    if (result == SUCCESS) {
                        display_student(student);
                    } else {
                        printf("Student with ID %u not found.\n", id);
                    }
                }
                break;
            }
            
            case 2: {
                printf("Enter last name: ");
                if (fgets(input, sizeof(input), stdin)) {
                    input[strcspn(input, "\n")] = '\0';
                    Student** results;
                    int count;
                    result = find_students_by_last_name(db, input, &results, &count);
                    if (result == SUCCESS) {
                        printf("Found %d student(s):\n", count);
                        for (int i = 0; i < count; i++) {
                            display_student(results[i]);
                        }
                        free(results);
                    } else {
                        printf("No students with last name '%s' found.\n", input);
                    }
                }
                break;
            }
            
            case 3: {
                printf("Enter first name: ");
                if (fgets(input, sizeof(input), stdin)) {
                    input[strcspn(input, "\n")] = '\0';
                    Student** results;
                    int count;
                    result = find_students_by_first_name(db, input, &results, &count);
                    if (result == SUCCESS) {
                        printf("Found %d student(s):\n", count);
                        for (int i = 0; i < count; i++) {
                            display_student(results[i]);
                        }
                        free(results);
                    } else {
                        printf("No students with first name '%s' found.\n", input);
                    }
                }
                break;
            }
            
            case 4: {
                printf("Enter group: ");
                if (fgets(input, sizeof(input), stdin)) {
                    input[strcspn(input, "\n")] = '\0';
                    Student** results;
                    int count;
                    result = find_students_by_group(db, input, &results, &count);
                    if (result == SUCCESS) {
                        printf("Found %d student(s):\n", count);
                        for (int i = 0; i < count; i++) {
                            display_student(results[i]);
                        }
                        free(results);
                    } else {
                        printf("No students in group '%s' found.\n", input);
                    }
                }
                break;
            }
            
            case 5:
                sort_students_by_id(db);
                printf("Students sorted by ID.\n");
                display_students(db);
                break;
                
            case 6:
                sort_students_by_last_name(db);
                printf("Students sorted by last name.\n");
                display_students(db);
                break;
                
            case 7:
                sort_students_by_first_name(db);
                printf("Students sorted by first name.\n");
                display_students(db);
                break;
                
            case 8:
                sort_students_by_group(db);
                printf("Students sorted by group.\n");
                display_students(db);
                break;
                
            case 9: {
                printf("Enter student ID to save: ");
                if (fgets(input, sizeof(input), stdin)) {
                    unsigned int id = (unsigned int)atoi(input);
                    Student* student;
                    result = find_student_by_id(db, id, &student);
                    if (result == SUCCESS) {
                        result = save_student_to_trace_file(student, trace_file);
                        if (result == SUCCESS) {
                            printf("Student data saved to file\n");
                        } else {
                            printf("Error saving student data.\n");
                        }
                    } else {
                        printf("Student with ID %u not found.\n", id);
                    }
                }
                break;
            }
            
            case 10:
                result = save_top_students_to_trace_file(db, trace_file);
                if (result == SUCCESS) {
                    printf("Top students data saved to file\n");
                } else {
                    printf("Error saving top students.\n");
                }
                break;
                
            case 11:
                display_students(db);
                break;
                
            case 0:
                break;
                
            default:
                printf("Invalid key.\n");
                break;
        }
        
    } while (choice != 0);
    
    free_database(db);
    return 0;
}
