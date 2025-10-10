#pragma once
#include <cmath>
#include <format>
#include <stdexcept>
#include <type_traits>

namespace ncfw {
template <uint32_t N, typename T> struct Vector {
  T values[N];

  const T &operator[](uint32_t p_idx) const { return values[p_idx]; }
  T &operator[](uint32_t p_idx) { return values[p_idx]; }

  T dot(const Vector<N, T> &p_other) const {
    T dot = (T)0;
    for (uint32_t i = 0; i < N; ++i) {
      dot += values[i] * p_other.values[i];
    }
    return dot;
  }

  float length() const
    requires(std::is_same_v<T, float>)
  {
    return std::sqrt(this->dot(*this));
  }

  double length() const
    requires(!std::is_same_v<T, float>)
  {
    return std::sqrt(static_cast<double>(this->dot(*this)));
  }
};

template <typename T> using Vec4 = Vector<4, T>;
template <typename T> using Vec3 = Vector<3, T>;
template <typename T> using Vec2 = Vector<2, T>;

typedef Vec4<float> Vec2f;
typedef Vec4<float> Vec3f;
typedef Vec4<float> Vec4f;

template <typename T> struct Vector<2, T> {
  T x;
  T y;

  const T &operator[](uint32_t p_idx) const {
    switch (p_idx) {
    case 0: return x;
    case 1: return y;
    default: throw std::out_of_range(std::format("Index out of range: {}", p_idx));
    };
  }

  T &operator[](uint32_t p_idx) {
    switch (p_idx) {
    case 0: return x;
    case 1: return y;
    default: throw std::out_of_range(std::format("Index out of range: {}", p_idx));
    };
  }

  T dot(const Vec2<T> &p_other) const { return x * p_other.x + y * p_other.y; }

  float length() const
    requires(std::is_same_v<T, float>)
  {
    return std::sqrt(this->dot(*this));
  }

  double length() const
    requires(!std::is_same_v<T, float>)
  {
    return std::sqrt(static_cast<double>(this->dot(*this)));
  }
};

template <typename T> struct Vector<3, T> {
  T x;
  T y;
  T z;

  const T &operator[](uint32_t p_idx) const {
    switch (p_idx) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range(std::format("Index out of range: {}", p_idx));
    };
  }

  T &operator[](uint32_t p_idx) {
    switch (p_idx) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range(std::format("Index out of range: {}", p_idx));
    };
  }

  Vec3<T> cross(const Vec3<T> &p_rhs) const {
    return {.x = y * p_rhs.z - z * p_rhs.y, .y = z * p_rhs.x - x * p_rhs.z, .z = x * p_rhs.y - y * p_rhs.x};
  }

  T dot(const Vec3<T> &p_other) const { return x * p_other.x + y * p_other.y + z * p_other.z; }

  float length() const
    requires(std::is_same_v<T, float>)
  {
    return std::sqrt(this->dot(*this));
  }

  double length() const
    requires(!std::is_same_v<T, float>)
  {
    return std::sqrt(static_cast<double>(this->dot(*this)));
  }
};

template <typename T> struct Vector<4, T> {
  T x;
  T y;
  T z;
  T w;

  const T &operator[](uint32_t p_idx) const {
    switch (p_idx) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default: throw std::out_of_range(std::format("Index out of range: {}", p_idx));
    };
  }

  T &operator[](uint32_t p_idx) {
    switch (p_idx) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default: throw std::out_of_range(std::format("Index out of range: {}", p_idx));
    };
  }

  T dot(const Vec4<T> &p_other) const { return x * p_other.x + y * p_other.y + z * p_other.z + w * p_other.w; }

  float length() const
    requires(std::is_same_v<T, float>)
  {
    return std::sqrt(this->dot(*this));
  }

  double length() const
    requires(!std::is_same_v<T, float> && std::is_convertible_v<T, double>)
  {
    return std::sqrt(static_cast<double>(this->dot(*this)));
  }
};
} // namespace ncfw
