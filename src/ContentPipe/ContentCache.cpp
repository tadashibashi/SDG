#include "ContentCache.h"
#include <fstream>
#include <iostream>

namespace SDG::ContentPipe
{
    auto ContentCache::Load(const std::string &path) -> bool
    {
        // Open cache file and read into cache
        std::ifstream cacheFile(path);
        if (!cacheFile.is_open())
        {
            std::cout << "New content cache file will be generated at (" << path << ")\n";
            return false;
        }

        // Populate cache from file
        std::map<std::string, long long> cache;
        while (cacheFile)
        {
            std::string line;
            std::getline(cacheFile, line);

            if (cacheFile.bad())
                break;
            if (line.empty())
                continue;

            size_t commaPos = line.find_first_of(',');
            std::string filename;
            if (commaPos == std::string::npos)
            {
                std::cout << "Warning: Missing a comma on line with text \"" << line << "\"\n";
                continue;
            }

            filename = line.substr(0, commaPos);


            long long lastEdited;
            try {
                lastEdited = std::stoll(line.substr(commaPos + 1));
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "Invalid timestamp on line with text \"" << line << "\"\n";
                continue;
            }

            cache[filename] = lastEdited;

            // getline sets eof bit on reading the last line.
            // That's why the check for eof occurs after reading.
            if (cacheFile.eof())
                break;
        }
        cacheFile.close();

        // Populating complete with no errors, commit changes
        this->cache.swap(cache);
        return true;
    }

    auto ContentCache::Write(const std::string &path) -> bool
    {
        std::ofstream outFile;
        outFile.open(path, std::ios::out | std::ios::trunc);
        if (!outFile.is_open())
        {
            std::cerr << "There was a problem opening the SDG_ContentCache.txt file while caching data.\n";
            return false;
        }

        for (const auto &[k, v] : cache)
        {
            outFile << k << "," << v << '\n';
        }
        outFile.close();

        return true;
    }

    auto ContentCache::EntryIsNewer(const std::string &filename, long long writeTime) -> bool
    {
        auto it = cache.find(filename);
        return (it == cache.end() || writeTime > it->second);
    }
}