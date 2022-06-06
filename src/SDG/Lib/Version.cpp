#include "Version.h"
#include <SDG/Lib/Platform.h>
#include <SDG/Debug/LogImpl.h>
   

SDG::Version::Version() : major(), minor(), patch()
{

}

SDG::Version::Version(unsigned major, unsigned minor, unsigned patch) :
    major(major), minor(minor), patch(patch)
{

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
