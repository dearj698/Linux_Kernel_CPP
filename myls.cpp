//
// Created by Zhaohua Liu on 2019-09-27.
//
#include <iostream>
#include <unistd.h>
#include "File.hpp"

char *formatdate(char* string, time_t val){
    strftime(string, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
    return string;
};
using namespace std;

int main (int argc, char* argv[]) {
    char buff[PATH_MAX];
    string pathname = getcwd(buff , PATH_MAX);
    File myfile(pathname);
    myfile.Expand();
    std::vector<File*> childrenFile = myfile.getChildrenFile();
    if(argc == 1 ){
        for(int i = 0 ; i < childrenFile.size() ; i++){
            printf("%s\n", childrenFile[i]->getName().c_str());
        }
    }
    else if (argc == 2 && strncmp(argv[1], "-l", sizeof("-l")) == 0) {
        char time[36];
        for (int i = 0; i < childrenFile.size(); ++i) {
            time_t modtime = childrenFile[i]->getModTime();
            printf("%s   %hu %s %s  %lld  %s %s\n", childrenFile[i]->getPermission().c_str(), childrenFile[i]->getHardlinkNum(), childrenFile[i]->getName().c_str(), childrenFile[i]->getGroupName().c_str(), childrenFile[i]->getFileSize(), ctime(&modtime), childrenFile[i]->getName().c_str());
        }
    }
    else if (argc == 2 && strncmp(argv[1], "-l", sizeof("-l")) != 0){
        string dirname = string(argv[1]);
        dirname = pathname + "/" + dirname;
        File* dir = new File(dirname);
        dir->Expand();
        std::vector<File*> childrenFile = dir->getChildrenFile();
        for(int i = 0 ; i < childrenFile.size() ; i++){
            printf("%s\n", childrenFile[i]->getName().c_str());
        }
    }
    else if(argc == 3){
        char time[36];

        File* mydir = new File(argv[2]);
        mydir->Expand();
        std::vector<File*> dirfiles = mydir->getChildrenFile();
        for (int i = 0; i < dirfiles.size() ; ++i) {
            printf("%s   %hu %s %s  %lld  %s %s\n", dirfiles[i]->getPermission().c_str(), dirfiles[i]->getHardlinkNum(), dirfiles[i]->getName().c_str(), dirfiles[i]->getGroupName().c_str(), dirfiles[i]->getFileSize(), formatdate(time, dirfiles[i]->getModTime()), dirfiles[i]->getName().c_str());

        }
    }
    return 0;
}