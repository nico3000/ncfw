#pragma once
#include <exception>
#include <string>

namespace ncfw {
class Exception : public std::exception {
public:
  Exception(const std::string &p_what = "") : std::exception(), m_what(p_what) {}

  const char *what() const noexcept { return m_what.c_str(); }

private:
  std::string m_what;
};
} // namespace ncfw
