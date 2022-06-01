#include "Buffer.h"
#include <SDG/Debug/Assert.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Math/Math.h>
#include <SDG/Lib/Memory.h>
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

    const size_t Buffer::DefaultInitCap = 32;

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

    size_t
    Buffer::Read(void *buffer, size_t size) const
    {
        return ReadImpl(buffer, size, true, true);
    }

    size_t
    Buffer::Read(String &str, size_t length) const
    {
        CheckBoundsRead(head_ + length);
        str = String((const char *)head_, length);
        head_ += length;
        return length;
    }

    size_t
    Buffer::Read(char *str, size_t length) const
    {
        return ReadImpl(str, length, false, true);
    }

    size_t
    Buffer::Peek(void *buffer, size_t size) const
    {
        return ReadImpl(buffer, size, true, false);
    }

    size_t
    Buffer::Peek(String &str, size_t length) const
    {
        CheckBoundsRead(head_ + length);
        str = String((const char *)head_, length);
        return length;
    }

    size_t
    Buffer::Peek(char *str, size_t length) const
    {
        return ReadImpl(str, length, false, false);
    }

    size_t
    Buffer::Write(const String &str)
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
        return WriteImpl(buffer, size, true);
    }

    size_t
    Buffer::Write(const char *buffer, size_t size)
    {
        return WriteImpl(buffer, size, false);
    }

    void
    Buffer::Reserve(size_t size)
    {
        Expand(size);
    }

    void
    Buffer::Seek(int64_t bytes, Position origin) const
    {
        uint8_t *position = GetPosition(bytes, origin);
        CheckBoundsRead(position);
        head_ = position;
    }

    uint8_t *
    Buffer::GetPosition(int64_t bytes, Position origin) const
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
        if (newCap > Capacity())
        {
            // These vals need to be cached before mutating Buffer
            size_t position = Tell();
            size_t size = Size();

            // Commit changes
            buf_ = Realloc(buf_, newCap);
            head_ = buf_ + position;
            end_ = buf_ + size;
            cap_ = buf_ + newCap;
        }
    }

    void
    Buffer::CheckBoundsWrite(uint8_t *ptr)
    {
        if (ptr < buf_)
            throw OutOfRangeException((uintptr_t)ptr - (uintptr_t)buf_ - 1,
                "Attempted to write data outside of Buffer bounds");
        else if (ptr > cap_)
            Expand((ptr - buf_) * 2 + 1);
    }

    void
    Buffer::CheckBoundsRead(uint8_t *ptr) const
    {
        if (ptr < buf_ || ptr > end_)
        {
            throw OutOfRangeException((uintptr_t)ptr - (uintptr_t)buf_ - 1, "Attempted to read/seek outside of Buffer's bounds. "
                "Max position: " + std::to_string(end_-buf_));
        }
    }

    size_t
    Buffer::ReadImpl(void *buf, size_t size, bool useEndian, bool moveHead) const
    {
        CheckBoundsRead(head_ + size);
        if (useEndian)
            MemcpyEndian(buf, head_, size, endian_);
        else
            memcpy(buf, head_, size);

        if (moveHead)
            head_ += size;

        return size;
    }

    size_t
    Buffer::WriteImpl(const void *buf, size_t size, bool useEndian)
    {
        CheckBoundsWrite(head_ + size); // check in-bounds and cap expansion
        if (useEndian)
            MemcpyEndian(head_, buf, size, endian_);
        else
            memcpy(head_, buf, size);

        head_ += size;    // move the read/write head

        if (head_ > end_) // move end ptr when writing beyond it
            end_ = head_;

        return size;
    }
}
