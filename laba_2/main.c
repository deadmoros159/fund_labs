#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

// a
void* memchr(const void* str, int c, size_t n) {
    if (str == NULL) {
        return NULL;
    }
    
    const unsigned char* p = (const unsigned char*)str;
    unsigned char ch = (unsigned char)c;
    
    for (size_t i = 0; i < n; i++) {
        if (p[i] == ch) {
            return (void*)(p + i);
        }
    }
    
    return NULL;
}

// b
int memcmp(const void* str1, const void* str2, size_t n) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    const unsigned char* p1 = (const unsigned char*)str1;
    const unsigned char* p2 = (const unsigned char*)str2;
    
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    
    return 0;
}

// c
void* memcpy(void* dest, const void* src, size_t n) {
    if (dest == NULL || src == NULL) {
        return dest;
    }
    
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    
    return dest;
}

// d
void* memset(void* str, int c, size_t n) {
    if (str == NULL) {
        return NULL;
    }
    
    unsigned char* ptr = (unsigned char*)str;
    unsigned char value = (unsigned char)c;
    
    for (size_t i = 0; i < n; i++) {
        ptr[i] = value;
    }
    
    return str;
}

// e
char* strncat(char* dest, const char* src, size_t n) {
    if (dest == NULL || src == NULL) {
        return dest;
    }
    
    char* dest_end = dest;
    while (*dest_end != '\0') {
        dest_end++;
    }
    
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest_end[i] = src[i];
    }
    
    dest_end[i] = '\0';
    
    return dest;
}

// f
char* strchr(const char* str, int c) {
    if (str == NULL) {
        return NULL;
    }
    
    unsigned char target = (unsigned char)c;
    
    while (*str != '\0') {
        if ((unsigned char)*str == target) {
            return (char*)str;
        }
        str++;
    }
    
    if (target == '\0') {
        return (char*)str;
    }
    
    return NULL;
}

// g
int strncmp(const char* str1, const char* str2, size_t n) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    const unsigned char* p1 = (const unsigned char*)str1;
    const unsigned char* p2 = (const unsigned char*)str2;
    
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
        if (p1[i] == '\0') {
            return 0;
        }
    }
    
    return 0;
}

// h
char* strncpy(char* dest, const char* src, size_t n) {
    if (dest == NULL || src == NULL) {
        return dest;
    }
    
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    
    return dest;
}

// i
size_t strcspn(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t count = 0;
    
    while (str1[count] != '\0') {
        const char* reject = str2;
        while (*reject != '\0') {
            if (str1[count] == *reject) {
                return count;
            }
            reject++;
        }
        count++;
    }
    
    return count;
}

// k
size_t strlen(const char* str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    
    return length;
}

// l
char* strpbrk(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    
    while (*str1 != '\0') {
        const char* check = str2;
        while (*check != '\0') {
            if (*str1 == *check) {
                return (char*)str1;
            }
            check++;
        }
        str1++;
    }
    
    return NULL;
}

// m
char* strrchr(const char* str, int c) {
    if (str == NULL) {
        return NULL;
    }
    
    const char* last_occurrence = NULL;
    unsigned char target = (unsigned char)c;
    
    while (*str != '\0') {
        if ((unsigned char)*str == target) {
            last_occurrence = str;
        }
        str++;
    }
    
    if (target == '\0') {
        return (char*)str;
    }
    
    return (char*)last_occurrence;
}

// n
char* strstr(const char* haystack, const char* needle) {
    if (haystack == NULL || needle == NULL) {
        return NULL;
    }
    
    if (*needle == '\0') {
        return (char*)haystack;
    }
    
    while (*haystack != '\0') {
        const char* h = haystack;
        const char* n = needle;
        
        while (*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }
        
        if (*n == '\0') {
            return (char*)haystack;
        }
        
        haystack++;
    }
    
    return NULL;
}

