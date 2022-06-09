/* ====================================================================================================================
 * File: IO.h
 * Contains low-level functions for file reading and writing, using SDL2 as a backend for cross-platform 
 * functionality
 * ================================================================================================================== */
#pragma once

#include <cstddef>
#include <vector>

namespace SDG::IO
{
    /// Get the last error that occured in one of the IO functions. Not thread safe...
    const char *GetError();

    /// Reads data from a file into a null-terminated c-string. Same as ReadFile, but with a null terminator.
    /// @param path the filepath
    /// @param data [out] the data to receive
    /// @param size [out] the size of the data in bytes, NOT including the null terminator.
    /// @returns true on a successful file read--the data ptr is live and becomes the user's
    /// responsibility to free. If false, data will receive a nullptr, and size will receive 0.
    bool ReadFileStr(const char *path, uint8_t **data, size_t *size);

    /// Reads data from a file into a buffer.
    /// @param path the filepath
    /// @param data [out] the data to receive
    /// @param size [out] the size of the data in bytes.
    /// @returns true on a successful file read--the data ptr is live and becomes the user's
    /// responsibility to free. If false, data will receive a nullptr, and size will receive 0.
    bool ReadFile(const char *path, uint8_t **data, size_t *size);

    /// Reads data from a file into a null-terminated c-string. Same as ReadFile, but with a null terminator.
    /// @param path the filepath
    /// @param data [out] the data to receive
    /// @param size [out] the size of the data in bytes, NOT including the null terminator.
    /// @returns true on a successful file read--the data ptr is live and becomes the user's
    /// responsibility to free. If false, data will receive a nullptr, and size will receive 0.
    bool ReadEncryptedFileStr(const char *path, uint8_t **data, size_t *size);

    /// Reads data from a file into a buffer.
    /// @param path the filepath
    /// @param data [out] the data to receive
    /// @param size [out] the size of the data in bytes.
    /// @returns true on a successful file read--the data ptr is live and becomes the user's
    /// responsibility to free. If false, data will receive a nullptr, and size will receive 0.
    bool ReadEncryptedFile(const char *path, uint8_t **data, size_t *size);

    bool WriteEncryptedFile(const char *path, const uint8_t *mem, size_t size);
    bool WriteFile(const char *path, const uint8_t *mem, size_t size);
}
