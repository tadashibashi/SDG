#pragma once
#include <SDG/Crypto.h>
#include <iostream>

void CryptoTest()
{
    auto efile = SDG::encrypt("Yimamalama", { 'a', 'b', 'e', ' ', 'l', 'i', 'n', 'c', 'o', 'l', 'n'});
    std::cout << "Encrypted: \"";
    for (auto e : efile)
    {
        std::cout << e;
    }
    std::cout << "\"\n";

    auto dfile = SDG::decrypt("Yomamalama", efile);
    std::cout << "Decrypted: \"";
    for (auto d : dfile)
    {
        std::cout << d;
    }
    std::cout << "\"\n";

}
