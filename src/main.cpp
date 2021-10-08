#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define NOT_FOUND (-1)
#define bigint unsigned long long int

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

void show_help();
void show_info();
void print_error(const string&, int);
void bruteforce_singlethread(const char*, const string&);
void bruteforce_singlethread(const char*);

void fill_array(char*, int, char);
char next_char(char, const char*);
void next_direct(char*, const char*);
int ctoi(char, const char*);
bool is_last(char, const char*);

int charset_size = -1;
int pass_size = -1;
char* pass;

bool fwrite_enabled = false;

int main(int argc, char const *argv[]) {
    show_info();
    if (argc < 3) show_help();

    const int mode = atoi(argv[1]);
    pass_size = atoi(argv[2]);
    string fname;
    if (argc > 3) {
        if (!strcmp(argv[3], "-f")) {
            if (argc > 4) { fname = argv[4]; fwrite_enabled = true; }
            else print_error("Please specify a file", 3);
        } else print_error("Unknown flag", 2);
    } else fwrite_enabled = false;

    pass = (char*) calloc(pass_size, sizeof(char));
    if (fwrite_enabled) {
        ofstream f;
        f.open(fname);
        if (!f.good()) print_error("Invalid file", 4);
        f.close();
    }

    switch (mode) {
        case 0:
            charset_size = BAREBONE_CHARSET_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(BAREBONE_CHARSET, fname);
            else bruteforce_singlethread(BAREBONE_CHARSET);
            break;

        case 1:
            charset_size = MINIMAL_CHARSET_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(MINIMAL_CHARSET, fname);
            else bruteforce_singlethread(MINIMAL_CHARSET);
            break;

        case 2:
            charset_size = BASIC_CHARSET_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(BASIC_CHARSET, fname);
            else bruteforce_singlethread(BASIC_CHARSET);
            break;

        case 3:
            charset_size = NORMAL_CHARSET_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(NORMAL_CHARSET, fname);
            else bruteforce_singlethread(NORMAL_CHARSET);
            break;

        case 4:
            charset_size = BIG_CHARSET_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(BIG_CHARSET, fname);
            else bruteforce_singlethread(BIG_CHARSET);
            break;

        default:
            cout << "Mode not recognized" << endl;
            break;
    }
}

void bruteforce_singlethread(const char* _charset, const string& fname) {
    fill_array(pass, pass_size, _charset[0]);
    ofstream f;
    f.open(fname);

    const bigint field_size = pow(charset_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    cout << "Attempts needed: " << field_size + 1 << endl;
    f << pass << endl;
    for (bigint i = 0; i < field_size; i++) {
        next_direct(pass, _charset);
        f << pass << endl;
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            cout << "\rProgress: " << (float) ((int) (progress * 10.0)) / 10.0 << "%";
            cout.flush();
        }
    }
    cout << endl;
}

void bruteforce_singlethread(const char* _charset) {
    fill_array(pass, pass_size, _charset[0]);

    const bigint field_size = pow(charset_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    clog << "Attempts needed: " << field_size << endl;
    cout << pass << endl;
    for (bigint i = 0; i < field_size; i++) {
        next_direct(pass, _charset);
        cout << pass << endl;
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            clog << "\rProgress: " << (float) ((int) (progress * 10.0)) / 10.0 << "%";
            clog.flush();
        }
    }
    clog << endl;
}

void next_direct(char* _pass, const char* _charset) {
    const char c = _pass[0];
    if (is_last(c, _charset)) {
        for (int i = 0; i < pass_size; i++) {
            if (_pass[i] == _charset[charset_size - 1]) {
                _pass[i] = _charset[0];
            } else {
                _pass[i] = next_char(_pass[i], _charset);
                break;
            }
        }
    } else {
        _pass[0] = next_char(c, _charset);
    }
}

char next_char(char c, const char* _charset) {
    const int index = ctoi(c, _charset);
    if (index != charset_size - 1)
        return _charset[index + 1];
    else
        return _charset[0];
}

bool is_last(char c, const char* _charset) {
    return c == _charset[charset_size - 1];
}

int ctoi(char c, const char* _charset) {
    for (int i = 0; i < charset_size; i++) {
        if (_charset[i] == c) return i;
    }
    return NOT_FOUND;
}

void fill_array(char* array, int size, char n) {
    for (int i = 0; i < size; i++)
        array[i] = n;
}

void show_info() {
    clog << ">>> Bruty by Belluxx (https://github.com/Belluxx/Bruty) <<<\n\n";
}

void show_help() {
    clog << "Usage: bruty charset length [-f out_file]" << endl;
    clog << "\t- charset: the set of characters that composes the passwords\n"
            "\t\t0: Barebone ->   lowercase letters\n"
            "\t\t1: Minimal  ->   lowercase letters and digits\n"
            "\t\t2: Basic    ->   lowercase and uppercase letters\n"
            "\t\t3: Normal   ->   lowercase and uppercase letters and digits\n"
            "\t\t4: Big      ->   lowercase and uppercase letters, digits and symbols\n";
    clog << "\t- length: the length of the password\n";
    clog << "\t- out_file: the name of the file where passwords will be written\n";
    exit(1);
}

void print_error(const string& s, int code) {
    cout << s << endl;
    exit(code);
}