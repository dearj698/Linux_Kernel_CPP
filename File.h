//
// Created by Zhaohua Liu on 2019-09-17.
//

#ifndef INC_3307_FILE_H
#define INC_3307_FILE_H
#include <string>
#include <sys/stat.h>
#include <vector>
#include <cstdio>
class File {


private:
        std::string Name;

        std::string Type;

        off_t FileSize{};

        uid_t OwnerID{};

        std::string OwnerName;

        gid_t GroupId{};

        std::string GroupName;

        std::string Permission;

        time_t    AccessTime{};

        time_t    ModTime{};   /* time of last modification */

        time_t    StatusChTime{};   /* time of last status change */

        blksize_t BlockSize{};

        std::vector<FILE> ChildrenFile;

        int ErrorNUm;

public:
        explicit File(const char * Name);

        void Dump(FILE* FileStream);

        void Rename(std::string Name);

        void Remove();

        bool Compare(FILE AnotherFile);

        void Expand();

        const std::string &getName() const;

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

        const std::vector<FILE> &getChildrenFile() const;

        int getErrorNUm() const;

        // setters for all attributes
        void setName(const std::string &name);

        void setType(const std::string &type);

        void setFileSize(off_t fileSize);

        void setOwnerId(uid_t ownerId);

        void setOwnerName(const std::string &ownerName);

        void setGroupId(gid_t groupId);

        void setGroupName(const std::string &groupName);

        void setAccessTime(time_t accessTime);

        void setModTime(time_t modTime);

        void setStatusChTime(time_t statusChTime);

        void setBlockSize(blksize_t blockSize);

        void setChildrenFile(const std::vector<FILE> &childrenFile);

        void setErrorNUm(int errorNUm);

         ~File();
};


#endif //INC_3307_FILE_H
