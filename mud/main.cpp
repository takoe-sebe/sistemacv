#include <iostream>
// #include <functional>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
//#include <experimental/filesystem> https://www.boost.org/doc/libs/1_62_0/more/getting_started/windows.html    https://cmake.org/cmake/help/v3.15/module/FindBoost.html
// #include <stdio.h>
#include "lib/PicoSHA2/picosha2.h" // https://github.com/okdshin/PicoSHA2
#include <ctime>

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
    cout << "Welcome to the version control program!\n"
            "The MUD program allows you to control file changes,\n"
            "track its versions, return the file to earlier versions\n"
            "and erase all information from absolutely all versions\n"
            "of the file.\n\n"

            "The following is a list of commands that will help you complete these steps.\n"
            "mud help - help\n"
            "mud update <filename> - file status record\n"
            "mud history <filename> - file change history\n"
            "mud undo <filename> [steps] - file rollback a few steps\n"
            "mud redo <filename> [steps] - file return in several steps\n"
            "mud clear <filename> - cleaning all file versions\n"    << endl;
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

void copy_file(const string& src, const string& dst) {
    ifstream in(src.c_str(), ios::binary);
    if (!in) {
        throw runtime_error("can`t open file: " + src);
    }
    ofstream out(dst.c_str(), ios::binary | ios::trunc);
    if (!out) {
        throw runtime_error("can`t create file: " + dst);
    }
    out << in.rdbuf();
}

int main(const int argc, const char *argv[]) {
    char buffer[80];
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    char* format = "%A_%B%d_%Y_%I_%M_%S";
    strftime(buffer, 80, format, timeinfo);
    string a = buffer;
    try {
        copy_file("..\\text.txt", "..//copy// "+ a + ".txt");
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    
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
