#include "brutetools.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NOT_FOUND (-1)
#define bigint unsigned long long int

/**
 * Start bruteforce dictionary generation in single-thread mode and
 * writes it to a file.
 *
 * @param charset The charset that will be used to compose passwords
 * @param charset_size The number of characters in the charset
 * @param pass_size The length of the password
 * @param fname The name of the file where the dictionary will be
 * written
 */
void generate_dict(const char* charset, int charset_size, int pass_size, const char* fname) {
    char* pass = (char*) calloc(pass_size, sizeof(char));
    fill_array(pass, pass_size, charset[0]);
    FILE *f;
    f = fopen(fname, "w");

    const bigint field_size = pow(charset_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    printf("Dictionary words: %llu\n", field_size + 1);
    fprintf(f, "%s\n", pass);
    for (bigint i = 0; i < field_size; i++) {
        next_pass(pass, pass_size, charset, charset_size);
        fprintf(f, "%s\n", pass);
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            printf("\rProgress: %.1f%%", progress);
            fflush(stdout);
        }
    }
    printf("\n");

    fclose(f);
    free(pass);
}

/**
 * Start bruteforce dictionary generation in single-thread mode and
 * prints it to the terminal (stdout)
 *
 * @param charset The charset that will be used to compose passwords
 * @param charset_size The number of characters in the charset
 * @param pass_size The length of the password
 */
void generate_dict(const char* charset, int charset_size, int pass_size) {
    char* pass = (char*) calloc(pass_size, sizeof(char));
    fill_array(pass, pass_size, charset[0]);

    const bigint field_size = pow(charset_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    fprintf(stderr, "Dictionary words: %llu\n", field_size + 1);
    printf("%s\n", pass);
    for (bigint i = 0; i < field_size; i++) {
        next_pass(pass, pass_size, charset, charset_size);
        printf("%s\n", pass);
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            fprintf(stderr, "\rProgress: %.1f%%", progress);
            fflush(stderr);
        }
    }
    fprintf(stderr, "\n");
}

static void next_pass(char* pass, int pass_size, const char* charset, int charset_size) {
    for (int i = 0; i < pass_size; i++) {
        if (pass[i] == charset[charset_size - 1]) {
            pass[i] = charset[0];
        } else {
            pass[i] = next_char(pass[i], charset, charset_size);
            break;
        }
    }
}

static char next_char(char c, const char* charset, int charset_size) {
    const int index = index_of_char(c, charset, charset_size);
    if (index != charset_size - 1)
        return charset[index + 1];
    else
        return charset[0];
}

static int index_of_char(char c, const char* charset, int charset_size) {
    for (int i = 0; i < charset_size; i++)
        if (charset[i] == c)
            return i;
    return NOT_FOUND;
}

static void fill_array(char* array, int size, char n) {
    for (int i = 0; i < size; i++)
        array[i] = n;
}