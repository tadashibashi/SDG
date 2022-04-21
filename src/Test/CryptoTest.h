#pragma once
#include <SDG/Crypto.h>
#include <SDG/XMLReader.h>
#include <SDG/FileSys.h>
#include <SDG/Logging.h>

#include <iostream>

void CryptoTest()
{
    auto efile = SDG::Encrypt("ghipwetvsadhhhhh127aghawy239gfhahj4",
                              {'a', 'b', 'e', ' ', 'l', 'i', 'n', 'c', 'o', 'l', 'n', ' ', 'w', 'a', 's', ' ', 't', 'h',
                               'e', ' ', 's', 'i', 'x', 't', 'e', 'e', 'n', 't', 'h', ' ', 'p'});
    std::cout << "Encrypted: \"";
    for (auto e : efile)
    {
        std::cout << e;
    }
    std::cout << "\"\n";

    auto dfile = SDG::Decrypt("ghipwetvsadhhhhh127aghawy239gfhahj4", efile);
    std::cout << "Decrypted: \"";
    for (auto d : dfile)
    {
        std::cout << d;
    }
    std::cout << "\"\n";

    SDG::RWopsMem io = SDG::FileSys::DecryptFile("assets/config");
    SDG_Log("memory: {}", io.memory);
    io.Free();

    std::string title;
    int width, height;
    bool fullscreen;

    //SDG::XMLReader::ParseGameConfig("assets/config", &title, &width, &height, &fullscreen);
    //SDG_Log("results: title {} width {} height {} fullscreen {}", title, width, height, fullscreen);
}
