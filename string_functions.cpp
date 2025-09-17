#include "string_functions.h"
const int INITIAL_SIZE = 128;
const int MAX_STR_LENGTH = 500;

/*
1. что такое файл "str.h func.cpp"?
2. добавь мейкфайл или скрипт которым это дело собирать
5. когда делаешь realloc - та же проблема, не инициализируется новый участок
*/


// prints strings character by character until the NULL character is encountered
// str - ������������ ������
int my_puts(const char *str)
    {

    if (str == NULL)
        {
        return EOF;
        }

    // ���� �� 0
    for ( ; *str != '\0' ; str++ )
        {
        if (putchar(*str) == EOF)
            {
            return EOF;
            }
        }

    // error -> EOF
    return (putchar('\n') == EOF) ? EOF : 0;

    }


// find the first occurrence of a character
// str - ������������ ������
// ch  - �������, ������� �� ���� � ������ (int ������������� ������ �������, ����� ����� �������)
char *my_strchr(const char *str, int ch)
    {

    if (str == NULL)
        {
        return NULL;
        }

    // int -> char
    char target = (char)ch;

    for ( ; *str != '\0' ; str++ )
        {
        if (*str == target)
            {
            return (char *)str;
            }
        }

    return (target == '\0') ? (char *)str : NULL;

    }


// length of the string
// str - ������������ ������
int my_strlen(const char *str)
    {

    // ��� �������� chars � str
    int counter = 0;

    for ( ; *str != '\0' ; str++ )
        {
        counter++;
        }

    return counter;

    }


// copy one string into another (with 0?)
// dest - ������ ���� ��������
// src  - ������ ������� ��������
char *my_strcpy(char *dest, const char *src)
    {

    // ptr - running pointer
    // ��� ptr ����������� �� ��������� �� ������, �.�. dest �� �������
    // � ��� ptr ����� �� dest
    char *ptr = dest;

    while (*src != '\0')
        {
        // ������� ptr �� dest
        *ptr++ = *src++;
        }

    // ���������� � �����, ����� � ����� dest �� ���� ������
    *ptr = '\0';
    return dest;

    }


// copy a specified number of characters from one string to another
// dest - ������ ���� ��������
// src  - ������ ������� ��������
// n    - ���-�� ���������� ��������
char *my_strncpy(char *dest, const char *src, size_t n)
    {

    char *ptr = dest;

    // �������� �������
    for (size_t i = 0; i < n && src[i] != '\0'; i++)
        {
        *ptr++ = src[i];
        }

    for (size_t i = ptr - dest; i < n; i++)
        {
        *ptr++ = '\0';
        }

    return dest;

    }


// append a copy in the destination string (with 0)
// dest - ������ ���� ���������
// src  - ������ ������� ���������
char *my_strcat(char *dest, const char *src)
    {

    char *ptr = dest;

    while (*ptr != '\0')
        {
        ptr++;
        }

    while (*src != '\0')
        {
        *ptr++ = *src++;
        }

    *ptr = '\0';
    return dest;

    }


// append not more than n characters (with 0)
// dest - ������ ���� ���������
// src  - ������ ������� ���������
// n    - ���-�� ��� ��������
char *my_strncat(char *dest, const char *src, size_t n)
    {

    char *ptr = dest;
    size_t i = 0;

    while (*ptr != '\0')
        {
        ptr++;
        }

    while (i < n && src[i] != '\0')
        {
        *ptr++ = src[i++];
        }

    *ptr = '\0';
    return dest;

    }


// converts the numbers in string form to their integer value
// accepts a string as a parameter and yields an integer value in return
// strg - ������������� ������
int my_atoi(const char *strg)
    {

    int result = 0;
    int sign = 1;

    // ������� ��������
    while (*strg == ' ')
        {
        strg++;
        }

    // ��������� �����
    if (*strg == '-')
        {
        sign = -1;
        strg++;
        }
    else if (*strg == '+')
        {
        strg++;
        }

    // ��������������
    while (*strg >= '0' && *strg <= '9')
        {
        result = result * 10 + (*strg - '0');
        strg++;
        }

    return sign * result;

    }


// reads the given number of characters of a line
// from the input stream and stores it into the specified string
// buff   - ��������� ����� � �������� �������
// n      - ���-�� ��������
// stream - ������� �����
char *my_fgets(char *buff, int n, FILE *stream)
    {

    int ch = 0;
    char *ptr = buff;

    if (n <= 0) return NULL;

    // ������ �� n-1 �������� ��� ����� ������/EOF
    for (int i = 0; i < n - 1; i++)
        {
        ch = fgetc(stream);

        if (ch == EOF)
            {
            if (ptr == buff) return NULL; // ������ �� ���������
            break;
            }

        *ptr++ = (char)ch;

        if (ch == '\n')
            {
            break;
            }
        }

    *ptr = '\0';
    return buff;

    }


// returns a pointer to the duplicated string s
// ���� ������� �� ������ ����������� ������, ��� ������ ������ ���������� ���
// s - ���������� ������
char *my_strdup(const char *s)
    {

    if (s == NULL) return NULL;

    size_t len = strlen(s) + 1;
    char *new_str = (char *)calloc(MAX_STR_LENGTH, len);

    if (new_str == NULL) return NULL;

    return (char *)memcpy(new_str, s, len);

    }


// get a string from a file
// lineptr - ��������� �� ��������� ������
// n       - ������ ������
// stream  - ����

// pos - ������� � ������
// ch  - ����������� ������
size_t my_getline(char **lineptr, size_t *n, FILE *stream)
    {

    // �������� ������� ����������
    if (lineptr == NULL || n == NULL || stream == NULL)
        {
        return -1;
        }

    size_t pos = 0;
    int ch = 0;

    // ��������� ������, ���� �� ��������
    if (*lineptr == NULL || *n == 0)
        {
        *n = INITIAL_SIZE;
        *lineptr = (char *)calloc(MAX_STR_LENGTH, *n);
        if (*lineptr == NULL) return -1;
        }

    while ((ch = fgetc(stream)) != EOF)
        {
        // ����������� ����� ��� �������������
        if (pos + 1 >= *n)
            {
            size_t new_size = *n * 2;
            char *new_ptr = (char *)realloc(*lineptr, new_size);
            if (new_ptr == NULL) return -1;
            *lineptr = new_ptr;
            *n = new_size;
            }

        (*lineptr)[pos++] = (char)ch;

        if (ch == '\n')
            {
            break;
            }
        }

    if (pos == 0 && ch == EOF)
        {
        return -1; // ����� �����
        }

    (*lineptr)[pos] = '\0';
    return (size_t)pos;

    }


// takes two strings s1 and s2 as arguments and finds the first occurrence of the string s2 in the string s1
// s1 - исходная строка
// s2 - строка которую ищем в s1
// возвращает указатель на первый символ s2 в s1
char *my_strstr(const char *s1, const char *s2)
    {

    if (s1 == NULL || s2 == NULL)
        {
        return NULL;
        }
    
    // Если s2 пустая строка - возвращаем s1
    if (*s2 == '\0')
        {
        return (char *)s1;
        }
    
    // Проходим по s1
    while (*s1 != '\0')
        {
        const char *h = s1;
        const char *n = s2;
        
        // чек подстрок
        while (*h != '\0' && *n != '\0' && *h == *n)
            {
            h++;
            n++;
            }
        
        // конец s2 -> есть совпадение
        if (*n == '\0')
            {
            return (char *)s1;
            }
        
        s1++;
        }
    
    return NULL; // нет s2
    
    }