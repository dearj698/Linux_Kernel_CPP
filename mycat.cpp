//
// Created by Zhaohua Liu on 2019-09-27.
//

#include <fstream>
#include <iostream>
#include "File.hpp"
using namespace std;

int main(int argc, char* argv[]){
    for (int i = 1; i <argc ; ++i) {
        File* openfile = new File(argv[i]);
        fstream outfile;
        outfile.open(argv[i], fstream::in);
        int intErrorNumber = errno;
        if(intErrorNumber != 0){
            openfile->setErrorNUm(intErrorNumber);
            string errorMessage = string(strerror(intErrorNumber));
            cout<<errorMessage<<endl;
            return intErrorNumber;
        }
        char buff[openfile->getBlockSize()];
        while(outfile.getline(buff,openfile->getBlockSize())){
            cout << buff <<endl;
        }
        outfile.close();
    }
    return 0;
}