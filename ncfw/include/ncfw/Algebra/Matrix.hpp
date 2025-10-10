#pragma once
#include "ncfw/Algebra/Vector.hpp"

#include <assert.h>
#include <cstdint>
#include <format>
#include <stdint.h>
#include <string>
#include <type_traits>

namespace ncfw {
template <uint32_t ROWS, uint32_t COLS, typename T> struct Matrix {
  static const Matrix<ROWS, COLS, T> &identity()
    requires(ROWS == COLS)
  {
    static Matrix<ROWS, COLS, T> id = createIdentity();
    return id;
  }

  static Matrix<ROWS, COLS, T> fromRows(std::initializer_list<const Vector<COLS, T>> p_rows) {
    assert(p_rows.size() <= ROWS);
    Matrix<ROWS, COLS, T> m = {};
    uint32_t r = 0;
    for (const auto &row : p_rows) {
      for (uint32_t c = 0; c < COLS; ++c) {
        m.set(r, c, row[c]);
      }
      ++r;
    }
    return m;
  }

  static Matrix<ROWS, COLS, T> fromColumns(std::initializer_list<const Vector<ROWS, T>> p_columns) {
    return Matrix<COLS, ROWS, T>::fromRows(p_columns).transpose();
  }

#ifdef NCFW_MATRIX_COLUMN_MAJOR
  static constexpr uint32_t toRawIndex(uint32_t p_row, uint32_t p_col) { return p_col * ROWS + p_row; }
#else
  static constexpr uint32_t toRawIndex(uint32_t p_row, uint32_t p_col) { return p_row * COLS + p_col; }
#endif

  T values[ROWS * COLS];

  T &get(uint32_t p_row, uint32_t p_col) { return values[toRawIndex(p_row, p_col)]; }
  const T &get(uint32_t p_row, uint32_t p_col) const { return values[toRawIndex(p_row, p_col)]; }
  void set(uint32_t p_row, uint32_t p_col, const T &p_value) { values[toRawIndex(p_row, p_col)] = p_value; }

  Matrix<ROWS, COLS, T> inverse() const
    requires(ROWS == COLS)
  {
    T det = this->det();
    Matrix<ROWS, COLS, T> inv;
    for (uint32_t r = 0; r < ROWS; ++r) {
      for (uint32_t c = 0; c < COLS; ++c) {
        inv.set(c, r, ((r + c) % 2 == 0 ? T(1) : T(-1)) * this->minor(r, c) / det);
      }
    }
    return inv;
  }

  T det() const
    requires(ROWS == COLS)
  {
    if constexpr (ROWS == 1) {
      return this->get(0, 0);
    } else if constexpr (ROWS == 2) {
      return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);
    } else if constexpr (ROWS == 3) {
      return this->get(0, 0) * this->get(1, 1) * this->get(2, 2) + this->get(0, 1) * this->get(1, 2) * this->get(2, 0) +
             this->get(0, 2) * this->get(1, 0) * this->get(2, 1) - this->get(0, 2) * this->get(1, 1) * this->get(2, 0) -
             this->get(0, 1) * this->get(1, 0) * this->get(2, 2) - this->get(0, 0) * this->get(1, 2) * this->get(2, 1);
    } else {
      T det = (T)0;
      for (uint32_t c = 0; c < COLS; ++c) {
        det += (c % 2 == 0 ? T(1) : T(-1)) * this->get(0, c) * this->minor(0, c);
      }
      return det;
    }
  }

  T minor(uint32_t p_skipRow, uint32_t p_skipCol) const
    requires(ROWS == COLS)
  {
#define _GET(_r, _c) this->get(_r < p_skipRow ? _r : (_r + 1), _c < p_skipCol ? _c : (_c + 1))
    if constexpr (ROWS == 2) {
      return _GET(0, 0);
    } else if constexpr (ROWS == 3) {
      return _GET(0, 0) * _GET(1, 1) - _GET(0, 1) * _GET(1, 0);
    } else if constexpr (ROWS == 4) {
      return _GET(0, 0) * _GET(1, 1) * _GET(2, 2) + _GET(0, 1) * _GET(1, 2) * _GET(2, 0) +
             _GET(0, 2) * _GET(1, 0) * _GET(2, 1) - _GET(0, 2) * _GET(1, 1) * _GET(2, 0) -
             _GET(0, 1) * _GET(1, 0) * _GET(2, 2) - _GET(0, 0) * _GET(1, 2) * _GET(2, 1);
    } else {
      Matrix<ROWS - 1, COLS - 1, T> m;
      for (uint32_t r = 0; r < ROWS - 1; ++r) {
        for (uint32_t c = 0; c < COLS - 1; ++c) {
          m.set(r, c, _GET(r, c));
        }
      }
      return m.det();
    }
#undef _GET
  }

  Matrix<COLS, ROWS, T> transpose() const {
    Matrix<COLS, ROWS, T> t;
    for (uint32_t r = 0; r < ROWS; ++r) {
      for (uint32_t c = 0; c < COLS; ++c) {
        t.set(c, r, this->get(r, c));
      }
    }
    return t;
  }

