#include <iostream>
// #include <functional>
#include <string>
#include <fstream>
// #include <stdio.h>

using namespace std;

unsigned int HashFAQ6(const char* filename) {
    ifstream is (filename, std::ifstream::binary);
    if (!is)
    {
        throw runtime_error("Cannot open file " + *filename);
    }
    unsigned int hash = 0;
    unsigned char byte;
    while (is >> byte)
    {
        hash += byte;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    is.close();
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void print_help() {
    cout << "long long help................." << endl;
    exit(0);
}
void print_history(const char* filename) {
    cout << "Printing history of " << filename << endl;
}

bool compare_str(const char* str1, const char* str2) {
    for (int i = 0; *(str1+i) != 0; i++) {
        if (*(str1+i) != *(str2+i)) return false;
    }
    return true;
}

int main(const int argc, const char *argv[]) {

    const char* filename = "..\\text.txt";
    if (argc == 1) {
        print_help();
    }

    if (argc > 1) {
        if (compare_str (argv[1], "help")) {
            print_help();
        }
        if (compare_str (argv[1], "history")) {
            if (argc > 2) {
                if (compare_str (argv[2], "swan")){
                    cout << "gagaga" << endl;
                    return 0;
                }
                filename = argv[2];
                print_history(filename);
                return 0;
            }

        }
        if (compare_str (argv[1], "undo")) {

        }

    }

  //      filename = argv[1];

  //  cout << filename << " : " << HashFAQ6(filename) << endl;

    print_help();
    return 0;
}
