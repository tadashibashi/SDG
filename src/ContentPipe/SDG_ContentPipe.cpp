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
    // Get the arguments
    if (argc < 4)
    {
        ManPrint();
        return 1;
    }
    
    std::string assetDir = argv[1], outDir = argv[2], encryptionKey = argv[3];
    std::map<std::string, long long> cache;
    std::ifstream cacheFile;

    // Open cache file and read into cache
    cacheFile.open("SDG_ContentCache.txt");
    if (cacheFile.is_open())
    {
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
                std::cout << "Error: Missing a comma on line with text \"" << line << "\"\n";
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
    }
    cacheFile.close();

    // Create the asset folder if it doesn't exist
    std::filesystem::directory_entry assetFolder(outDir);
    if (!assetFolder.exists())
    {
        std::filesystem::create_directory(assetFolder.path());
    }


    // For each item in the user's asset directory...
    std::filesystem::recursive_directory_iterator dir(assetDir);
    for (auto &item : dir)
    {
        long long writeTime      = item.last_write_time().time_since_epoch().count();
        std::string relativePath = item.path().string().substr(assetDir.length());
        std::string outFilePath = assetFolder.path().string() + relativePath;

        // Mirror folder structure in target path
        if (item.is_directory())
        {
            if (!std::filesystem::directory_entry(outFilePath).exists())
                std::filesystem::create_directory(outFilePath);
            continue;
        }


        auto it = cache.find(relativePath);
        if (it == cache.end() || writeTime > it->second) // item is new or a newer version exists
        {
            std::ifstream inFile;
            std::ofstream outFile;
            inFile.open(item.path().string(), std::ios::in | std::ios::binary);

            // append .sdgc to files
            {
                if (item.path().has_extension())
                {
                    size_t dotPos = outFilePath.find(item.path().extension().string());
                    outFilePath = outFilePath.substr(0, dotPos) + ".sdgc";
                }
                else
                {
                    outFilePath += ".sdgc";
                }
            }

            // Write the new or updated file
            outFile.open(outFilePath,
                    std::ios::out | std::ios::trunc | std::ios::binary);
            if (!inFile.is_open())
            {
                std::cout << "There was a problem opening file at path: " << item.path() << '\n';
                continue;
            }
            if (!outFile.is_open())
            {
                std::cerr << "There was a problem writing a file at path: " <<
                    assetFolder.path().string() + item.path().relative_path().string() << '\n';
                continue;
            }

            // Encrypt file
            for(int i = 0; true ; ++i)
            {
                unsigned char c = inFile.get();
                if (inFile.eof() || inFile.bad())
                    break;
                unsigned char add = encryptionKey[i % encryptionKey.length()];
                c ^= ~add;
                c = (unsigned char)(c + add - i);
                outFile << c;
            }

            std::cout << "Processing content file (" << relativePath.substr(1) << ")\n";
            cache[relativePath] = writeTime;
        }
    }

    // Output changes to cache file
    std::ofstream outFile;
    outFile.open("SDG_ContentCache.txt", std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "There was a problem opening the SDG_ContentCache.txt file while caching data.\n";
        return 1;
    }

    for (auto & [k, v] : cache)
    {
        outFile << k << "," << v << '\n';
    }
    outFile.close();

    return 0;
}