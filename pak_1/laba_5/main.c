#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// флаг -a

int is_latin_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_arabic_digit(char c) {
    return c >= '0' && c <= '9';
}

int remove_digits(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return -1;
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        if (!is_arabic_digit(c)) {
            fputc(c, output);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}

int count_letters(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (is_latin_letter(line[i])) {
                count++;
            }
        }
        fprintf(output, "%d\n", count);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int count_special(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            char c = line[i];
            if (!is_latin_letter(c) && !is_arabic_digit(c) && c != ' ' && c != '\n' && c != '\r') {
                count++;
            }
        }
        fprintf(output, "%d\n", count);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int replace_with_hex(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return -1;
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        if (is_arabic_digit(c) == 1 || c == '\n' || c == ',' || c == '\t' || c == ' ') {
            fputc(c, output);
        } else {
            fprintf(output, "%X", (unsigned char)c);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Invalid input\n");
        return 1;
    }

    char *flag = argv[1];
    char *input_file = argv[2];
    char output_file[256] = {0};

    if (strlen(flag) >= 2 && flag[1] == 'n') {
        if (argc < 4) {
            printf(" Output file required for flag %s\n", flag);
            return 1;
        }
        strncpy(output_file, argv[3], sizeof(output_file) - 1);
    } else {
        char *last_slash = strrchr(input_file, '/');
        char *last_backslash = strrchr(input_file, '\\');
        char *filename = input_file;
        
        if (last_slash || last_backslash) {
            filename = (last_slash > last_backslash) ? last_slash + 1 : last_backslash + 1;
        }
        
        snprintf(output_file, sizeof(output_file), "out_%s", filename);
    }

    char action_flag[3] = {0};
    if (strlen(flag) >= 2) {
        if (flag[1] == 'n' && strlen(flag) >= 3) {
            action_flag[0] = flag[0];
            action_flag[1] = flag[2];
        } else {
            action_flag[0] = flag[0];
            action_flag[1] = flag[1];
        }
    } else {
        printf("Invalid flag format\n");
        return 1;
    }


    // Флаги
    int result;
    if (strcmp(action_flag, "-d") == 0 || strcmp(action_flag, "/d") == 0) {
        result = remove_digits(input_file, output_file);
    } else if (strcmp(action_flag, "-i") == 0 || strcmp(action_flag, "/i") == 0) {
        result = count_letters(input_file, output_file);
    } else if (strcmp(action_flag, "-s") == 0 || strcmp(action_flag, "/s") == 0) {
        result = count_special(input_file, output_file);
    } else if (strcmp(action_flag, "-a") == 0 || strcmp(action_flag, "/a") == 0) {
        result = replace_with_hex(input_file, output_file);
    } else {
        printf("Invalid flag %s\n", flag);
        return 1;
    }

    if (result != 0) {
        printf("Invalid processing file\n");
        return 1;
    }

    printf("Output written to: %s\n", output_file);
    return 0;
}
