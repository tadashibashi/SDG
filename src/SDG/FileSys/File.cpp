//
//  File.cpp
//  SDG_Engine
//
#include "File.h"
#include <SDG/FileSys/Private/IO.h>

namespace SDG
{
    /// Private implementation class data
    class File::Impl
    {
    public:
        Impl(): mem(), size(), path(), error(), isOpen(false) {}
    
        char *mem;
        Path path;
        String error;
        size_t size;
        bool isOpen;
    }; /* class File::Impl */

    // === Constructor / Destructor ===============================================

    File::File() : impl(new Impl)
    {

    }

    File::File(const Path &path) : impl(new Impl)
    {
        Open(path);
    }

    File::~File()
    {
        // Automatically close the file when it goes out of scope.
        Close();
        delete impl;
    }

    const char *
    File::Data() const
    {
        return impl->mem;
    }

    bool
    File::IsOpen() const
    {
        return impl->isOpen;
    }

    int64_t
    File::Size() const
    {
        return impl->size;
    }

    const char *
    File::GetError() const
    {
        return impl->error.Cstr();
    }


    bool
    File::Open(const Path &path)
    {
        return (path.Extension() == "sdgc") ?
               OpenEncryptedImpl(path) :
               OpenImpl(path);
    }


    bool
    File::OpenImpl(const Path &filepath)
    {
        char *mem;
        size_t size;

        if (!IO::ReadFileStr(filepath.Str().Cstr(), &mem, &size))
        {
            impl->error = String("File::Open: error: ") + IO::GetError();
            return false;
        }

        // success -> commit changes
        impl->mem = mem;
        impl->size = size;
        impl->error = "No errors.";
        impl->isOpen = true;
        impl->path = filepath;
        return true;
    }

    bool File::OpenEncryptedImpl(const Path &path)
    {
        bool result = IO::ReadEncryptedFileStr(path.Str().Cstr(), &impl->mem, &impl->size);
        if (result)
        {
            impl->isOpen = true;
            impl->error = "No errors.";
            impl->path = path;
        }
        else
        {
            impl->error = String("File::OpenEncrypted: error: ") + IO::GetError();
        }

        return result;
    }

    void
    File::Close()
    {
        if (impl->mem)
        {
            free(impl->mem);
            impl->mem = nullptr;
        }

        impl->isOpen = false;
        impl->size = 0;
        impl->path = Path();
    }

    bool
    File::IsLoaded() const
    {
        return impl->mem;
    }

    const Path &
    File::Filepath() const
    {
        return impl->path;
    }

}

