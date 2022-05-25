/*!
 * @file File.h
 *
 * @class File
 * @abstract Class that loads a file's contents from disk into memory.
 * Intended for cleanly wrapping and loading game assets.
 */
#pragma once
#include "Path.h"
#include <SDG/Position.h>

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

    /// Gets the pointer to the file data.
    [[nodiscard]]
    const uint8_t *Data() const;

    /// Gets the data as a c-string text data.
    [[nodiscard]]
    const char *Cstr() const;

    /// Gets the result of the last call to Open.
    [[nodiscard]]
    const char *GetError() const;
    
    /// The size of the file. A null-terminator is automatically appended to 
    /// the file data, but not counted by this function.
    [[nodiscard]]
    int64_t Size() const;

    /// Checks whether file is opened or not.
    /// It may or may not have data loaded into memory. Use IsLoaded() to check
    /// for this check.
    [[nodiscard]]
    bool IsOpen() const;

    /// Checks if data has been loaded into memory or not.
    [[nodiscard]]
    bool IsLoaded() const;

    /// Saves the data into a file at the indicated path.
    /// Returns true
    bool Save(const Path &path) const;

    /// Overwrites the file at the path that the file was previously opened at.
    /// It will fail to save if the File did not previously load successfully.
    bool Save() const;

    template<typename T>
    size_t Write(const T &obj)
    {
        return Write(&obj, sizeof(T));
    }

    size_t Write(const void *ptr, size_t size);
    size_t Write(const String &str);
    size_t Write(const char *str);

    template<typename T>
    size_t Read(T &obj)
    {
        return Read(&obj, sizeof(T));
    }

    size_t Read(void *ptr, size_t size);
    size_t Read(String &str, size_t length);
    size_t Read(char *str, size_t length);

    File &Seek(int64_t bytes, Position origin = Position::Start);
    size_t Tell() const;

    File &Reserve(size_t bytes);

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
