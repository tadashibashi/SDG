#include "Crypto.h"

std::vector<uint8_t> 
SDG::Encrypt(const std::string &key, const std::vector<uint8_t> &data)
{
    std::vector<uint8_t> ret;
    ret.reserve(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        auto c = (uint8_t)key[i % key.size()];
        ret.push_back(c + data[i] - i);
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
        auto c = (uint8_t)key[i % key.size()];
        ret.push_back(data[i] - c + i);
    }

    return ret;
}
