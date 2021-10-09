#ifndef BRUTY_BRUTETOOLS_H
#define BRUTY_BRUTETOOLS_H
#include <string>

// Main functions
void generate_dict(const char*, int, int, const char*);
void generate_dict(const char*, int, int);

// Low level functions
static void fill_array(char*, int, char);
static char next_char(char, const char*, int);
static void next_pass(char*, int, const char*, int);
static int index_of_char(char, const char*, int);

#endif //BRUTY_BRUTETOOLS_H