  std::string toString() const {
    std::string result;
    for (uint32_t r = 0; r < ROWS; ++r) {
      for (uint32_t c = 0; c < COLS; ++c) {
        if constexpr (std::is_floating_point_v<T>) {
          result += std::format("{:+.3f}{}", this->get(r, c), c == COLS - 1 ? "" : " ");
        } else {
          result += std::format("{:5}{}", this->get(r, c), c == COLS - 1 ? "" : " ");
        }
      }
      if (r != ROWS - 1) {
        result += "\n";
      }
    }
    return result;
  }

private:
  static Matrix<ROWS, COLS, T> createIdentity()
    requires(ROWS == COLS)
  {
    Matrix<ROWS, COLS, T> id = {};
    for (uint32_t i = 0; i < ROWS; ++i) {
      id.set(i, i, (T)1);
    }
    return id;
  }
};

template <typename T> using Mat4x4 = Matrix<4, 4, T>;
template <typename T> using Mat3x4 = Matrix<3, 4, T>;
template <typename T> using Mat3x3 = Matrix<3, 3, T>;
template <typename T> using Mat2x3 = Matrix<2, 3, T>;
template <typename T> using Mat2x2 = Matrix<2, 2, T>;
typedef Mat4x4<float> Mat4x4f;
typedef Mat3x4<float> Mat3x4f;
typedef Mat3x3<float> Mat3x3f;
typedef Mat3x3<float> Mat2x3f;
typedef Mat2x2<float> Mat2x2f;

template <uint32_t R, uint32_t N, uint32_t C, typename T>
Matrix<R, C, T> operator*(const Matrix<R, N, T> &p_lhs, const Matrix<N, C, T> &p_rhs) {
  Matrix<R, C, T> result = {};
  for (uint32_t r = 0; r < R; ++r) {
    for (uint32_t c = 0; c < C; ++c) {
      for (uint32_t i = 0; i < N; ++i) {
        result.get(r, c) += p_lhs.get(r, i) * p_rhs.get(i, c);
      }
    }
  }
  return result;
}

template <uint32_t R, uint32_t C, typename T> Matrix<R, C, T> operator*(const Matrix<R, C, T> &p_lhs, const T &p_rhs) {
  Matrix<R, C, T> result = {};
  for (uint32_t r = 0; r < R; ++r) {
    for (uint32_t c = 0; c < C; ++c) {
      result.set(r, c, p_lhs.get(r, c) * p_rhs);
    }
  }
  return result;
}

template <uint32_t R, uint32_t C, typename T> Matrix<R, C, T> operator*(const T &p_lhs, const Matrix<R, C, T> &p_rhs) {
  Matrix<R, C, T> result = {};
  for (uint32_t r = 0; r < R; ++r) {
    for (uint32_t c = 0; c < C; ++c) {
      result.set(r, c, p_lhs * p_rhs.get(r, c));
    }
  }
  return result;
}

template <uint32_t R, uint32_t C, typename T> Matrix<R, C, T> operator/(const Matrix<R, C, T> &p_lhs, const T &p_rhs) {
  Matrix<R, C, T> result = {};
  for (uint32_t r = 0; r < R; ++r) {
    for (uint32_t c = 0; c < C; ++c) {
      result.set(r, c, p_lhs.get(r, c) / p_rhs);
    }
  }
  return result;
}

template <uint32_t R, uint32_t C, typename T> Matrix<R, C, T> &operator*=(Matrix<R, C, T> &p_lhs, const T &p_rhs) {
  return p_lhs = p_lhs * p_rhs;
}

template <uint32_t R, uint32_t C, typename T> Matrix<R, C, T> &operator/=(Matrix<R, C, T> &p_lhs, const T &p_rhs) {
  return p_lhs = p_lhs / p_rhs;
}

template <uint32_t R, uint32_t N, uint32_t C, typename T>
Matrix<R, C, T> &operator*=(Matrix<R, N, T> &p_lhs, const Matrix<N, C, T> &p_rhs) {
  return p_lhs = p_lhs * p_rhs;
}

template <uint32_t R, uint32_t C, typename T>
Vector<R, T> operator*(const Matrix<R, C, T> &p_lhs, const Vector<C, T> &p_rhs) {
  Matrix<R, 1, T> result = p_lhs * reinterpret_cast<const Matrix<C, 1, T> &>(p_rhs);
  return reinterpret_cast<const Vector<R, T> &>(result);
}

template <uint32_t R, uint32_t C, typename T>
Vector<C, T> operator*(const Vector<R, T> &p_lhs, const Matrix<R, C, T> &p_rhs) {
  Matrix<1, C, T> result = reinterpret_cast<const Matrix<1, R, T> &>(p_lhs) * p_rhs;
  return reinterpret_cast<const Vector<C, T> &>(result);
}
} // namespace ncfw

template <uint32_t ROWS, uint32_t COLS, typename T> struct std::formatter<ncfw::Matrix<ROWS, COLS, T>> {
  constexpr auto parse(std::format_parse_context &p_ctx) { return p_ctx.begin(); }

  auto format(const ncfw::Matrix<ROWS, COLS, T> &p_matrix, std::format_context &p_ctx) const {
    return std::format_to(p_ctx.out(), "{}", p_matrix.toString());
  }
};
