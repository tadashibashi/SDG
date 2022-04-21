#include "Crypto.h"

std::vector<uint8_t> 
SDG::Encrypt(const std::string &key, const std::vector<uint8_t> &data)
{
    std::vector<uint8_t> ret;
    ret.reserve(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        auto add = (uint8_t)key[i % key.size()];
        uint8_t c = data[i];
        c ^= ~add;
        c = add + c - i;
        ret.push_back(c);
    }

    return ret;
}


std::vector<uint8_t> 
SDG::Decrypt(const std::string &key, const std::vector<uint8_t> &data)
{
    std::vector<uint8_t> ret;
    ret.reserve(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        auto add = (uint8_t)key[i % key.size()];
        uint8_t c = data[i];
        c = c - add + i;
        c ^= ~add;
        ret.push_back(c);
    }

    return ret;
}
