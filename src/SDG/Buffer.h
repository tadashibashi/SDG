/*!
 * @file Buffer.h
 * @namespace SDG
 * @class Buffer
 */
#pragma once
#include <SDG/String.h>
#include <SDG/Math/Endian.h>
#include <SDG/Position.h>

namespace SDG
{

    /// Helper class for reading and writing file's contents within
    class Buffer
    {
    public:
        const size_t DefaultInitCap = 32;

        /// Creates a buffer of data with initial capacity and endianness
        /// @param initCap - initial capacity
        /// @param endian  - target endianness of the data
        Buffer(size_t initCap = 32, Endian endian = Endian::Little);
        Buffer(void *data, size_t size, Endian endian = Endian::Little);

        // When assigning or copying, the buffer's data gets copied and
        // the head gets reset to 0 in the recipient Buffer.
        Buffer(const Buffer &buffer);
        Buffer &operator = (const Buffer &buffer);
        ~Buffer();

        /// Reads a primitive type from the buffer
        template<typename T>
        size_t Read(T &a)
        {
            return Read(&a, sizeof(a));
        }
        
        /// Reads memory into a buffer. Endianness of the data read is
        /// affected by the Buffer's target data endianness.
        /// @param size size of the memory to read. Should be equal or smaller
        /// than the size of the buffer you're passing.
        size_t Read(void *buffer, size_t size);

        /// Reads characters into a string. String of chars in the source data is
        /// expected to be big-endian. e.g. [h][e][l][l][o]
        size_t Read(String &str, size_t length);

        size_t Read(char *str, size_t length);

        template<typename T>
        size_t Write(const T &a)
        {
            return Write(&a, sizeof(a));
        }

        size_t Write(const String &str);
        size_t Write(const char *str);

        size_t Write(const void *buffer, size_t size);
        size_t Write(const char *buffer, size_t size);

        Buffer &Reserve(size_t size);

        /// Gets the byte size of the entire buffer
        [[nodiscard]] size_t Size() const noexcept { return end_ - buf_; }
        /// Tells the current byte position in the buffer
        [[nodiscard]] size_t Tell() const noexcept { return head_ - buf_; }
        [[nodiscard]] size_t Empty() const noexcept { return end_ == buf_; }
        
        [[nodiscard]] size_t Capacity() const noexcept { return cap_ - buf_; }
        [[nodiscard]] Endian Endianness() const noexcept { return endian_; }

        /// Moves the Buffer's current read position
        Buffer &Seek(int64_t bytes, Position origin = Position::Start);
        Buffer &Clear() noexcept { end_ = buf_; head_ = buf_; return *this; }

        [[nodiscard]] const uint8_t *Data() { return buf_; }

        typedef uint8_t *iterator;
        iterator begin() { return buf_; }
        iterator end() { return end_; }
    private:
        uint8_t *buf_, *head_, *end_, *cap_;
        Endian endian_; // endianness of the target data

        /// Gets a pointer position from BufferOrigin and byte position
        /// @param bytes  - number of bytes that stems from the origin
        /// @param origin - the position from which bytes will be counted
        /// @returns the resulting pointer
        [[nodiscard]] uint8_t *GetPosition(int64_t bytes, Position origin);
        void Expand(size_t size);
        void CheckBounds(uint8_t *ptr, bool writing);
    };
}
