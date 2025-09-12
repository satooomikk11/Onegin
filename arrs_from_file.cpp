#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "string_functions.h"

const int MAX_LINES  = 1000;
const int MAX_LENGTH = 256;

// для заполнения массива указателей строками из файла
// char*** : указатель на строку, указатель на массив строк, указатель на указатель на массив строк
// char*** - адрес массива адресов
// char**  - массив адресов строк
// char*   - адрес строки
// char    - символы строки
// filename - исходный файл
// lines_arr - массив указателей на строки, куда они будут сохраняться
// lines_number - количество строк
int read_lines_from_file(const char *filename, char ***lines_arr, int *lines_number)
{
    // r - открыть файл для прочтения
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        return -1;
        // сразу выводится сообщение почему не получилось открыть файл
    }

    // выделение памяти для массива указателей
    *lines_arr = (char **)calloc(MAX_LINES, sizeof(char *));

    // buffer - буфер для временного хранения строк
    char buffer[MAX_LENGTH] = "";
    *lines_number = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL && *lines_number < MAX_LINES)
    {
        // todo: проверка NULL указателей
        // выделение памяти для строки
        (*lines_arr)[*lines_number] = (char *)calloc(strlen(buffer) + 1, sizeof(char));
        // копирование строки
        strcpy((*lines_arr)[*lines_number], buffer);
        (*lines_number)++;
    }

    fclose(file);
    return 0;
}

// для очистки памяти динамического массива
// lines_arr    - массив, который надо очистить
// lines_number - кол-во элементов массива
void free_arr(char **lines_arr, int lines_number)
{
    // сначала очищаем каждую строку
    for (int i = 0; i < lines_number; i++)
    {
        free(lines_arr[i]);
    }
    // потом очищаем сам массив
    free(lines_arr);
}

int main()
{
    char **lines = NULL;
    int count = 0;

    if (read_lines_from_file("test1.txt", &lines, &count) == 0)
    {
        printf("Прочитано %d строк:\n", count);

        for (int i = 0; i < count; i++)
        {
            printf("%s", lines[i]);
        }

        free_arr(lines, count);
    }

    else
    {
        printf("Не удалось проичтать файл!");
    }

    return 0;
}