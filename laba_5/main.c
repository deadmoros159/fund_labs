#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    SUCCESS,
    ERROR_OPEN_FILE,
    ERROR_MEMORY,
    ERROR_INVALID_INPUT
} return_code;

static int is_word_char(char c) {
    return isalnum((unsigned char)c) || ispunct((unsigned char)c);
}

return_code wrap_line(const char* line, FILE* output) {
    if (line == NULL || output == NULL) {
        return ERROR_INVALID_INPUT;
    }
    
    int line_length = strlen(line);
    
    if (line_length <= 80) {
        if (fprintf(output, "%s\n", line) < 0) {
            return ERROR_OPEN_FILE;
        }
        return SUCCESS;
    }
    
    int current_pos = 0;
    
    while (current_pos < line_length) {
        int segment_end = current_pos + 80;
        
        if (segment_end >= line_length) {
            if (fprintf(output, "%s\n", line + current_pos) < 0) {
                return ERROR_OPEN_FILE;
            }
            break;
        }
        
        int break_pos = segment_end;
        
        while (break_pos > current_pos && !isspace((unsigned char)line[break_pos]) && 
               is_word_char(line[break_pos])) {
            break_pos--;
        }
        
        if (break_pos <= current_pos) {
            break_pos = segment_end;
            while (break_pos < line_length && !isspace((unsigned char)line[break_pos]) && 
                   is_word_char(line[break_pos])) {
                break_pos++;
            }
        }
        
        int segment_length = break_pos - current_pos;
        
        while (current_pos < break_pos && isspace((unsigned char)line[current_pos])) {
            current_pos++;
            segment_length--;
        }
        
        if (segment_length <= 0) {
            current_pos = break_pos;
            continue;
        }
        
        char* segment = (char*)malloc(segment_length + 1);
        if (segment == NULL) {
            return ERROR_MEMORY;
        }
        strncpy(segment, line + current_pos, segment_length);
        segment[segment_length] = '\0';
        
        if (segment_length <= 80) {
            if (fprintf(output, "%s\n", segment) < 0) {
                free(segment);
                return ERROR_OPEN_FILE;
            }
            free(segment);
            current_pos = break_pos;
            continue;
        }
        
        int seg_current = 0;
        
        while (seg_current < segment_length) {
            int seg_end = seg_current + 80;
            
            if (seg_end >= segment_length) {
                if (fprintf(output, "%s\n", segment + seg_current) < 0) {
                    free(segment);
                    return ERROR_OPEN_FILE;
                }
                break;
            }
            
            int seg_break = seg_end;
            while (seg_break > seg_current && !isspace((unsigned char)segment[seg_break]) && 
                   is_word_char(segment[seg_break])) {
                seg_break--;
            }
            
            if (seg_break <= seg_current) {
                seg_break = seg_end;
            }
            
            int part_length = seg_break - seg_current;
            char* part = (char*)malloc(part_length + 1);
            if (part == NULL) {
                free(segment);
                return ERROR_MEMORY;
            }
            strncpy(part, segment + seg_current, part_length);
            part[part_length] = '\0';
            
            if (part_length < 80) {
                int space_count = 0;
                for (int i = 0; i < part_length; i++) {
                    if (isspace((unsigned char)part[i])) {
                        space_count++;
                    }
                }
                
                if (space_count > 0) {
                    int extra_spaces = 80 - part_length;
                    int spaces_per_gap = extra_spaces / space_count;
                    int remainder = extra_spaces % space_count;
                    
                    char* formatted = (char*)malloc(81);
                    if (formatted == NULL) {
                        free(part);
                        free(segment);
                        return ERROR_MEMORY;
                    }
                    
                    int formatted_pos = 0;
                    for (int i = 0; i < part_length; i++) {
                        formatted[formatted_pos++] = part[i];
                        if (isspace((unsigned char)part[i])) {
                            for (int j = 0; j < spaces_per_gap; j++) {
                                formatted[formatted_pos++] = ' ';
                            }
                            if (remainder > 0) {
                                formatted[formatted_pos++] = ' ';
                                remainder--;
                            }
                        }
                    }
                    formatted[formatted_pos] = '\0';
                    
                    if (fprintf(output, "%s\n", formatted) < 0) {
                        free(formatted);
                        free(part);
                        free(segment);
                        return ERROR_OPEN_FILE;
                    }
                    free(formatted);
                } else {
                    if (fprintf(output, "%s\n", part) < 0) {
                        free(part);
                        free(segment);
                        return ERROR_OPEN_FILE;
                    }
                }
            } else {
                if (fprintf(output, "%s\n", part) < 0) {
                    free(part);
                    free(segment);
                    return ERROR_OPEN_FILE;
                }
            }
            
            free(part);
            seg_current = seg_break;
            
            while (seg_current < segment_length && isspace((unsigned char)segment[seg_current])) {
                seg_current++;
            }
        }
        
        free(segment);
        current_pos = break_pos;
        
        while (current_pos < line_length && isspace((unsigned char)line[current_pos])) {
            current_pos++;
        }
    }
    
    return SUCCESS;
}

return_code format_file(const char* input_path, const char* output_path) {
    if (input_path == NULL || output_path == NULL) {
        return ERROR_INVALID_INPUT;
    }
    
    FILE* input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        return ERROR_OPEN_FILE;
    }
    
    FILE* output_file = fopen(output_path, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return ERROR_OPEN_FILE;
    }
    
    char* line = NULL;
    size_t line_length = 0;
    size_t read;
    return_code result = SUCCESS;
    
    while ((read = getline(&line, &line_length, input_file)) != -1) {
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
            read--;
        }
        
        if (read > 0) {
            result = wrap_line(line, output_file);
            if (result != SUCCESS) {
                break;
            }
        }
    }
    
    if (line != NULL) {
        free(line);
    }
    
    fclose(input_file);
    fclose(output_file);
    
    return result;
}

int main() {
    char input_path[256];
    char output_path[256];
    
    printf("Text File Formatter\n\n");
    
    printf("Enter input file: ");
    if (fgets(input_path, sizeof(input_path), stdin) == NULL) {
        printf("Error reading input file\n");
        return 1;
    }
    
    printf("Enter output file: ");
    if (fgets(output_path, sizeof(output_path), stdin) == NULL) {
        printf("Error reading output path\n");
        return 1;
    }
    
    input_path[strcspn(input_path, "\n")] = '\0';
    output_path[strcspn(output_path, "\n")] = '\0';
    
    if (strlen(input_path) == 0 || strlen(output_path) == 0) {
        printf("Error empty paths\n");
        return 1;
    }
    
    return_code result = format_file(input_path, output_path);
    
    switch (result) {
        case SUCCESS:
            printf("File formatted and saved to '%s'\n", output_path);
            break;
        case ERROR_OPEN_FILE:
            printf("Error cannot open file\n");
            break;
        case ERROR_MEMORY:
            printf("Memory allocation error\n");
            break;
        case ERROR_INVALID_INPUT:
            printf("Invalid input parameters\n");
            break;
        default:
            printf("Unknown error\n");
            break;
    }
    
    return 0;
}
