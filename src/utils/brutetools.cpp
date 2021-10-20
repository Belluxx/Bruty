#include "brutetools.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define bigint unsigned long long int

void generate_indexes(const char*, int);
static void next_pass(char*, int, const char*, int);
static char next_char(char, const char*, int);
static void fill_array(char*, int, char);

int charset_indexes[128] = {};

/**
 * Start bruteforce dictionary generation in single-thread mode
 * printing progress information to stderr
 *
 * @param charset The charset that will be used to compose passwords
 * @param charset_size The number of characters in the charset
 * @param pass_size The length of the password
 */
void generate_dict(const char* charset, int charset_size, int pass_size) {
    generate_indexes(charset, charset_size);

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

/**
 * Start bruteforce dictionary generation in single-thread mode
 * without printing progress information
 *
 * @param charset The charset that will be used to compose passwords
 * @param charset_size The number of characters in the charset
 * @param pass_size The length of the password
 */
void generate_dict_silent(const char* charset, int charset_size, int pass_size) {
    generate_indexes(charset, charset_size);

    char* pass = (char*) calloc(pass_size, sizeof(char));
    fill_array(pass, pass_size, charset[0]);

    const bigint field_size = pow(charset_size, pass_size) - 1;
    printf("%s\n", pass);
    for (bigint i = 0; i < field_size; i++) {
        next_pass(pass, pass_size, charset, charset_size);
        printf("%s\n", pass);
    }
}

void generate_indexes(const char* charset, int charset_size) {
    for (int i = 0; i < charset_size; i++) {
        char c = charset[i];
        charset_indexes[c] = i;
    }
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
    const int index = charset_indexes[c];
    if (index != charset_size - 1)
        return charset[index + 1];
    else
        return charset[0];
}

static void fill_array(char* array, int size, char n) {
    for (int i = 0; i < size; i++)
        array[i] = n;
}