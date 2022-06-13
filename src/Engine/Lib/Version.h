#pragma once
#include <iosfwd>
#include <cstdint>

/// Supports patch numbers up to 9,999,999, minor versions up to 9,999
#define SDG_VERSION_HASH(major, minor, patch) \
    ((major) * 100'000'000'000ull + (minor) * 10'000'000ull + (patch))

namespace SDG
{
    class Version
    {
        friend std::ostream &operator << (std::ostream &os, const Version &v);
    public:
        Version();
        Version(unsigned major, unsigned minor, unsigned patch = 0);

        static Version FromString(const class String &str);

        [[nodiscard]] bool operator == (const Version version) const;
        [[nodiscard]] bool operator != (const Version version) const;
        [[nodiscard]] bool operator > (const Version version) const;
        [[nodiscard]] bool operator < (const Version version) const;
        [[nodiscard]] bool operator >= (const Version version) const;
        [[nodiscard]] bool operator <= (const Version version) const;

        [[nodiscard]] unsigned Major() const { return major; }
        [[nodiscard]] unsigned Minor() const { return minor; }
        [[nodiscard]] unsigned Patch() const { return patch; }

        unsigned long long Hash() const;
    private:
        unsigned major, minor, patch;
        static Version engineVersion;
    };

    std::ostream &operator << (std::ostream &os, const Version &v);
}