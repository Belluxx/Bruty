#ifndef BRUTY_BRUTETOOLS_H
#define BRUTY_BRUTETOOLS_H
#include <string>

// Main functions
void bruteforce_singlethread(const char*, int, int, const std::string&);
void bruteforce_singlethread(const char*, int, int);

// Low level functions
static void fill_array(char*, int, char);
static char next_char(char, const char*, int);
static void next_direct(char*, int, const char*, int);
static int ctoi(char, const char*, int);
static bool is_last(char, const char*, int);

#endif //BRUTY_BRUTETOOLS_H
