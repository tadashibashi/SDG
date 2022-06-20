#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <crunch.hpp>
#include <nlohmann/json.hpp>
#include "ContentCache.h"

namespace fs = std::filesystem;
using namespace std::string_literals;

const std::string CacheFilename = "SDG_ContentCache.txt";

void PrintManual()
{
    std::cout << "SDG_ContentPipe <assetDir> <outDir> <encryptionKey> <configPath>\n\n"
        << "  parameters:\n"
        << "    assetDir      - project's asset directory\n"
        << "    outDir        - output asset directory\n"
        << "    encryptionKey - key to encrypt files with\n"
        << "    configPath    - path to config json file. An array of objects with \"type\" and \"path\" fields, indicating target assets to process and copy.\n";
}

void CreateAtlas(const std::string &sourceFolder, const std::string &dest)
{
    // Make sure the source textures exist
    if (!fs::exists(sourceFolder))
    {
        std::cerr << "Error: failed to create texture atlas: source folder does not exist (" << sourceFolder << ")\n";
        return;
    }

    // Create atlas parent folder if it doesn't exist
    fs::path atlasFolder = fs::path(dest).parent_path();
    if (!fs::exists(atlasFolder))
    {
        fs::create_directories(atlasFolder);
    }

    // Run crunch packer
    const char *args[] = { "crunch", dest.c_str(), sourceFolder.c_str(),
        "-j", "-v", "-u", "-t", "-r" };
    crunch(sizeof(args) / sizeof(void *), args);
}


const char *OpenJson(std::string &path, nlohmann::json *json)
{
    std::ifstream configFile;
    configFile.open(path, std::ios::binary);
    if (!configFile.is_open())
    {
        return "failed to open file";
    }

    nlohmann::json j;
    try {
        j = nlohmann::json::parse(configFile);
    }
    catch (const nlohmann::detail::exception &e)
    {
        return e.what();
    }
    catch (...)
    {
        return "unknown error";
    }

    if (json)
        *json = std::move(j);

    return nullptr;
}

void EncryptFile(std::ifstream &inFile, std::ofstream &outFile, const std::string &key)
{
    // Encrypt file
    for (int i = 0; true; ++i)
    {
        unsigned char c = inFile.get();
        if (inFile.eof() || inFile.bad())
            break;
        unsigned char add = key[i % key.length()];
        c ^= ~add;
        c = (unsigned char)(c + add - i);
        outFile << c;
    }
}


int main(int argc, char *argv[])
{
    std::cout << "[ContentPipe] Processing assets. . .\n";
    if (argc < 5)
    {
        std::cout << "Not enough arguments provided to ContentPipe: \n";
        PrintManual();
        return 1;
    }
    
    // Get the args
    std::string assetDir = argv[1], outDir = argv[2], encryptionKey = argv[3], configPath = argv[4];
    fs::directory_entry assetFolder(outDir);

    SDG::ContentPipe::ContentCache cache;
    cache.Load(CacheFilename);

    // Open asset config
    nlohmann::json j;
    {
        const char *result = OpenJson(configPath, &j);
        if (result != 0)
        {
            std::cerr << "Failed to open or parse asset config json (" << configPath << "): " << result << '\n';
            return 1; 
        }
    }

    // For each asset in config
    for (auto &assetInfo : j)
    {
        // Get info from json
        auto type = std::string{ assetInfo.value("type", "") };
        auto path = assetInfo.value("path", "");
        auto entry = fs::directory_entry(assetDir + "/" + path);

        // Validate info
        {
            bool pathExists = fs::exists(entry.path());
            if (type.empty() || path.empty() || !pathExists)
            {
                std::cout << "Warning: skipping asset entry: \n";
                if (type.empty())
                {
                    std::cout << " (!) missing \"type\" field\n";
                    if (!path.empty())
                        std::cout << " -> contains path \"" << path << "\"\n";
                }
                if (path.empty())
                {
                    std::cout << " (!) missing \"path\" field.\n";
                    if (!type.empty())
                        std::cout << " -> contains type \"" << type << "\"\n";
                }
                if (!path.empty() && !pathExists)
                {
                    std::cout << " (!) file at path \"" << path << "\" does not exist.\n";
                }
                continue;
            }
        }

        // Perform task based on type   
        if (type == "texture-atlas") // run crunch
        {
            auto relPath = assetInfo.at("path").get<std::string>();
            CreateAtlas(assetDir + "/" + relPath, outDir + "/atlases/" + relPath);

        }
        else                         // copy as encrypted sdgc file
        {
            long long writeTime      = entry.last_write_time().time_since_epoch().count();
            std::string relativePath = entry.path().string().substr(assetDir.length());
            std::string outFilePath  = assetFolder.path().string() + relativePath;

            // Make sure folder structure exists in target destination
            {
                fs::path parent = fs::path(outFilePath).parent_path();
                if (!fs::exists(parent))
                    fs::create_directories(parent);
            }
        
            if (cache.EntryIsNewer(relativePath, writeTime)) // item is new or a newer version exists
            {
                // Copy and encrypt file to new location
                std::ifstream inFile;
                std::ofstream outFile;
                inFile.open(entry.path().string(), std::ios::binary);

                // append .sdgc to files (marks encrypted status)
                {
                    if (entry.path().has_extension())
                    {
                        size_t dotPos = outFilePath.find(entry.path().extension().string());
                        outFilePath = outFilePath.substr(0, dotPos) + ".sdgc";
                    }
                    else
                    {
                        outFilePath += ".sdgc";
                    }
                }

                // Write the new or updated file
                outFile.open(outFilePath, std::ios::trunc | std::ios::binary);
                if (!inFile.is_open())
                {
                    std::cerr << "There was a problem opening file at path: " << entry.path() << '\n';
                    continue;
                }
                if (!outFile.is_open())
                {
                    std::cerr << "There was a problem writing a file at path: " <<
                        assetFolder.path().string() + entry.path().relative_path().string() << '\n';
                    continue;
                }

                EncryptFile(inFile, outFile, encryptionKey);

                std::cout << "[ContentPipe] Encrypting file (" << relativePath.substr(1) << ")\n";
                cache[relativePath] = writeTime;
            }
        }
    }

    // Output changes to cache file
    cache.Write(CacheFilename);
    std::cout << "[ContentPipe] Done!\n";
    return 0;
}
