//
// Created by Zhaohua Liu on 2019-09-17.
//
#include <fstream>
#include <cstdio>
#include <pwd.h>
#include <grp.h>
#include <zconf.h>
#include <dirent.h>
#include <string>
#include "File.hpp"

using namespace std;
    File::File(string name) {

        struct stat buf = {};
        if(stat(name.c_str(), &buf)==-1){
            printf("errON[%d]errMsg[%s]\n",errno,strerror(errno));
            this->setErrorNUm(errno);
            exit(1);
        } else{
            // set File Name
            this->setName(name);
            //set file Type
            if((buf.st_mode & S_IFREG)==S_IFREG){
                this->type = "File";
            } else if((buf.st_mode & S_IFDIR)==S_IFDIR){
                this->type="Dir";
            }
            //set File size
            this->fileSize = buf.st_size;
            //set Owner Id
            this->ownerID = buf.st_uid;
            //set Owner Name
            struct passwd *my_info;
            my_info = getpwuid(this->getOwnerId() );
            this->ownerName = my_info->pw_name;
            // set group id
            this->groupId = buf.st_gid;
            //set group name
            struct group *group_info;
            group_info = getgrgid(this->getGroupId());
            this->groupName =group_info->gr_name;
            //set default permission
            std::string permission = "---------";
            if(stat(name.c_str(), &buf) == 0){
                mode_t perm = buf.st_mode;
                permission[0] = (perm & S_IRUSR) ? 'r' : '-';
                permission[1] = (perm & S_IWUSR) ? 'w' : '-';
                permission[2] = (perm & S_IXUSR) ? 'x' : '-';
                permission[3] = (perm & S_IRGRP) ? 'r' : '-';
                permission[4] = (perm & S_IWGRP) ? 'w' : '-';
                permission[5] = (perm & S_IXGRP) ? 'x' : '-';
                permission[6] = (perm & S_IROTH) ? 'r' : '-';
                permission[7] = (perm & S_IWOTH) ? 'w' : '-';
                permission[8] = (perm & S_IXOTH) ? 'x' : '-';
                permission[9] = '\0';
            }
            this->permission = permission;
            // set last access time
            this->accessTime = buf.st_atime;
            //set modification time
            this->modTime = buf.st_mtime;
            //set status change time
            this->statusChTime = buf.st_ctime;
            //set blocksize
            this->blockSize = buf.st_blksize;
            // initialize the children directory as empty vector
            std::vector<File*> childrenDir;
            this->childrenFile = childrenDir;
            //initialize the error as 0
            this->setErrorNUm(0);
            this->hardlinkNum = buf.st_nlink;
        }

    }
    File::~File() {//destructor
    }

    int File::Dump(std::fstream &FileStream) {
            char path[PATH_MAX];
            string pathname = getcwd(path , PATH_MAX);
            int intErrorNumber;
            if (this->getType() != "File") {
                intErrorNumber = errno;
                char buff[256];
                strerror_r(intErrorNumber,buff,256);
                printf("Error: %s",buff);
                this->setErrorNUm(intErrorNumber);
                return intErrorNumber;
            }
            char buff[getBlockSize()];
            ifstream originFile;
            string fullname = pathname + "/" + this->getName();
            originFile.open(fullname, ifstream::in);
            intErrorNumber = errno;
            if(intErrorNumber != 0){
                this->setErrorNUm(intErrorNumber);
                char buff[256];
                strerror_r(intErrorNumber,buff,256);
                printf("Error: %s",buff);
                return intErrorNumber;
            }
            while(originFile.getline(buff,this->getBlockSize())){
                    FileStream << buff << endl;
            }

            originFile.close();
            return 0;
    }


    int File::Rename(const string Name) {
        int internalerr;
        rename( this->getName().c_str(),  Name.c_str());
        internalerr = errno;
        if(internalerr!=0 && internalerr != EXDEV){
            this->setErrorNUm(internalerr);
            char buff[256];
            strerror_r(internalerr,buff,256);
            printf("Error: %s\n",buff);
            return internalerr;
        }
        return 0;
    }

    int File::Remove() {
        int internalerr;
        if (unlink(this->getName().c_str())<0){
            internalerr = errno;
            this->setErrorNUm(internalerr);
            char buff[256];
            strerror_r(internalerr,buff,256);
            printf("Error: %s",buff);
            return internalerr;
        }
        this->~File();
        return 0;
    }

    int File::Compare(FILE* AnotherFile) {
        char path[PATH_MAX];
        string pathname = getcwd(path , PATH_MAX);
        int internalerr;
        FILE * oringinFile;
        string fullname = pathname + "/" + this->getName();
        oringinFile = fopen (fullname.c_str(), "r");// open this file
        internalerr = errno;
        if (internalerr != 0){
            this->setErrorNUm(internalerr);
            char buff[256];
            strerror_r(internalerr,buff,256);
            printf("Error: %s",buff);
            return internalerr;
        }
        int N = this->getBlockSize();
        char buf1[N];
        char buf2[N];
        do{
            if(fgets(buf1, N, oringinFile)!= NULL && fgets(buf2, N, AnotherFile)!=NULL){
                printf("string1 %s\n", buf1);
                printf("string2 %s\n", buf2);
                if (strcmp(buf1, buf2)!=0){
                    return 1;
                }
            }

        }while (!feof(AnotherFile) && !feof(oringinFile));
        return 0;
}
    int File::Expand() {
        int intErrorNumber;
        struct dirent *entry;
        File * newfile;
        DIR* dir;
        if (this->getType() != "Dir") {
            intErrorNumber = errno;
            char buff[256];
            strerror_r(intErrorNumber,buff,256);
            printf("Error: %s",buff);
            this->setErrorNUm(intErrorNumber);
            return intErrorNumber;
        }
        dir = opendir(this->getName().c_str());
        intErrorNumber = errno;
        if( intErrorNumber!=0 ) {
            this->setErrorNUm(intErrorNumber);
            char buff[256];
            strerror_r(intErrorNumber,buff,256);
            printf("Error: %s",buff);
            return intErrorNumber;
        }
        while((entry=readdir(dir)) != NULL){
            string fullname = this->getName()+ "/" +entry->d_name;
            newfile = new File(fullname);
            newfile->setName(entry->d_name);
            this->childrenFile.push_back(newfile);
            delete newfile;
        }
        closedir(dir);
        return 0;
    }

    //getters for attributes



    const std::string &File::getType() const {
        return type;
    }

    off_t File::getFileSize() const {
        return fileSize;
    }

    uid_t File::getOwnerId() const {
        return ownerID;
    }

    const std::string &File::getOwnerName() const {
        return ownerName;
    }

    gid_t File::getGroupId() const {
        return groupId;
    }

    const std::string &File::getGroupName() const {
        return groupName;
    }

    const std::string &File::getPermission() const {
        return permission;
    }

    time_t File::getAccessTime() const {
        return accessTime;
    }

    time_t File::getModTime() const {
        return modTime;
    }

    time_t File::getStatusChTime() const {
        return statusChTime;
    }

    blksize_t File::getBlockSize() const {
        return blockSize;
    }

    const std::vector<File*> &File::getChildrenFile() const {
        return childrenFile;
    }
int File::getErrorNUm() const {
    return errorNUm;
}



void File::setErrorNUm(int errorNUm) {
    File::errorNUm = errorNUm;
}



nlink_t File::getHardlinkNum() const {
    return hardlinkNum;
}

const string &File::getName() const {
    return name;
}

void File::setName(const string &name) {
    File::name = name;
}
















