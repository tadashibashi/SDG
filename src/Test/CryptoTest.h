#pragma once
#include <SDG/Crypto.h>
#include <SDG/XMLReader.h>
#include <SDG/FileSys.h>
#include <SDG/Logging.h>

#include <iostream>

void CryptoTest()
{
    auto efile = SDG::Encrypt("ghipwet",
                              {'f', 'o', 'r', ' ', 'G', 'o', 'd', ' ', 's', 'o', ' ', 'l', 'o', 'v', 'e', 'd', ' ',
                               't', 'h', 'e', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 't', 'h', 'a', 't'});
    std::cout << "Encrypted: \"";
    for (auto e : efile)
    {
        std::cout << e;
    }
    std::cout << "\"\n";

    auto dfile = SDG::Decrypt("ghipwet", efile);
    std::cout << "Decrypted: \"";
    for (auto d : dfile)
    {
        std::cout << d;
    }
    std::cout << "\"\n";
}
