#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int     my_puts   (const char *str);
char   *my_strchr (const char *str, int ch);
int     my_strlen (const char *str);
char   *my_strcpy (char *dest, const char *src);
char   *my_strncpy(char *dest, const char *src, size_t n);
char   *my_strcat (char *dest, const char *src);
char   *my_strncat(char *dest, const char *src, size_t n);
int     my_atoi   (const char *str);
char   *my_fgets  (char *str, int n, FILE *stream);
char   *my_strdup (const char *s);
size_t  my_getline(char **lineptr, size_t *n, FILE *stream);
char   *my_strstr (const char *s1, const char *s2);


#endif // STRING_FUNCTIONS_H
