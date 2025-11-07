#include "header.h"

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
        int break_pos = current_pos + 80;
        
        if (break_pos >= line_length) {
            if (fprintf(output, "%s\n", line + current_pos) < 0) {
                return ERROR_OPEN_FILE;
            }
            break;
        }
        
        int actual_break = break_pos;
        
        while (actual_break > current_pos && is_word_char(line[actual_break])) {
            actual_break--;
        }
        
        if (actual_break == current_pos) {
            while (actual_break < line_length && is_word_char(line[actual_break])) {
                actual_break++;
            }
        }
        
        int chunk_length = actual_break - current_pos;
        if (chunk_length > 0) {
            while (current_pos < actual_break && isspace((unsigned char)line[current_pos])) {
                current_pos++;
                chunk_length--;
            }
            
            if (chunk_length > 0) {
                char* chunk = (char*)malloc(chunk_length + 1);
                if (chunk == NULL) {
                    return ERROR_MEMORY;
                }
                
                strncpy(chunk, line + current_pos, chunk_length);
                chunk[chunk_length] = '\0';
                
                if (fprintf(output, "%s\n", chunk) < 0) {
                    free(chunk);
                    return ERROR_OPEN_FILE;
                }
                
                free(chunk);
            }
        }
        
        current_pos = actual_break;
        
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
        printf("Error empty pathes\n");
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
            printf("ERROR_MEMORY\n");
            break;
        case ERROR_INVALID_INPUT:
            printf("ERROR_INVALID_INPUT\n");
            break;
        default:
            printf("Unknown error\n");
            break;
    }
    
    return 0;
}
