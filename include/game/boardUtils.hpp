#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include <string>
#include <vector>

namespace BoardUtils
{
std::vector<std::vector<char>>
stringVectorToCharVector(const std::vector<std::string>& stringVector);

extern std::vector<std::string> maze;
} // namespace BoardUtils

#endif
