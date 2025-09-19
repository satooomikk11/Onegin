#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
// #include "string_functions.h"

const int MAX_LENGTH = 1000;

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// для обмена двух строк в массиве
// lines_arr - массив, в котором меняются строки
// index_1   - индекс первой строки
// ildex_2   - индекс второй строки
void swap_lines(char **lines_arr, int index_1, int index_2)
{
    assert(lines_arr != NULL);

    char *temp         = lines_arr[index_1];
    lines_arr[index_1] = lines_arr[index_2];
    lines_arr[index_2] = temp;
    return ;
}

// сортировка
void bubblesort(void *base, size_t lines_number, size_t size, 
                int (*compare_func)(const void *, const void *))
{
    assert(base         != NULL);
    assert(compare_func != NULL);

    char *lines_arr = (char *)base;
    int swapped = 0;
    for (size_t i = 0; i < lines_number - 1; i++)
    {
        // сброс значения для следующего прохода по массиву
        swapped = 0;
        for (size_t j = 0; j < lines_number - 1; j++)
        {
            char *elem1 = lines_arr + j * size;
            char *elem2 = lines_arr + (j + 1) * size;
            
            if (compare_func(elem1, elem2) > 0)
            {
                // обмен элементов
                for (size_t k = 0; k < size; k++)
                {
                    char temp = elem1[k];
                    elem1[k]  = elem2[k];
                    elem2[k]  = temp;
                }
                swapped = 1;
            }
        }
    
        if (swapped == 0) break;
    }
}

// сравнение строк без начальных символов
int strcmp_ignore_prefix(const char *s1, const char *s2)
{    
    // пропуск начальных символов в первой строке
    while (*s1 && (isalpha((unsigned char)*s1) == 0))
    {
        s1++;
    }
    
    // пропуск начальных символов во второй строке
    while (*s2 && (isalpha((unsigned char)*s2) == 0))
    {
        s2++;
    }

    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// сравнение строк с конца
int strcmp_from_end(const char *s1, const char *s2)
{
    const char *p1 = s1;
    const char *p2 = s2;
    
    while (*p1 != '\0') p1++;
    while (*p2 != '\0') p2++;

    // переход к последнему символу перед '\0'
    p1--;
    p2--;

    while (p1 >= s1 && (isalpha((unsigned char)*s1) == 0))
    {
        p1--;
    }

    while (p2 >= s2 && (isalpha((unsigned char)*s2) == 0))
    {
        p2--;
    }
    
    // сравнение символов с конца
    while (p1 >= s1 && p2 >= s2)
    {
        // выход из цикла как только символы разные
        if (*p1 != *p2)
        {
            return (unsigned char)*p1 - (unsigned char)*p2;
        }  
        p1--;
        p2--;
    }
    
    // результат
    if (p1 < s1 && p2 < s2) return 0;
    if (p1 < s1) return -1;
    if (p2 < s2) return 1;
    
    return 0;
}

// сравнение строк с конца
int compare_strings_from_end(const void *a, const void *b)
{
    return strcmp_from_end(*(const char **)a, *(const char **)b);
}

// сортировка строк с конца
void sort_lines_from_end(char **lines_arr, unsigned lines_number)
{
    assert(lines_arr != NULL);
    bubblesort((void *)lines_arr, lines_number, sizeof(char *), compare_strings_from_end);
}

// подсчёт числа строк в файле
// filename - файл, в котором считаем строки
unsigned count_lines_in_file(const char *filename)
{
    assert(filename != NULL);

    FILE *file = fopen(filename, "r");

    unsigned count = 0;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        count++;
    }

    fclose(file);
    return count;
}

// для выделения памяти под массив
// lines_number - чисто строк, под которые выделяется память
char **allocate_lines_arr(unsigned lines_number)
{
    return (char **)calloc(lines_number, sizeof(char*));
}

// для заполнения массива указателей строками из файла
// filename - исходный файл
// lines_arr - массив указателей на строки, куда они будут сохраняться
// lines_number - количество строк
int read_lines_from_file(const char *filename, char **lines_arr, unsigned lines_number)
{
    assert(filename  != NULL);
    assert(lines_arr != NULL);

    // r - открыть файл для прочтения
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Ошибка открытия файла");
        return -1;
        // сразу выводится сообщение почему не получилось открыть файл
    }

    // buffer - буфер для временного хранения строк
    char buffer[MAX_LENGTH] = "";
    int current_line = 0;

     while (fgets(buffer, sizeof(buffer), file) != NULL && current_line < lines_number)
    {
        // удаление символа новой строки если есть
        size_t len = strlen(buffer);
        // если послежний символ \n заменяем на \0
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
            len--;
        }

        // выделение памяти для строки
        lines_arr[current_line] = (char *)calloc(len + 1, sizeof(char));

        // копирование строки
        strcpy(lines_arr[current_line], buffer);
        current_line++;
    }

    fclose(file);    
    return 0;
}

// для очистки памяти динамического массива
// lines_arr    - массив, который надо очистить
// lines_number - кол-во элементов массива
void free_arr(char **lines_arr, unsigned lines_number)
{
     assert(lines_arr != NULL);
    // сначала очищаем каждую строку
    for (int i = 0; i < lines_number; i++)
    {
        free(lines_arr[i]);
    }
    // потом очищаем сам массив
    free(lines_arr);
    return ;
}

// сравнение строк
// a, b - элементы массива, которые сравниваются
int compare_strings(const void *a, const void *b)
{
    return strcmp_ignore_prefix(*(const char **)a, *(const char **)b);
}

// сортировки массива строк по алфавиту
// lines_arr    - сортируемый массив
// lines_number - длина массива
void sort_lines_alphabet(char **lines_arr, unsigned lines_number)
{
    assert(lines_arr != NULL);
    bubblesort((void *)lines_arr, lines_number,  sizeof(char *), compare_strings);
}

// запись отсортированных строк в файл
// filename     - файл в который записываем
// lines_arr    - записываемый массив
// lines_number - число записываемых строк
int my_output(const char *filename, char **lines_arr, unsigned lines_number)
{
    assert(filename  != NULL);
    assert(lines_arr != NULL);

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Ошибка открытия файла для записи\n");
        return -1;
    }

    for (unsigned i = 0; i < lines_number; i++)
    {
        fprintf(file, "%s\n", lines_arr[i]);
    }

    fclose(file);
    return 0;
}

int main()
{
    const char *input_filename                = "test1.txt";
    const char *output_filename               = "sorted_output.txt";
    const char *output_end_filename           = "sorted_end_output.txt";
    const char *output_first_version_filename = "first_version_output.txt";
    
    // count - кол-во прочитанных строк
    unsigned count = count_lines_in_file(input_filename);

    // инициализация массива
    char **lines = allocate_lines_arr(count);

    if (read_lines_from_file(input_filename, lines, count) == 0)
    {
        // копия для вывода в третий файл
        char **lines_copy = allocate_lines_arr(count);
        for (unsigned i = 0; i < count; i++)
        {
            lines_copy[i] = strdup(lines[i]);
        }

        // сортировка по алфавиту
        sort_lines_alphabet(lines, count);
        my_output(output_filename, lines, count);
        
        // сортировка с конца
        sort_lines_from_end(lines, count);
        my_output(output_end_filename, lines, count);

        // запись исходного текста в файл
        my_output(output_first_version_filename, lines_copy, count);
        
        // очистка памяти
        free_arr(lines, count);
        free_arr(lines_copy, count);
    }

    return 0;
}
