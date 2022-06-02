/*!
 * @file Buffer.h
 * @namespace SDG
 * @class Buffer
 */
#pragma once
#include <SDG/Lib/Endian.h>
#include <SDG/Lib/String.h>

namespace SDG
{
    /// Expandable container of bytes, which may be read from and written to.
    class Buffer
    {
    public:
        enum Origin {
            Start,
            End,
            Relative
        };

        /// Default buffer capacity when not specified by the user in the ctor.
        static const size_t DefaultInitCap;

        /// Creates a buffer of data with initial capacity and endianness
        /// @param initCap - initial capacity
        /// @param endian  - target endianness of the data
        Buffer(size_t initCap = DefaultInitCap, Endian endian = Endian::Little);
        Buffer(void *data, size_t size, Endian endian = Endian::Little);

        // When assigning or copying, the buffer's data gets copied and
        // the head gets reset to 0 in the recipient Buffer.
        Buffer(const Buffer &buffer);
        Buffer &operator = (const Buffer &buffer);
        ~Buffer();

        /// Reads a primitive type from the buffer. Other types will result
        /// in undefined behavior due to differences in compiler behavior
        /// for padding/alignment of data in classes and structs.
        /// Buffer read/write head moves forward by sizeof(T).
        template<typename T>
        size_t Read(T &a) const
        {
            return Read(&a, sizeof(T));
        }
        
        /// Reads memory into a buffer. Endianness of the data read is
        /// affected by the Buffer's target data endianness.
        /// @param size size of the memory to read. Should be equal or smaller
        /// than the size of the buffer you're passing.
        /// Buffer read/write head moves forward by size.
        size_t Read(void *buffer, size_t size) const;

        /// Reads characters into a string. String of chars in the source data is
        /// expected to be big-endian. e.g. [h][e][l][l][o]
        /// Buffer read/write head moves forward by length.
        size_t Read(String &str, size_t length) const;

        /// Reads characters into a string buffer; does not append a null-terminator.
        /// Buffer read / write head moves forward by length.
        size_t Read(char *str, size_t length) const;

        /// Same as Read, but does not move the Buffer's read/write head
        template<typename T>
        size_t Peek(T &a) const
        {
            return Peek(&a, sizeof(T));
        }

        /// Same as Read, but does not move the Buffer's read/write head
        size_t Peek(void *buffer, size_t size) const;

        /// Same as Read, but does not move the Buffer's read/write head
        size_t Peek(String &str, size_t length) const;

        /// Same as Read, but does not move the Buffer's read/write head
        size_t Peek(char *str, size_t length) const;

        /// Write a primitive type into the buffer. Other types will result
        /// in undefined behavior due to differences in compiler behavior
        /// for padding/alignment of data in classes and structs.
        /// Buffer read/write head moves forward by sizeof(T).
        template<typename T>
        size_t Write(const T &a)
        {
            return Write(&a, sizeof(a));
        }

        /// Writes an SDG::String into the Buffer.
        /// Will always write string in big-endian.
        /// Buffer read/write head moves forward by String's length.
        size_t Write(const String &str);

        /// Write a null-terminated c-string into the Buffer.
        /// Will always write string in big-endian.
        /// Buffer read/write head moves forward by c-string's length.
        size_t Write(const char *str);

        /// Write a block of bytes into the Buffer.
        /// Buffer's target endianness will be taken into account.
        /// Buffer read/write head moves forward by size.
        size_t Write(const void *bytes, size_t size);

        /// Write a string of characters into the Buffer.
        /// Will always write string in big-endian.
        size_t Write(const char *str, size_t size);

        /// Reserve a specific number of bytes in the buffer to prevent re-allocation
        /// If size > Capacity(), it will expand the internal byte buffer.
        void Reserve(size_t size);

        /// Gets the current size of the Buffer in bytes.
        [[nodiscard]] size_t Size() const noexcept { return end_ - buf_; }

        /// Tells the current byte position in the buffer
        [[nodiscard]] size_t Tell() const noexcept { return head_ - buf_; }

        /// Checks if the buffer is empty.
        [[nodiscard]] size_t Empty() const noexcept { return end_ == buf_; }
        
        /// Gets the full pre-allocated internal byte size of the Buffer. It is
        /// always greater than or equal to Size(). This is set with Reserve,
        /// and automatically increased when Size() > Capacity().
        [[nodiscard]] size_t Capacity() const noexcept { return cap_ - buf_; }
        [[nodiscard]] Endian Endianness() const noexcept { return endian_; }

        /// Moves the Buffer's current read position
        void Seek(int64_t bytes, Origin origin = Start) const;

        /// Resets the Buffer's internal data.
        void Clear() noexcept { end_ = buf_; head_ = buf_; }

        /// Gets the internal byte array. Please be aware that the pointer
        /// retrieved by this function may become invalidated as soon as the
        /// internal capacity is increased by Write or Reserve.
        /// Therefore, it is most useful for quickly copying data rather
        /// than long-term referencing.
        [[nodiscard]] const uint8_t *Data() { return buf_; }

        typedef uint8_t *Iterator;
        typedef const uint8_t *ConstIterator;
        [[nodiscard]] Iterator begin() { return buf_; }
        [[nodiscard]] Iterator end() { return end_; }
        [[nodiscard]] ConstIterator cbegin() { return buf_; }
        [[nodiscard]] ConstIterator cend() { return end_; }

    private:
        uint8_t *buf_, *end_, *cap_;
        mutable uint8_t *head_;
        Endian endian_; // endianness of the target data

        /// Gets pointer position from Position enum and byte position
        /// Parameter "bytes" may be negative or positive.
        [[nodiscard]] uint8_t *GetPosition(int64_t bytes, Origin origin) const;
        void Expand(size_t size);
        void CheckBoundsWrite(uint8_t *ptr);
        void CheckBoundsRead(uint8_t *ptr) const;
        size_t ReadImpl(void *buf, size_t size, bool useEndian, bool moveHead) const;
        size_t WriteImpl(const void *buf, size_t size, bool useEndian);
    };
}
