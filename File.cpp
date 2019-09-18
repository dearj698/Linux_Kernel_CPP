//
// Created by Zhaohua Liu on 2019-09-17.
//

#include <fstream>
#include "File.h"

File::File(const char *Name) {
    struct stat buf ={};
    stat(Name, &buf);
}

File::~File() {

}

void File::Rename(std::string Name) {

}

void File::Dump(std::fstream FileStream) {

}

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

const std::vector<File> &File::getChildrenFile() const {
    return ChildrenFile;
}

int File::getErrno() const {
    return Errno;
}


