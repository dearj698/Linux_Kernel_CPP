//
// Created by Zhaohua Liu on 2019-09-26.
//
#include <fstream>
#include "File.hpp"
using namespace std;

int main(int argc, char* argv[]){
    File* myfile = new File(argv[1]);
    myfile->Rename(argv[2]);
    int internal_error = errno;
    if ( internal_error == EXDEV){
        fstream outfile;
        outfile.open(argv[2],fstream::out);
        myfile->Dump(outfile);
        outfile.close();
        myfile->Remove();
    }

    return 0;
}