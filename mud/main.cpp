#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <cstdio>
#include "lib/PicoSHA2/picosha2.h" // https://github.com/okdshin/PicoSHA2
#include <ctime>
#include <windows.h>

using namespace std;

string filename;

string hash_file() {
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
            "of the file.\n"
            "Put the path to the file in the 'config' file. \n\n"

            "The following is a list of commands that will help you complete these steps.\n"
            "mud help - help\n"
            "mud path <filename> - learn how to change the file you're working with\n"
            "mud history <filename> - file change history\n"
            "mud undo <filename> [steps] - file rollback a few steps\n"
            "mud redo <filename> [steps] - file return in several steps\n"
            "mud clear <filename> - cleaning all file versions\n"    << endl;
    exit(0);
}
void mud_mda() {
    cout <<
         ".........................__.\n"
         "................,-~*`?lllllll`*~,\n"
         "..........,-~*`lllllllllllllllllllllll`*-,\n"
         ".....,-~*lllllllllllllllllllllllllllllllll*-,\n"
         "..,-*llllllllllllllllllllllllllllllllllllllll.\\.\n"
         ";*`lllllllllllllllllllllllllll,-~*~-,llllllllll\\\n"
         ".\\llllllllllllllllllllllll/.........\\;;;;lllll,-`~-,\n"
         "..\\llllllllllllllllll,-*...........`~-~-,...(.(`*,`,\n"
         "...\\lllllllll,-~*.....................)_-\\..*`*;..)\n"
         "....\\,-*`?,*`)............,-~*`~................/\n"
         ".....|/.../.../~,......-~*,-~*`;................/.\\\n"
         "..../.../.../.../..,-,..*~,.`*~*................*...\\.\n"
         "...|.../.../.../.*`...\\...........................)....)`~,\n"
         "...|./.../..../.......)......,.)`*~-,............/....|..)...`~-,.\n"
         ".././.../...,*`-,.....`-,...*`....,---......\\..../...../..|.........```*~-,,,,\n"
         "..(..........)`*~-,....`*`.,-~*.,-*......|.../..../.../............\\........\n"
         "...*-,.......`*-,...`~,..``.,,,-*..........|.,*...,*...|..............\\........\n"
         "......*,.........`-,...)-,..............,-*`...,-*....(`-,............\\.......\n"
         ".........f`-,.........`-,/...*-,___,,-~*....,-*......|...`-,..........\\........\n \n"

         "Please try \"mud help\""
         << endl;
    exit(0);
}

void mud_clear(){
    filesystem::path pathToDelete("..\\copy");
    remove_all(pathToDelete);
    cout << "You have cleared all file versions "  << endl;
}

void print_hash() {
    cout << "file hash: ";
    string hash = hash_file();
    for (int i = 0; i < hash.size(); i++) {
        cout << char_to_hex(hash[i]);
    }
    cout << endl;
    cout << "Printing history of " << filename << endl;
}

void mud_history(){
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf=FindFirstFile("..\\copy\\*", &FindFileData);
    if (hf!=INVALID_HANDLE_VALUE)
    {
        do{
            cout << FindFileData.cFileName << endl;
        }
        while (FindNextFile(hf,&FindFileData)!=0);
        FindClose(hf);
    }
}

void copy_file(const string& src, const string& dst) {
    filesystem::path pathToCreat("..\\copy");
    create_directory(pathToCreat);
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

string convert(char* a, int size) {
    string s(a);
    return s;
}

void mud_path(){
    int size=0;
    FILE *F;
    char cfg_buff[300];

    int i=0;
    memset(&cfg_buff, 0, sizeof(cfg_buff));

    if((F = fopen("config.txt", "rb")) == NULL)
        cout << "ERROR" << endl;

    while(1)
    {
        int ch = fgetc(F);
        if(ch == EOF)
        {size=i+1; break;}
        cfg_buff[i] = ch;
        i++;
    }
    fclose(F);
    filename = convert(cfg_buff, (size/sizeof(char)));
}

int main(const int argc, const char *argv[]) {
    char buffer[80];
    mud_path();
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    char* format = "%A_%B%d_%Y_%I_%M_%S";
    strftime(buffer, 80, format, timeinfo);
    string a = buffer;
    try {
        string var = "..//copy// "+ a + ".txt";
        copy_file(filename, var);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    string args[argc];

    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    if (argc > 1) {
        if (args[1] == "help") {
            mud_help();
        }
        if (args[1] == "clear") {
            mud_clear();
            return 0;
        }
        if (args[1] == "path") {
            cout << "You can change the path to your file in \"config\"\n"
                    "Please, before changing the file path, clear all versions of your file using \"mud clear\"" << endl;
            return 0;
        }
        if (args[1] == "history") {
            mud_history();
            return 0;
        }
        if (args[1] == "history") {
            if (argc > 2) {
                if (args[2] == "hash") {
                    filename = args[2];
                    print_hash();
                    return 0;
                }

            }

        }
    }

    mud_mda();
    return 0;
}
