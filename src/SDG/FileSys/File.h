/*!
 * @file File.h
 *
 * @class File
 * @abstract Class that loads a file's contents from disk into memory.
 * Intended for cleanly wrapping and loading game assets.
 */
#pragma once
#include "Path.h"

struct SDL_RWops;

namespace SDG
{

/// Class that loads a file's contents from disk into memory.
/// Intended for use to cleanly wrap and load game assets.
class File {
    class Impl;
public:
    enum Origin {
        Start,
        End,
        Relative
    };
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

    bool LoadFromRW(SDL_RWops *io);
    
    /// Closes the file, freeing it of internally loaded data.
    /// After a call to Free() you may safely re-use this object to open another file.
    /// This is automatically called when the File object goes out of scope.
    void Close();

    static bool Delete(const Path &filepath);

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

    [[nodiscard]]
    int64_t Capacity() const;

    /// Checks whether file is opened or not.
    /// It may or may not have data loaded into memory. Use IsOpen() to check
    /// for this check.
    [[nodiscard]]
    bool IsOpen() const;

    /// Saves the data into a file at the indicated path.
    /// Returns true
    bool SaveAs(const Path &path) const;

    /// Overwrites the file at the path that this File was previously successfully
    /// opened at. Throws a RuntimeException if the File did not previously load
    /// successfully. Please check IsLoaded() before calling this function.
    /// @returns whether the file saved successfully
    bool Save() const;
     
    template<typename T>
    size_t Write(const T &obj)
    {
        return Write(&obj, sizeof(T));
    }

    size_t Write(const String &str);
    size_t Write(const char *str);
    size_t Write(const void *ptr, size_t size);



    template<typename T>
    size_t Read(T &obj)
    {
        return Read(&obj, sizeof(T));
    }

    template<typename T>
    [[nodiscard]] T Read()
    {
        T obj;
        Read(&obj, sizeof(T));

        return obj;
    }

    size_t Read(void *ptr, size_t size);
    size_t Read(String &str, size_t length);
    size_t Read(char *str, size_t length);

    File &Seek(int64_t bytes, Origin origin = Origin::Start);
    [[nodiscard]] size_t Tell() const;

    File &Reserve(size_t bytes);

    [[nodiscard]] const Path &Filepath() const;

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
