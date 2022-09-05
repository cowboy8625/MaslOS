#include "genericFileSystemInterface.h"
#include "../mrafs/mrafsFileSystemInterface.h"

namespace FilesystemInterface
{
    GenericFilesystemInterface::GenericFilesystemInterface()
    {
        this->InterfaceType = FilesystemInterfaceType::Generic;
    }


    const char* GenericFilesystemInterface::CreateFile(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->CreateFile(path);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::CreateFile(const char* path, uint64_t sizeInBytes)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->CreateFile(path, sizeInBytes);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::CreateFolder(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->CreateFolder(path);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::DeleteFile(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->DeleteFile(path);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::DeleteFolder(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->DeleteFolder(path);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }


    const char* GenericFilesystemInterface::CopyFile(const char* oldPath, const char* newPath)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->CopyFile(oldPath, newPath);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::CopyFolder(const char* oldPath, const char* newPath)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->CopyFolder(oldPath, newPath);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::RenameFile(const char* oldPath, const char* newPath)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->RenameFile(oldPath, newPath);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::RenameFolder(const char* oldPath, const char* newPath)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->RenameFolder(oldPath, newPath);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }


    bool GenericFilesystemInterface::FileExists(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->FileExists(path);
            }
        }
        return false;
    }

    bool GenericFilesystemInterface::FolderExists(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->FolderExists(path);
            }
        }
        return false;
    }


    FileInfo* GenericFilesystemInterface::GetFileInfo(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->GetFileInfo(path);
            }
        }
        return NULL;
    }

    FolderInfo* GenericFilesystemInterface::GetFolderInfo(const char* path)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->GetFolderInfo(path);
            }
        }
        return NULL;
    }


    const char** GenericFilesystemInterface::GetFiles(const char* path, uint64_t* outCount)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->GetFiles(path, outCount);
            }
        }
        return NULL;
    }

    const char** GenericFilesystemInterface::GetFolders(const char* path, uint64_t* outCount)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->GetFolders(path, outCount);
            }
        }
        return NULL;
    }

    uint64_t GenericFilesystemInterface::ReadFile(const char* path, void** buffer)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->ReadFile(path, buffer);
            }
        }
        return 0;
    }


    const char* GenericFilesystemInterface::ReadFile(const char* path, uint64_t byteCount, void* buffer)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->ReadFile(path, byteCount, buffer);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::WriteFile(const char* path, uint64_t byteCount, void* buffer)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->WriteFile(path, byteCount, buffer);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::ReadFileBuffer(const char* path, uint64_t address, uint64_t byteCount, void* buffer)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->ReadFileBuffer(path, address, byteCount, buffer);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::WriteFileBuffer(const char* path, uint64_t address, uint64_t byteCount, void* buffer)
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->WriteFileBuffer(path, address, byteCount, buffer);
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    
    const char* GenericFilesystemInterface::InitAndSaveFSTable()
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->InitAndSaveFSTable();
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::SaveFSTable()
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->SaveFSTable();
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

    const char* GenericFilesystemInterface::LoadFSTable()
    {
        switch (this->InterfaceType)
        {
            case FilesystemInterfaceType::Mrafs:
            {
                return ((MrafsFilesystemInterface*)this)->LoadFSTable();
            }
        }
        return FSCommandResult.ERROR_GENERIC_INTERFACE;
    }

}
