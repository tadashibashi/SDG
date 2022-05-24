#include "Buffer.h"
#include <SDG/Debug/Assert.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Math/Math.h>
#include <SDG/Memory.h>
#include <SDG/Platform.h>

#include <cstring>

namespace SDG
{
    /// Copies data while matching endianness
    static void *MemcpyEndian(void *dest, const void *src, size_t size, Endian endian)
    {
        if (SystemEndian() == endian)
        {
            for (uint8_t *p = (uint8_t *)src, *end_ = (uint8_t *)src + size, *targ = (uint8_t *)dest;
                p != end_; ++p, ++targ)
            {
                *targ = *p;
            }
        }
        else
        {
            for (uint8_t *p = (uint8_t *)src, *end_ = (uint8_t *)src + size, *targ = (uint8_t *)dest + size - 1;
                p != end_; ++p, --targ)
            {
                *targ = *p;
            }
        }

        return dest;
    }

    Buffer::Buffer(size_t initCap, Endian endian) :
        buf_(Malloc<uint8_t>(initCap)), head_(buf_), end_(buf_), 
        endian_(endian == Endian::Unknown ? SystemEndian() : endian), 
        cap_(buf_ + initCap)
    {

    }

    Buffer::Buffer(void *data, size_t size, Endian endian) :
        buf_((uint8_t *)data), head_(buf_), end_(buf_ + size),
        endian_(endian), cap_(buf_ + size)
    {

    }

    Buffer::Buffer(const Buffer &buffer) :
        buf_(Malloc<uint8_t>(buffer.Capacity())), head_(buf_), 
        end_(buf_ + buffer.Size()), endian_(buffer.Endianness()),
        cap_(buf_ + buffer.Capacity())
    {
        memcpy(buf_, buffer.buf_, buffer.Size());
    }

    Buffer &
    Buffer::operator = (const Buffer &buffer)
    {
        if (Capacity() < buffer.Capacity())
            Expand(buffer.Capacity());
        head_ = buf_;
        end_ = buf_ + buffer.Size();
        memcpy(buf_, buffer.buf_, buffer.Size());

        return *this;
    }

    Buffer::~Buffer()
    {
        Free(buf_);
    }

    /// Reads memory into the buffer. Endianness of the data read is
    /// affected by the target data endianness.
    /// @param size size of the memory to read. Should be equal or smaller
    /// than the size of the buffer you're passing.
    size_t
    Buffer::Read(void *buffer, size_t size)
    {
        CheckBounds(head_ + size, false);
        MemcpyEndian(buffer, head_, size, endian_);
        head_ += size;
        return size;
    }

    size_t
    Buffer::Read(String &str, size_t length)
    {
        CheckBounds(head_ + length, false);
        str = String((const char *)head_, length);
        head_ += length;
        return length;
    }

    size_t
    Buffer::Read(char *str, size_t length)
    {
        CheckBounds(head_ + length, false);
        memcpy(str, head_, length);
        head_ += length;
        return length;
    }

    size_t Buffer::Write(const String &str)
    {
        return Write(str.Cstr(), str.Length());
    }

    size_t
    Buffer::Write(const char *str)
    {
        if (!str) return 0;
        return Write(str, strlen(str));
    }

    size_t
    Buffer::Write(const void *buffer, size_t size)
    {
        CheckBounds((uint8_t *)head_ + size, true);
        MemcpyEndian(head_, buffer, size, endian_);
        head_ += size;
        if (head_ > end_)
            end_ = head_;
        return size;
    }

    size_t
    Buffer::Write(const char *buffer, size_t size)
    {
        CheckBounds((uint8_t *)head_ + size, true);
        memcpy(head_, buffer, size);
        head_ += size;
        if (head_ > end_)
            end_ = head_;
        return size;
    }

    Buffer &
    Buffer::Reserve(size_t size)
    {
        Expand(size);
        return *this;
    }

    Buffer &
    Buffer::Seek(int64_t bytes, Position origin)
    {
        uint8_t *position = GetPosition(bytes, origin);
        CheckBounds(position, false);
        head_ = position;
        return *this;
    }

    uint8_t *
    Buffer::GetPosition(int64_t bytes, Position origin)
    {
        switch (origin)
        {
        case Position::Start:
            return buf_ + bytes;
        case Position::End:
            return end_ + bytes;
        case Position::Relative:
            return head_ + bytes;
        default:
            return nullptr;
        }
    }

    void
    Buffer::Expand(size_t newCap)
    {
        size_t position = Tell();
        size_t size = Size();

        if (newCap > Capacity())
        {
            buf_ = Realloc(buf_, newCap);
            head_ = buf_ + position;
            end_ = buf_ + size;
            cap_ = buf_ + newCap;
        }
    }

    void
    Buffer::CheckBounds(uint8_t *ptr, bool writing)
    {
        if (writing)
        {
            if (ptr < buf_)
                throw OutOfRangeException((uintptr_t)ptr - (uintptr_t)buf_ - 1, "Attempted to write data outside of Buffer bounds");
            else if (ptr > cap_)
                Expand((ptr-buf_) * 2 + 1);    
        }
        else
        {
            if (ptr < buf_ || ptr > end_)
            {
                throw OutOfRangeException((uintptr_t)ptr - (uintptr_t)buf_ - 1, "Attempted to read/seek outside of Buffer's bounds. "
                    "Max position: " + std::to_string(end_-buf_));
            }
        }
    }
}
