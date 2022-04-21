#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace SDG
{
	std::vector<uint8_t> Encrypt(const std::string &key, const std::vector<uint8_t> &data);
	std::vector<uint8_t> Decrypt(const std::string &key, const std::vector<uint8_t> &data);
}
