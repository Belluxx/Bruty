/**
 * Belluxx 2021
 *
 * Basic bruteforce dictionary command-line generator written in C++
 *
 * TODO: Allow min-max password length range
 */

#include <iostream>
#include <cmath>
#include "utils/brutetools.h"
using namespace std;

static const int BAREBONE_CHARSET_SIZE = 26;
static const char BAREBONE_CHARSET[BAREBONE_CHARSET_SIZE] =   {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

static const int MINIMAL_CHARSET_SIZE = 36;
static const char MINIMAL_CHARSET[MINIMAL_CHARSET_SIZE] =     {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                               '0','1','2','3','4','5','6','7','8','9'};

static const int BASIC_CHARSET_SIZE = 52;
static const char BASIC_CHARSET[BASIC_CHARSET_SIZE] =         {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                               'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

static const int NORMAL_CHARSET_SIZE = 62;
static const char NORMAL_CHARSET[NORMAL_CHARSET_SIZE] =       {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                               'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                                               '0','1','2','3','4','5','6','7','8','9'};

static const int BIG_CHARSET_SIZE = 70;
static const char BIG_CHARSET[BIG_CHARSET_SIZE] =             {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                               'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                                               '0','1','2','3','4','5','6','7','8','9',
                                                               '!','#','-','_','$','%','&','*'};

void show_info();
void show_help();
void print_error(const string&, int);
bool streq(const char*, const char*);

bool silent_mode = false;

int main(int argc, char const *argv[]) {
    if (argc < 3) show_help();

    const int mode = atoi(argv[1]);
    const int pass_size = atoi(argv[2]);
    if (argc == 4) {
        if (streq(argv[3], "-s"))
            silent_mode = true;
        else
            print_error("Unknown flag", 1);
    }

    if (!silent_mode) show_info();

    switch (mode) {
        case 0:
            if (silent_mode) generate_dict_silent(BAREBONE_CHARSET, BAREBONE_CHARSET_SIZE, pass_size);
            else generate_dict(BAREBONE_CHARSET, BAREBONE_CHARSET_SIZE, pass_size);
            break;

        case 1:
            if (silent_mode) generate_dict_silent(MINIMAL_CHARSET, MINIMAL_CHARSET_SIZE, pass_size);
            else generate_dict(MINIMAL_CHARSET, MINIMAL_CHARSET_SIZE, pass_size);
            break;

        case 2:
            if (silent_mode) generate_dict_silent(BASIC_CHARSET, BASIC_CHARSET_SIZE, pass_size);
            else generate_dict(BASIC_CHARSET, BASIC_CHARSET_SIZE, pass_size);
            break;

        case 3:
            if (silent_mode) generate_dict_silent(NORMAL_CHARSET, NORMAL_CHARSET_SIZE, pass_size);
            else generate_dict(NORMAL_CHARSET, NORMAL_CHARSET_SIZE, pass_size);
            break;

        case 4:
            if (silent_mode) generate_dict_silent(BIG_CHARSET, BIG_CHARSET_SIZE, pass_size);
            else generate_dict(BIG_CHARSET, BIG_CHARSET_SIZE, pass_size);
            break;

        default:
            print_error("Charset not recognized", 1);
            break;
    }
}

void show_info() {
    clog << ">>> Bruty by Belluxx (https://github.com/Belluxx/Bruty) <<<\n";
}

void show_help() {
    clog << "Usage: bruty charset length [-s]" << endl;
    clog << "\t- charset: the number of the charset that will be used to compose the passwords\n"
            "\t\t0: lowercase letters\n"
            "\t\t1: lowercase letters and digits\n"
            "\t\t2: lowercase and uppercase letters\n"
            "\t\t3: lowercase and uppercase letters and digits\n"
            "\t\t4: lowercase and uppercase letters, digits and symbols\n";
    clog << "\t- length: the length of the password\n";
    clog << "\t- -s: silent mode, do not print progress information\n";
    exit(1);
}

void print_error(const string& s, int code) {
    clog << s << endl;
    exit(code);
}

bool streq(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}