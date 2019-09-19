//
// Created by Zhaohua Liu on 2019-09-17.
//

#include <fstream>
#include <iostream>
#include <pwd.h>
#include <cerrno>
#include <grp.h>
#include "File.h"
    File::File(const char *Name) {

        struct stat buf = {};
        if(stat(Name, &buf)==-1){
            printf("errON[%d]errMsg[%s]\n",errno,strerror(errno));
            this->setErrorNUm(errno);
            exit(1);
        } else{
            // set File Name
            this->setName(Name);
            //set file Type
            if((buf.st_mode & S_IFREG)==S_IFREG){
                this->setType("File");
            } else if((buf.st_mode & S_IFDIR)==S_IFDIR){
                this->setType("Dir");
            }
            //set File size
            this->setFileSize(buf.st_size);
            //set Owner Id
            this->setOwnerId(buf.st_uid);
            //set Owner Name
            struct passwd *my_info;
            my_info = getpwuid(this->getOwnerId() );
            this->setOwnerName(my_info->pw_name);
            // set group id
            this->setGroupId(buf.st_gid);
            //set group name
            struct group *group_info;
            group_info = getgrgid(this->getGroupId());
            this->setOwnerName(group_info->gr_name);
            //set default permission
            std::string permission = "---";
            if(buf.st_mode & S_IREAD){
                permission[0] = 'r';
            }
            if(buf.st_mode & S_IWRITE){
                permission[1] = 'w';
            }
            if(buf.st_mode & S_IEXEC){
                permission[2] = 'x';
            }
            // set last access time
            this->setAccessTime(buf.st_atime);
            //set modification time
            this->setModTime(buf.st_mtime);
            //set status change time
            this->setStatusChTime(buf.st_ctime);
            //set blocksize
            this->setBlockSize(buf.st_blksize);
            // initialize the children directory as empty vector
            std::vector<FILE> childrenDir = {};
            this->setChildrenFile(childrenDir);
            //initialize the error as 0
            this->setErrorNUm(0);
        }

    }

    void File::Dump(FILE *FileStream) {



    }
    File::~File() {//destructor
    }

    void File::Rename(std::string Name) {

    }



    //getters for attributes

    const std::string &File::getName() const {
        return Name;
    }

    const std::string &File::getType() const {
        return Type;
    }

    off_t File::getFileSize() const {
        return FileSize;
    }

    uid_t File::getOwnerId() const {
        return OwnerID;
    }

    const std::string &File::getOwnerName() const {
        return OwnerName;
    }

    gid_t File::getGroupId() const {
        return GroupId;
    }

    const std::string &File::getGroupName() const {
        return GroupName;
    }

    const std::string &File::getPermission() const {
        return Permission;
    }

    time_t File::getAccessTime() const {
        return AccessTime;
    }

    time_t File::getModTime() const {
        return ModTime;
    }

    time_t File::getStatusChTime() const {
        return StatusChTime;
    }

    blksize_t File::getBlockSize() const {
        return BlockSize;
    }

    const std::vector<FILE> &File::getChildrenFile() const {
        return ChildrenFile;
    }



    // setters for all attributes
void File::setName(const std::string &name) {
    Name = name;
}

void File::setType(const std::string &type) {
    Type = type;
}

void File::setFileSize(off_t fileSize) {
    FileSize = fileSize;
}

void File::setOwnerId(uid_t ownerId) {
    OwnerID = ownerId;
}

void File::setOwnerName(const std::string &ownerName) {
    OwnerName = ownerName;
}

void File::setGroupId(gid_t groupId) {
    GroupId = groupId;
}

void File::setGroupName(const std::string &groupName) {
    GroupName = groupName;
}


void File::setAccessTime(time_t accessTime) {
    AccessTime = accessTime;
}

void File::setModTime(time_t modTime) {
    ModTime = modTime;
}

void File::setStatusChTime(time_t statusChTime) {
    StatusChTime = statusChTime;
}

void File::setBlockSize(blksize_t blockSize) {
    BlockSize = blockSize;
}

void File::setChildrenFile(const std::vector<FILE> &childrenFile) {
    ChildrenFile = childrenFile;
}

int File::getErrorNUm() const {
    return ErrorNUm;
}

void File::setErrorNUm(int errorNUm) {
    ErrorNUm = errorNUm;
}






