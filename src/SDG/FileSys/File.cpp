//
//  File.cpp
//  SDG_Engine
//
#include "File.h"
#include "SDG/FileSys/Private/IO.h"
#include "Path.h"

using std::string;

/// Private implementation class data
class SDG::File::Impl
{
public:
    Impl(): mem(), size(), path(), error(), isOpen(false) {}
    
    char *mem;
    Path path;
    string error;
    size_t size;
    bool isOpen;
}; /* class SDG::File::Impl */

// === Constructor / Destructor ===============================================

SDG::File::File() : impl(new Impl)
{

}

SDG::File::File(const SDG::Path &path) : impl(new Impl)
{
    Open(path);
}

SDG::File::~File()
{
    // Automatically close the file when it goes out of scope.
    Close();
    delete impl;
}

const char *
SDG::File::Data() const
{
    return impl->mem;
}

bool
SDG::File::IsOpen() const
{
    return impl->isOpen;
}

int64_t
SDG::File::Size() const
{
    return impl->size;
}

const char *
SDG::File::GetError() const
{
    return impl->error.data();
}


bool
SDG::File::Open(const Path &path)
{
    return (path.Extension() == "sdgc") ?
           OpenEncryptedImpl(path) :
           OpenImpl(path);
}


bool
SDG::File::OpenImpl(const Path &filepath)
{
    char *mem;
    size_t size;

    if (!IO::ReadFileStr(filepath.Str().Cstr(), &mem, &size))
    {
        impl->error = string("File::Open: error: ") + IO::GetError();
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

bool SDG::File::OpenEncryptedImpl(const Path &path)
{
    bool result = SDG::IO::ReadEncryptedFileStr(path.Str().Cstr(), &impl->mem, &impl->size);
    if (result)
    {
        impl->isOpen = true;
        impl->error = "No errors.";
        impl->path = path;
    }
    else
    {
        impl->error = string("File::OpenEncrypted: error: ") + IO::GetError();
    }

    return result;
}

void
SDG::File::Close()
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
SDG::File::IsLoaded() const
{
    return impl->mem;
}

const SDG::Path &
SDG::File::Filepath() const
{
    return impl->path;
}







