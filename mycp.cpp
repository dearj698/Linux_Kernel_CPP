//
// Created by Zhaohua Liu on 2019-09-27.
//

#include "File.hpp"
#include <fstream>
using namespace std;

int main (int argc, char* argv[]){
    File* oldfile = new File(argv[1]);// open the original file
    fstream outfile;
    outfile.open(argv[2],fstream::out);
    oldfile->Dump(outfile);
    return 0;
}
