#pragma once
#include <map>
#include <string>

namespace SDG::ContentPipe
{
    class ContentCache
    {
    public:
        /// Loads cache file info from file at path
        auto Load(const std::string &path) -> bool;

        /// Writes cache file out to path
        auto Write(const std::string &path) -> bool;

        auto EntryIsNewer(const std::string &filename, long long writeTime) -> bool;

        auto &operator[](const std::string &key) { return cache[key]; }
        const auto &operator[](const std::string &key) const { return cache.at(key); }

    private:
        std::map<std::string, long long> cache;
    };
}