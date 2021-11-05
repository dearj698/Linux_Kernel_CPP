//
// Created by Zhaohua Liu on 2019-09-27.
//

#include "File.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    File* rmfile = new File(argv[1]);
    rmfile->Remove();
    return 0;
}