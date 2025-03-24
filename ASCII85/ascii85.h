#ifndef ASCII85_H
#define ASCII85_H

#include <iostream>
#include <cstdint>
#include <cctype>
#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <algorithm>

std::string encode_bytes(const std::vector<std::uint8_t>& bytes);
std::string ascii85_encode(const std::vector<std::uint8_t>& data);
std::vector<std::uint8_t> decode_bytes(const std::string& bytes);
std::vector<std::uint8_t> ascii85_decode(const std::string& encoded);


#endif