// o
char* strtok(char* str, const char* delim) {
    static char* saved_ptr = NULL;
    
    if (delim == NULL) {
        return NULL;
    }

    if (str != NULL) {
        saved_ptr = str;
    }
    else if (saved_ptr == NULL) {
        return NULL;
    }

    char* token_start = saved_ptr;
    while (*token_start != '\0') {
        const char* d = delim;
        int is_delim = 0;
        while (*d != '\0') {
            if (*token_start == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (!is_delim) {
            break;
        }
        token_start++;
    }
    
    if (*token_start == '\0') {
        saved_ptr = NULL;
        return NULL;
    }

    char* token_end = token_start;
    while (*token_end != '\0') {
        const char* d = delim;
        int is_delim = 0;
        while (*d != '\0') {
            if (*token_end == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (is_delim) {
            break;
        }
        token_end++;
    }

    if (*token_end == '\0') {
        saved_ptr = NULL;
    } else {
        *token_end = '\0';
        saved_ptr = token_end + 1;
    }
    
    return token_start;
}

int main() {
    printf("Testing all string functions:\n\n");
    
    printf("1. memchr:\n");
    char str1[] = "Hello, World!";
    char* result1 = (char*)memchr(str1, 'W', strlen(str1));
    if (result1 != NULL) {
        printf("   Found 'W' at position: %ld\n", result1 - str1);
    } else {
        printf("   'W' not found\n");
    }
    
    printf("\n2. memcmp:\n");
    char str2a[] = "apple";
    char str2b[] = "apple";
    int result2 = memcmp(str2a, str2b, 5);
    printf("   'apple' vs 'apple': %d\n", result2);
    
    printf("\n3. memcpy:\n");
    char src3[] = "Source";
    char dest3[10];
    memcpy(dest3, src3, 7);
    printf("   Copied: '%s'\n", dest3);

    printf("\n4. memset:\n");
    char str4[10];
    memset(str4, 'A', 5);
    str4[5] = '\0';
    printf("   Filled with 'A': '%s'\n", str4);

    printf("\n5. strncat:\n");
    char dest5[50] = "Hello";
    strncat(dest5, ", World", 8);
    printf("   Concatenated: '%s'\n", dest5);

    printf("\n6. strchr:\n");
    char str6[] = "Hello";
    char* result6 = strchr(str6, 'e');
    if (result6 != NULL) {
        printf("   Found 'e' at position: %ld\n", result6 - str6);
    }

    printf("\n7. strncmp:\n");
    char str7a[] = "apple";
    char str7b[] = "application";
    int result7 = strncmp(str7a, str7b, 3);
    printf("   'apple' vs 'application' (first 3 chars): %d\n", result7);

    printf("\n8. strncpy:\n");
    char src8[] = "Source";
    char dest8[10];
    strncpy(dest8, src8, 4);
    dest8[4] = '\0';
    printf("   Copied 4 chars: '%s'\n", dest8);

    printf("\n9. strcspn:\n");
    char str9[] = "hello";
    size_t result9 = strcspn(str9, "aeiou");
    printf("   Length until vowel in 'hello': %zu\n", result9);

    printf("\n10. strlen:\n");
    char str10[] = "Hello, World!";
    size_t result10 = strlen(str10);
    printf("   Length of 'Hello, World!': %zu\n", result10);

    printf("\n11. strpbrk:\n");
    char str11[] = "hello world";
    char* result11 = strpbrk(str11, "aeiou");
    if (result11 != NULL) {
        printf("   First vowel in 'hello world': '%c'\n", *result11);
    }

    printf("\n12. strrchr:\n");
    char str12[] = "hello";
    char* result12 = strrchr(str12, 'l');
    if (result12 != NULL) {
        printf("   Last 'l' in 'hello' at position: %ld\n", result12 - str12);
    }

    printf("\n13. strstr:\n");
    char str13[] = "hello world";
    char* result13 = strstr(str13, "world");
    if (result13 != NULL) {
        printf("   Found 'world' in 'hello world'\n");
    }

    printf("\n14. strtok:\n");
    char str14[] = "hello,world;test";
    printf("   Tokens: ");
    char* token = strtok(str14, ",;");
    while (token != NULL) {
        printf("'%s' ", token);
        token = strtok(NULL, ",;");
    }
    printf("\n");
    
    return 0;
}
