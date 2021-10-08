#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define NOT_FOUND (-1)
#define bigint unsigned long long int

static const int BAREBONE_DICT_SIZE = 26;
static const char BAREBONE_DICT[BAREBONE_DICT_SIZE] =   {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

static const int MINIMAL_DICT_SIZE = 36;
static const char MINIMAL_DICT[MINIMAL_DICT_SIZE] =     {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                         '0','1','2','3','4','5','6','7','8','9'};

static const int BASIC_DICT_SIZE = 52;
static const char BASIC_DICT[BASIC_DICT_SIZE] =         {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

static const int NORMAL_DICT_SIZE = 62;
static const char NORMAL_DICT[NORMAL_DICT_SIZE] =       {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                                         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                                         '0','1','2','3','4','5','6','7','8','9'};

static const int BIG_DICT_SIZE = 70;
static const char BIG_DICT[BIG_DICT_SIZE] =             {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
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

int dict_size = -1;
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
            dict_size = BAREBONE_DICT_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(BAREBONE_DICT, fname);
            else bruteforce_singlethread(BAREBONE_DICT);
            break;

        case 1:
            dict_size = MINIMAL_DICT_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(MINIMAL_DICT, fname);
            else bruteforce_singlethread(MINIMAL_DICT);
            break;

        case 2:
            dict_size = BASIC_DICT_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(BASIC_DICT, fname);
            else bruteforce_singlethread(BASIC_DICT);
            break;

        case 3:
            dict_size = NORMAL_DICT_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(NORMAL_DICT, fname);
            else bruteforce_singlethread(NORMAL_DICT);
            break;

        case 4:
            dict_size = BIG_DICT_SIZE;
            if (fwrite_enabled) bruteforce_singlethread(BIG_DICT, fname);
            else bruteforce_singlethread(BIG_DICT);
            break;

        default:
            cout << "Mode not recognized" << endl;
            break;
    }
}

void bruteforce_singlethread(const char* _dict, const string& fname) {
    fill_array(pass, pass_size, _dict[0]);
    ofstream f;
    f.open(fname);

    const bigint field_size = pow(dict_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    cout << "Attempts needed: " << field_size + 1 << endl;
    f << pass << endl;
    for (bigint i = 0; i < field_size; i++) {
        next_direct(pass, _dict);
        f << pass << endl;
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            cout << "\rProgress: " << (float) ((int) (progress * 10.0)) / 10.0 << "%";
            cout.flush();
        }
    }
    cout << endl;
}

void bruteforce_singlethread(const char* _dict) {
    fill_array(pass, pass_size, _dict[0]);

    const bigint field_size = pow(dict_size, pass_size) - 1;
    const bigint progress_step = field_size / 1000;
    clog << "Attempts needed: " << field_size << endl;
    cout << pass << endl;
    for (bigint i = 0; i < field_size; i++) {
        next_direct(pass, _dict);
        cout << pass << endl;
        if (i % progress_step == 0) {
            float progress = ((float) i / (float) field_size) * 100.0f;
            clog << "\rProgress: " << (float) ((int) (progress * 10.0)) / 10.0 << "%";
            clog.flush();
        }
    }
    clog << endl;
}

void next_direct(char* _pass, const char* _dict) {
    const char c = _pass[0];
    if (is_last(c, _dict)) {
        for (int i = 0; i < pass_size; i++) {
            if (_pass[i] == _dict[dict_size - 1]) {
                _pass[i] = _dict[0];
            } else {
                _pass[i] = next_char(_pass[i], _dict);
                break;
            }
        }
    } else {
        _pass[0] = next_char(c, _dict);
    }
}

char next_char(char c, const char* _dict) {
    const int index = ctoi(c, _dict);
    if (index != dict_size - 1)
        return _dict[index + 1];
    else
        return _dict[0];
}

bool is_last(char c, const char* _dict) {
    return c == _dict[dict_size - 1];
}

int ctoi(char c, const char* _dict) {
    for (int i = 0; i < dict_size; i++) {
        if (_dict[i] == c) return i;
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
    clog << "Usage: bruty dictionary length [-f out_file]" << endl;
    clog << "\t- dictionary:\n"
            "\t\t0: Barebone  abc..xyz\n"
            "\t\t1: Minimal   abc..012\n"
            "\t\t2: Basic     abc..XYZ\n"
            "\t\t3: Normal    abc..012..XYZ\n"
            "\t\t4: Big       abc..012..XYZ..%&*\n";
    clog << "\t- length: the length of the password\n";
    clog << "\t- out_file: the name of the file where passwords will be written\n";
    exit(1);
}

void print_error(const string& s, int code) {
    cout << s << endl;
    exit(code);
}