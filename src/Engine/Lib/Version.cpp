#include "Version.h"

#include <Engine/Debug/LogImpl.h>
#include <Engine/Lib/String.h>
#include <Engine/Platform.h>

SDG::Version::Version() : major(), minor(), patch()
{

}

SDG::Version::Version(unsigned major, unsigned minor, unsigned patch) :
    major(major), minor(minor), patch(patch)
{

}

SDG::Version SDG::Version::FromString(const String &str)
{
    Version result;
    auto arr = str.Split('.');
    for (size_t i = 0; i < 3; ++i)
        (&result.major)[i] = i < arr.Size() ? arr[i].ToNumber<unsigned>() : 0;
    return result;
}

bool SDG::Version::operator==(const Version version) const
{
    return Hash() == version.Hash();
}

bool SDG::Version::operator!=(const Version version) const
{
    return !operator==(version);
}

bool SDG::Version::operator>(const Version version) const
{
    return Hash() > version.Hash();
}

bool SDG::Version::operator<(const Version version) const
{
    return Hash() < version.Hash();
}

bool SDG::Version::operator>=(const Version version) const
{
    return !operator<(version);
}

bool SDG::Version::operator<=(const Version version) const
{
    return !operator>(version);
}

unsigned long long SDG::Version::Hash() const
{
    return SDG_VERSION_HASH(major, minor, patch);
}

std::ostream &SDG::operator<<(std::ostream &os, const Version &v)
{
    return os << v.major << '.' << v.minor << '.' << v.patch;
}
