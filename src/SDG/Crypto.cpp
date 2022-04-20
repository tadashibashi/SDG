#include "Crypto.h"

std::vector<uint8_t> 
SDG::encrypt(const std::string &key, const std::vector<uint8_t> &data)
{
    std::vector<uint8_t> ret;
    ret.reserve(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        uint8_t c = (uint8_t)key[i % key.size()];
        ret.push_back(c + data[i]);
    }

    return ret;
}


std::vector<uint8_t> 
SDG::decrypt(const std::string &key, const std::vector<uint8_t> &data)
{
    std::vector<uint8_t> ret;
    ret.reserve(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        uint8_t c = (uint8_t)key[i % key.size()];
        ret.push_back(data[i] - c);
    }

    return ret;
}
