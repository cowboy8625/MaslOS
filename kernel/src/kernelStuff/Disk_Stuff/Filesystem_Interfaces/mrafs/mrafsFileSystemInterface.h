#pragma once
#include "../generic/genericFileSystemInterface.h"

namespace FilesystemInterface
{
    class MrafsFilesystemInterface : public GenericFilesystemInterface
    {
    public:
        struct FSPartitionInfo
        {
            uint64_t sizeInBytes;
            uint64_t locationInBytes;
            bool free;
        };


    private:
        int64_t GetIndexOfPartitionFromLocation(uint64_t location);
        int64_t GetIndexOfFreeFilePartition(uint64_t sizeInBytes);
        FSPartitionInfo* CreateFilePartition(uint64_t size);
        const char* ResizeFilePartition(FSPartitionInfo* partition, uint64_t newSize);
        const char* DeleteFilePartition(FSPartitionInfo* partition);
        //const char* WipeFilePartition(FSPartitionInfo* partition);


    public:

        
        const uint64_t maxFSTableSize = 5000000;
    
        //FilesystemInterfaceType InterfaceType = FilesystemInterface::Mrafs;
        List<void*> fsPartitionList = List<void*>(10);
        List<FileInfo*> fsFileList = List<FileInfo*>(10);
        List<FolderInfo*> fsFolderList = List<FolderInfo*>(10);
        //void* partitionInterface = NULL;
        MrafsFilesystemInterface(PartitionInterface::GenericPartitionInterface* partitionInterface, PartitionInterface::PartitionInfo* partitionInfo);
        
        FileInfo* GetFile(const char* path);
        FolderInfo* GetFolder(const char* path);

        const char* CreateFile(const char* path);
        const char* CreateFolder(const char* path);

        const char* DeleteFile(const char* path);
        const char* DeleteFolder(const char* path);

        const char* CopyFile(const char* oldPath, const char* newPath);
        const char* CopyFolder(const char* oldPath, const char* newPath);

        const char* RenameFile(const char* oldPath, const char* newPath);
        const char* RenameFolder(const char* oldPath, const char* newPath);

        bool FileExists(const char* path);
        bool FolderExists(const char* path);

        FileInfo* GetFileInfo(const char* path);
        FolderInfo* GetFolderInfo(const char* path);

        const char** GetFiles(const char* path);

        const char* ReadFile(const char* path, void** buffer);

        const char* ReadFile(const char* path, uint64_t byteCount, void* buffer);
        const char* WriteFile(const char* path, uint64_t byteCount, void* buffer);

        const char* InitAndSaveFSTable();
        const char* SaveFSTable();
        const char* LoadFSTable();
    };
}