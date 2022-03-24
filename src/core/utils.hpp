#pragma once

#include <iostream>
#include <cstring>
#include <algorithm>

inline void ignore_chars(std::string &str, const std::string &ignore)
{
    for (unsigned int i = 0; i < ignore.length(); i++)
        str.erase(std::remove(str.begin(), str.end(), ignore[i]), str.end());
}
