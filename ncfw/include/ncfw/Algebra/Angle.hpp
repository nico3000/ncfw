#pragma once
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>

namespace ncfw {
class Angle {
public:
  static Angle rad(float p_radians) { return {p_radians}; }
  static Angle deg(float p_degrees) { return {(float)M_PI * p_degrees / 180.0f}; }

  float rad() const { return m_rad; }
  float deg() const { return 180.0f * m_rad / (float)M_PI; }
  float sin() const { return std::sinf(m_rad); }
  float cos() const { return std::cosf(m_rad); }
  float tan() const { return std::tanf(m_rad); }

  Angle operator+(const Angle &p_rhs) const { return {m_rad + p_rhs.m_rad}; }
  Angle operator-(const Angle &p_rhs) const { return {m_rad - p_rhs.m_rad}; }
  Angle operator*(float p_factor) const { return {m_rad * p_factor}; }
  Angle operator/(float p_divisor) const { return {m_rad * p_divisor}; }
  Angle &operator+=(const Angle &p_rhs) { return *this = *this + p_rhs; }
  Angle &operator-=(const Angle &p_rhs) { return *this = *this + p_rhs; }
  Angle &operator*=(float p_factor) { return *this = *this * p_factor; }
  Angle &operator/=(float p_divisor) { return *this = *this / p_divisor; }

private:
  float m_rad;

  Angle(float p_rad) : m_rad(p_rad - 2.0f * M_PI * std::floorf(p_rad / (2.0f * M_PI))) {}
};

inline Angle operator*(float p_lhs, const Angle &p_rhs) { return Angle::rad(p_lhs * p_rhs.rad()); }
} // namespace ncfw