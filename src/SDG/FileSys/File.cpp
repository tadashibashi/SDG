//
//  File.cpp
//  SDG_Engine
//
#include "File.h"
#include <SDG/Exceptions/InvalidArgumentException.h>
#include <SDG/Exceptions/RuntimeException.h>
#include <SDG/FileSys/Private/IO.h>
#include <SDG/Lib/Buffer.h>

namespace SDG
{
    /// Private implementation class data
    class File::Impl
    {
    public:
        Impl(): buf(), path(), error(), isOpen(false) {}
    
        Buffer buf;
        Path path;
        String error;
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

    /// Delete a file at the path
    /// Returns whether or not the file was deleted
    bool
    File::Delete(const Path &filepath)
    {
        return (filepath.FileExists()) ?
            (std::remove(filepath.Str().Cstr()) == 0) :
            false;
    }

    const uint8_t *
    File::Data() const
    {
        return impl->buf.Data();
    }

    const char *
    File::Cstr() const
    {
        return (const char *)impl->buf.Data();
    }

    bool
    File::IsOpen() const
    {
        return impl->isOpen;
    }

    int64_t
    File::Size() const
    {
        return impl->buf.Size();
    }

    int64_t
    File::Capacity() const
    {
        return impl->buf.Capacity();
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
        uint8_t *mem;
        size_t size;

        if (!IO::ReadFileStr(filepath.Str().Cstr(), &mem, &size))
        {
            impl->error = String("File::Open: error: ") + IO::GetError();
            return false;
        }

        // success -> commit changes
        impl->buf = Buffer(mem, size);
        impl->error = "No errors.";
        impl->isOpen = true;
        impl->path = filepath;
        return true;
    }

    bool File::OpenEncryptedImpl(const Path &path)
    {
        uint8_t *mem;
        size_t size;
        bool result = IO::ReadEncryptedFileStr(path.Str().Cstr(), &mem, &size);
        if (result)
        {
            impl->isOpen = true;
            impl->error = "No errors.";
            impl->path = path;
            impl->buf = Buffer(mem, size);
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
        impl->buf.Clear();
        impl->isOpen = false;
        impl->path = Path();
    }

    bool
    File::SaveAs(const Path &path) const
    {
        if (path.Extension() == "sdgc")
            return IO::WriteEncryptedFile(path.Str().Cstr(),
                impl->buf.Data(), impl->buf.Size());
        else
            return IO::WriteFile(path.Str().Cstr(),
                impl->buf.Data(), impl->buf.Size());
    }

    bool
    File::Save() const
    {
        if (IsOpen())
        {
            return SaveAs(impl->path);
        } 
        else
        {
            throw RuntimeException("File::Save: failed to save because "
                "there was no previously opened file.");
        }  
    }

    size_t
    File::Write(const void *ptr, size_t size)
    {
        return impl->buf.Write(ptr, size);
    }

    size_t File::Write(const String &str)
    {
        return impl->buf.Write(str);
    }

    size_t
    File::Write(const char *str)
    {
        return impl->buf.Write(str);
    }

    size_t
    File::Read(void *ptr, size_t size)
    {
        return impl->buf.Read(ptr, size);
    }

    size_t
    File::Read(String &str, size_t length)
    {
        return impl->buf.Read(str, length);
    }

    size_t
    File::Read(char *str, size_t length)
    {
        return impl->buf.Read(str, length);
    }

    File &
    File::Seek(int64_t bytes, Origin origin)
    {
        Buffer::Origin bOrigin;
        switch (origin)
        {
        case Origin::Start: bOrigin = Buffer::Start; break;
        case Origin::End: bOrigin = Buffer::End; break;
        case Origin::Relative: bOrigin = Buffer::Relative; break;
        default: // for potential invalid enum casts
            throw InvalidArgumentException("File::Seek(int64_t bytes, Origin origin)", "origin");
        }


        impl->buf.Seek(bytes, bOrigin);
        return *this;
    }

    size_t
    File::Tell() const
    {
        return impl->buf.Tell();
    }

    File &
    File::Reserve(size_t bytes)
    {
        impl->buf.Reserve(bytes);
        return *this;
    }

    const Path &
    File::Filepath() const
    {
        return impl->path;
    }

}

