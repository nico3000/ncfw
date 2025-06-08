#pragma once
#include <exception>
#include <string>

namespace ncfw {
class Exception : public std::exception {
public:
  Exception(const std::string &p_what = "") : std::exception(p_what.c_str()) {}
};
} // namespace ncfw
