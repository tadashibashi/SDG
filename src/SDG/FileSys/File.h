/* ============================================================================
 *  File.hpp
 *  SDG_Engine
 *
 * ========================================================================= */
#pragma once
#ifndef SDG_File_h
#define SDG_File_h
#include <string>
#include <SDG/FileSys/Path.h>

namespace SDG::FileSys
{

/// Class that loads a file's contents from disk into memory.
/// Intended for use to cleanly wrap and load game assets.
class File {
    class Impl;
public:
    File();
    ~File();
    explicit File(const Path &path);

    /// Loads data found in the file at path into the File class.
    /// @param path path to the file
    bool Open(const Path &path);

    /// Checks whether file is opened or not.
    /// It may or may not have data loaded into memory. Use IsLoaded() to check for this check.
    [[nodiscard]]
    bool IsOpen() const;
    
    /// Checks if data has been loaded into memory or not.
    [[nodiscard]]
    bool IsLoaded() const;
    
    /// Closes the file, freeing it of internally loaded data.
    /// After a call to Free() you may safely re-use this object to open another file.
    /// This is automatically called when the File object goes out of scope.
    void Close();

    // ============= GETTERS =================================================

    /// Gets the pointer to the file data. Always a valid c-string.
    /// Data from a file will be available if param "loadToMemory" was set to true in a succesful call to Open.
    [[nodiscard]]
    const char *Data() const;
    
    [[nodiscard]]
    const char *GetError() const;
    
    /// The size of the file. A null-terminator is automatically appended to the data, but not counted by this function.
    /// Therefore, the result is the same as strlen. This value is set regardless if loadToMemory was set to true after a
    /// successful call to Open.
    [[nodiscard]] int64_t Size() const;
    
private:
    /// Loads data found in the file at path into the File class.
    /// @param filepath path to the file
    bool OpenImpl(const Path &filepath);

    /// Loads an encrypted file
    bool OpenEncryptedImpl(const Path &path);

    /// Private implementation
    Impl *impl;
};

}

#endif /* SDG_File_h */
