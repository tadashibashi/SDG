#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace SDG
{
	std::vector<uint8_t> encrypt(const std::string &key, const std::vector<uint8_t> &data);
	std::vector<uint8_t> decrypt(const std::string &key, const std::vector<uint8_t> &data);
}
