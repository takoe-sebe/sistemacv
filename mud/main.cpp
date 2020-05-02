#include <iostream>
// #include <functional>
#include <string>
#include <vector>
#include <fstream>
//#include <experimental/filesystem> // https://www.boost.org/doc/libs/1_62_0/more/getting_started/windows.html    https://cmake.org/cmake/help/v3.15/module/FindBoost.html
// #include <stdio.h>
#include "lib/PicoSHA2/picosha2.h" // https://github.com/okdshin/PicoSHA2

using namespace std;

bool file_exists(string filename){
    ifstream file;
    file.open(filename);
    bool result = file.is_open();
    file.close();
    return result;
}

string hash_file(string filename) {
    ifstream f(filename, ios::binary);
    vector<unsigned char> s(picosha2::k_digest_size);
    picosha2::hash256(f, s.begin(), s.end());
    f.close();
    string result = "";
    for (int i = 0; i < s.size(); i++){
        result += s[i];
    }
    return result;
}

string char_to_hex(unsigned char c) {
    string hexarr[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
    return hexarr[c/16] + hexarr[c%16];
}

void mud_help() {
    cout << "long long help................\n"
            "very long"    << endl;
    exit(0);
}
void print_history(string filename) {
    cout << "file hash: ";
    string hash = hash_file(filename);
    for (int i = 0; i < hash.size(); i++) {
        cout << char_to_hex(hash[i]);
    }
    cout << endl;
    cout << "Printing history of " << filename << endl;
}

void mud_update(string filename) {

}

int main(const int argc, const char *argv[]) {

    string args[argc];

    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    string filename = "..\\text.txt";

    if (argc > 1) {
        if (args[1] == "help") {
            mud_help();
        }
        if (args[1] == "history") {
            if (argc > 2) {
                if (args[2] == "swan") {
                    cout << "gagaga" << endl;
                    return 0;
                }
                filename = args[2];
                print_history(filename);
                return 0;
            }

        }
        if (args[1] == "undo") {

        }

    }


    mud_help();
    return 0;
}
