//
//  File.cpp
//  SDG_Engine
//
#include "File.h"
#include "SDG/FileSys/Private/IO.h"
#include "FileSys.h"
#include <SDL_rwops.h>
#include "Path.h"

using std::string;

/// Private implementation class data
class SDG::FileSys::File::Impl
{
public:
    Impl(): mem(), size(), path(), error(), isOpen(false) {}
    
    char *mem;
    Path path;
    string error;
    size_t size;
    bool isOpen;
}; /* class SDG::FileSys::File::Impl */

// === Constructor / Destructor ===============================================

SDG::FileSys::File::File() : impl(new Impl)
{

}

SDG::FileSys::File::File(const SDG::Path &path) : impl(new Impl)
{
    Open(path);
}

SDG::FileSys::File::~File()
{
    // Automatically close the file when it goes out of scope.
    Close();
    delete impl;
}

const char *
SDG::FileSys::File::Data() const
{
    return impl->mem;
}

bool
SDG::FileSys::File::IsOpen() const
{
    return impl->isOpen;
}

int64_t
SDG::FileSys::File::Size() const
{
    return impl->size;
}

const char *
SDG::FileSys::File::GetError() const
{
    return impl->error.data();
}


bool
SDG::FileSys::File::Open(const Path &path)
{
    return (path.Extension() == "sdgc") ?
           OpenEncryptedImpl(path) :
           OpenImpl(path);
}


bool
SDG::FileSys::File::OpenImpl(const Path &filepath)
{
    char *mem;
    size_t size;

    if (!IO::ReadFileStr(filepath.String().c_str(), &mem, &size))
    {
        impl->error = string("File::Open: error: ") + SDL_GetError();
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

bool SDG::FileSys::File::OpenEncryptedImpl(const Path &path)
{
    bool result = SDG::IO::ReadEncryptedFileStr(path.String().c_str(), &impl->mem, &impl->size);
    if (result)
    {
        impl->isOpen = true;
        impl->error = "No errors.";
        impl->path = path;
    }
    else
    {
        impl->error = string("File::OpenEncrypted: error: ") + SDL_GetError();
    }

    return result;
}

void
SDG::FileSys::File::Close()
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
SDG::FileSys::File::IsLoaded() const
{
    return impl->mem;
}







