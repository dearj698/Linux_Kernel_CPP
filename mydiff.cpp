//
// Created by Zhaohua Liu on 2019-09-27.
//

#include <zconf.h>
#include "File.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    char path[PATH_MAX];
    string pathname = getcwd(path , PATH_MAX);
    File* newfile = new File(argv[1]);
    string fullname = pathname + "/" + argv[2];
    FILE* anotherFile = fopen (fullname.c_str(), "r");
    int result = newfile->Compare(anotherFile);
    if(result == 1){
        printf("different\n");
    }
    else if (result ==0){
        printf("same\n");
    }
    return 0;
}