#include "brutetools.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define NOT_FOUND (-1)
#define bigint unsigned long long int

/**
 * Start bruteforce dictionary generation in single-thread mode and
 * writes it to a file.
 *
 * @param _charset The charset that will be used to compose passwords
 * @param charset_size The number of characters in the charset
 * @param pass_size The length of the password
 * @param fname The name of the file where the dictionary will be
 * written
 */
void bruteforce_singlethread(const char* _charset, int charset_size, int pass_size, const string& fname) {
    char* pass = (char*) calloc(pass_size, sizeof(char));
    fill_array(pass, pass_size, _charset[0]);
    ofstream f;
    f.open(fname);

    const bigint field_size = pow(charset_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    cout << "Attempts needed: " << field_size + 1 << endl;
    f << pass << endl;
    for (bigint i = 0; i < field_size; i++) {
        next_direct(pass, pass_size, _charset, charset_size);
        f << pass << endl;
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            cout << "\rProgress: " << (float) ((int) (progress * 10.0)) / 10.0 << "%";
            cout.flush();
        }
    }
    cout << endl;
}

/**
 * Start bruteforce dictionary generation in single-thread mode and
 * prints it to the terminal (stdout)
 *
 * @param _charset The charset that will be used to compose passwords
 * @param charset_size The number of characters in the charset
 * @param pass_size The length of the password
 */
void bruteforce_singlethread(const char* _charset, int charset_size, int pass_size) {
    char* pass = (char*) calloc(pass_size, sizeof(char));
    fill_array(pass, pass_size, _charset[0]);

    const bigint field_size = pow(charset_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    clog << "Attempts needed: " << field_size << endl;
    cout << pass << endl;
    for (bigint i = 0; i < field_size; i++) {
        next_direct(pass, pass_size, _charset, charset_size);
        cout << pass << endl;
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            clog << "\rProgress: " << (float) ((int) (progress * 10.0)) / 10.0 << "%";
            clog.flush();
        }
    }
    clog << endl;
}

static void next_direct(char* _pass, int pass_size, const char* _charset, int charset_size) {
    const char c = _pass[0];
    if (is_last(c, _charset, charset_size)) {
        for (int i = 0; i < pass_size; i++) {
            if (_pass[i] == _charset[charset_size - 1]) {
                _pass[i] = _charset[0];
            } else {
                _pass[i] = next_char(_pass[i], _charset, charset_size);
                break;
            }
        }
    } else {
        _pass[0] = next_char(c, _charset, charset_size);
    }
}

static char next_char(char c, const char* _charset, int charset_size) {
    const int index = ctoi(c, _charset, charset_size);
    if (index != charset_size - 1)
        return _charset[index + 1];
    else
        return _charset[0];
}

static bool is_last(char c, const char* _charset, int charset_size) {
    return c == _charset[charset_size - 1];
}

static int ctoi(char c, const char* _charset, int charset_size) {
    for (int i = 0; i < charset_size; i++)
        if (_charset[i] == c)
            return i;
    return NOT_FOUND;
}

static void fill_array(char* array, int size, char n) {
    for (int i = 0; i < size; i++)
        array[i] = n;
}