/**
 * Pietro Bellodi 2021
 *
 * Basic bruteforce dictionary command-line generator written in C++
 *
 * TODO: Allow min-max password length range
 */

#include <iostream>
#include <cmath>
#include <fstream>
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

bool fwrite_enabled = false;

int main(int argc, char const *argv[]) {
    show_info();
    if (argc < 3) show_help();

    const int mode = atoi(argv[1]);
    const int pass_size = atoi(argv[2]);
    string fname;
    if (argc > 3) {
        if (!strcmp(argv[3], "-f")) {
            if (argc > 4) { fname = argv[4]; fwrite_enabled = true; }
            else print_error("Please specify a file", 3);
        } else print_error("Unknown flag", 2);
    } else fwrite_enabled = false;

    if (fwrite_enabled) {
        ofstream f;
        f.open(fname);
        if (!f.good()) print_error("Invalid file", 4);
        f.close();
    }

    switch (mode) {
        case 0:
            if (fwrite_enabled) generate_dict(BAREBONE_CHARSET, BAREBONE_CHARSET_SIZE, pass_size, fname);
            else generate_dict(BAREBONE_CHARSET, BAREBONE_CHARSET_SIZE, pass_size);
            break;

        case 1:
            if (fwrite_enabled) generate_dict(MINIMAL_CHARSET, MINIMAL_CHARSET_SIZE, pass_size, fname);
            else generate_dict(MINIMAL_CHARSET, MINIMAL_CHARSET_SIZE, pass_size);
            break;

        case 2:
            if (fwrite_enabled) generate_dict(BASIC_CHARSET, BASIC_CHARSET_SIZE, pass_size, fname);
            else generate_dict(BASIC_CHARSET, BASIC_CHARSET_SIZE, pass_size);
            break;

        case 3:
            if (fwrite_enabled) generate_dict(NORMAL_CHARSET, NORMAL_CHARSET_SIZE, pass_size, fname);
            else generate_dict(NORMAL_CHARSET, NORMAL_CHARSET_SIZE, pass_size);
            break;

        case 4:
            if (fwrite_enabled) generate_dict(BIG_CHARSET, BIG_CHARSET_SIZE, pass_size, fname);
            else generate_dict(BIG_CHARSET, BIG_CHARSET_SIZE, pass_size);
            break;

        default:
            clog << "Mode not recognized" << endl;
            break;
    }
}

void show_info() {
    clog << ">>> Bruty by Belluxx (https://github.com/Belluxx/Bruty) <<<\n";
}

void show_help() {
    clog << "Usage: bruty charset length [-f out_file]" << endl;
    clog << "\t- charset: the number of the charset that will be used to compose the passwords\n"
            "\t\t0: lowercase letters\n"
            "\t\t1: lowercase letters and digits\n"
            "\t\t2: lowercase and uppercase letters\n"
            "\t\t3: lowercase and uppercase letters and digits\n"
            "\t\t4: lowercase and uppercase letters, digits and symbols\n";
    clog << "\t- length: the length of the password\n";
    clog << "\t- out_file: the name of the file where passwords will be written\n";
    exit(1);
}

void print_error(const string& s, int code) {
    clog << s << endl;
    exit(code);
}