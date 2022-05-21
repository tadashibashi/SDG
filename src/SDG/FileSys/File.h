/*!
 * @file File.h
 *
 * @class File
 * @abstract Class that loads a file's contents from disk into memory.
 * Intended for cleanly wrapping and loading game assets.
 */
#pragma once
#include <SDG/FileSys/Path.h>

namespace SDG
{

/// Class that loads a file's contents from disk into memory.
/// Intended for use to cleanly wrap and load game assets.
class File {
    class Impl;
public:
    // ========== Initialization and Destruction ==========
    /// Initializes an unloaded file.
    File();
    /// Automatically closes and frees any file contents loaded in this class.
    ~File();
    /// Initializes and opens file from specified path.
    explicit File(const Path &path);

    /// Loads data found in the file at path into the File class.
    /// @param path path to the file
    bool Open(const Path &path);
    
    /// Closes the file, freeing it of internally loaded data.
    /// After a call to Free() you may safely re-use this object to open another file.
    /// This is automatically called when the File object goes out of scope.
    void Close();

    // ============= Getters =================================================

    /// Gets the pointer to the file data. Always a valid c-string.
    [[nodiscard]]
    const char *Data() const;

    /// Gets the result of the last call to Open.
    [[nodiscard]]
    const char *GetError() const;
    
    /// The size of the file. A null-terminator is automatically appended to the file data, but not counted by this function.
    [[nodiscard]]
    int64_t Size() const;

    /// Checks whether file is opened or not.
    /// It may or may not have data loaded into memory. Use IsLoaded() to check for this check.
    [[nodiscard]]
    bool IsOpen() const;

    /// Checks if data has been loaded into memory or not.
    [[nodiscard]]
    bool IsLoaded() const;

    const Path &Filepath() const;
    
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
