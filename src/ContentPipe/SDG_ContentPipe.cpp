#include <SDG/Crypto.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
void ManPrint()
{
    std::cout << "SDG_ContentPipe <assetDir> <outDir>\n";
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        ManPrint();
        return 1;
    }
    
    std::string assetDir = argv[1];
    std::string outDir = argv[2];

    std::map<std::string, uint64_t> cache;
    std::ifstream cacheFile;

    // Open cache file and fill it
    cacheFile.open(assetDir + "/.ContentCache.txt");
    if (cacheFile.is_open())
    {
        while (cacheFile)
        {        
            std::string line;
            std::getline(cacheFile, line);
            
            if (cacheFile.bad())
                break;

            size_t commaPos = line.find_first_of(',');
            std::string filename;
            if (commaPos == std::string::npos)
            {
                std::cout << "Error: Missing a comma on line with text \"" << line << "\"\n";
                continue;
            }

            filename = line.substr(0, commaPos);
                
            
            uint64_t lastEdited;
            
            try {
                lastEdited = std::stoull(line.substr(commaPos + 1));
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "There was a problem converting number on line with text \"" << line << "\"\n";
                continue;
            }
            
            cache[filename] = lastEdited;

            if (cacheFile.eof())
                break;
        }
    }

    std::cout << "Current Cache: \n";
    for (auto & [k, v] : cache)
    {
        std::cout << k << ": " << v << '\n';
    }

    std::filesystem::recursive_directory_iterator dir(assetDir);
    


    return 0;
}