//
// Created by Zhaohua Liu on 2019-09-17.
//

#ifndef INC_3307_FILE_HPP
#define INC_3307_FILE_HPP
#include <string>
#include <sys/stat.h>
#include <vector>
#include <cstdio>
class File {




private:
    std::string name;
public:
    const std::string &getName() const;

    void setName(const std::string &name);


private:

    std::string type;

        off_t fileSize;

        uid_t ownerID;

        std::string ownerName;

        gid_t groupId;

        std::string groupName;

        std::string permission;

        time_t    accessTime;

        time_t    modTime;   /* time of last modification */

        time_t    statusChTime;   /* time of last status change */

        blksize_t blockSize;

        std::vector<File*> childrenFile;

        nlink_t hardlinkNum;
public:
    nlink_t getHardlinkNum() const;

private:

    int errorNUm;
public:
    void setErrorNUm(int errorNUm);



public:
        explicit File(std::string name);

        int Dump(std::fstream &fileStream);

        int Rename(std::string name);

        int Remove();

        int Compare(FILE* anotherFile);

        int Expand();


        const std::string &getType() const;

        off_t getFileSize() const;

        uid_t getOwnerId() const;

        const std::string &getOwnerName() const;

        gid_t getGroupId() const;

        const std::string &getGroupName() const;

        const std::string &getPermission() const;

        time_t getAccessTime() const;

        time_t getModTime() const;

        time_t getStatusChTime() const;

        blksize_t getBlockSize() const;

        const std::vector<File*> &getChildrenFile() const;

        int getErrorNUm() const;




         ~File();
};


#endif //INC_3307_FILE_HPP
