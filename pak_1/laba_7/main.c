#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void remove_leading_zeros(char *str)
{
    int len = strlen(str);
    int first_non_zero = -1;

    for (int i = 0; i < len; i++) {
        if (str[i] != '0') {
            first_non_zero = i;
            break;
        }
    }

    if (first_non_zero > 0) {
        int new_len = len - first_non_zero;
        for (int i = 0; i < new_len; i++) {
            str[i] = str[i + first_non_zero];
        }
        str[new_len] = '\0';
    }
}

int char_to_digit(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' &&c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' &&c <= 'z') return c - 'a' + 10;
}

void get_nums(FILE* input)
{
    FILE* output = fopen("output.txt", "w");
    char c;
    int size_buff = 0;
    char all_nums[37] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char buffer[100];
    while ((c = fgetc(input)) != EOF)
    {
        if (c == '\n' || c=='\t' || c == ' ')
        {
            if (size_buff > 0)
            {
                buffer[size_buff] = '\0';
                //ПОИСК МИНИМАЛЬНОЙ БАЗЫ
                int min_base = 2;
                char min_char_base;
                for (int i = 0; i < size_buff; i++)
                {
                    int temp = char_to_digit(buffer[i]);
                    if (min_base < temp)
                    {
                        min_base = temp;
                        min_char_base = buffer[i];
                    }
                }
                min_base++;

                //ФУНКЦИЯ ВЫПОЛНЕНИЯ РАБОТЫ С БУФФЕРОМ...
                int decimal = 0;
                for (int i = 0; i < size_buff; i++)
                {
                    int temp = char_to_digit(buffer[i]);
                    decimal += temp * pow(min_base, size_buff - i - 1);
                }
                // printf("Result is %d %d\n", min_base, decimal);

                //вывод в файл
                remove_leading_zeros(buffer);
                fprintf(output, "%s    ", buffer);
                
                fprintf(output, "in min base: %d    ", min_base);
                
                fprintf(output, "in decimal: %d\n", decimal);
                
                





                //ИЗБАВЛЕНИЕ ОТ БУФФЕРА
                for (int i = 0; i < size_buff; i++)
                {
                    buffer[i] = 0;
                }
                size_buff = 0;
                // printf("ZAPISANO! & OCHISTCHENO\n");
            }
            continue;
        }

        int c_is_correct = 0;
        for (int i = 0; i < 37; i++)
        {
            if (all_nums[i] == c)
            {
                c_is_correct = 1;
                break;
            }
        }
        if (c_is_correct)
        {
            buffer[size_buff] = c;
            size_buff++;
        }


    }
    fclose(output);
    
}

int main(int argc, char const *argv[])
{


    FILE* file_in = fopen("input.txt", "r");
    get_nums(file_in);
    fclose(file_in);
    return 0;
}
