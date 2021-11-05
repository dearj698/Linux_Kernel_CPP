#include <iostream>
#include "File.hpp"

char *formatdate(char* string, time_t val){
    strftime(string, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
    return string;
};

using namespace std;
int main(int argc, char* argv[]) {
    char time[36];
    File* myfile = new File(argv[1]);
    printf("FIle Name: %s\n", myfile->getName().c_str());
    printf("File Type: %s\n",myfile->getType().c_str());
    printf("FIle size: %lld\n", myfile->getFileSize());
    printf("File OwnerID: %d\n", myfile->getOwnerId());
    printf("File Owner: %s\n",myfile->getOwnerName().c_str());
    printf("File GroupID: %d\n", myfile->getGroupId());
    printf("File Group: %s\n",myfile->getGroupName().c_str());
    printf("File Permission: %s\n", myfile->getPermission().c_str());
    printf("File access time: %s\n", formatdate(time, myfile->getAccessTime()));
    printf("File change time: %s\n", formatdate(time, myfile->getStatusChTime()));
    printf("File modification time: %s\n", formatdate(time, myfile->getModTime()));
    printf("File block size: %d\n", myfile->getBlockSize());
    printf("error nums: %d\n", myfile->getErrorNUm());
    return 0;
}


