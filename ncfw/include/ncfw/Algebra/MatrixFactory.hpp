#pragma once
#include "ncfw/Algebra/Angle.hpp"
#include "ncfw/Algebra/Matrix.hpp"
#include "ncfw/Algebra/Vector.hpp"

namespace ncfw {
namespace MatrixFactory {
static Mat4x4f createTranslation3D(float p_x, float p_y, float p_z) {
  Mat4x4f t = Mat4x4f::identity();
  t.set(0, 3, p_x);
  t.set(1, 3, p_y);
  t.set(2, 3, p_z);
  return t;
}

static Mat4x4f createScaling3D(float p_x, float p_y, float p_z) {
  Mat4x4f s = Mat4x4f::identity();
  s.set(0, 0, p_x);
  s.set(1, 1, p_y);
  s.set(2, 2, p_z);
  return s;
}

static Mat4x4f createRotation3DX(Angle p_angle) {
  Mat4x4f r = Mat4x4f::identity();
  r.set(1, 1, p_angle.cos());
  r.set(1, 2, -p_angle.sin());
  r.set(2, 1, p_angle.sin());
  r.set(2, 2, p_angle.cos());
  return r;
}

static Mat4x4f createRotation3DY(Angle p_angle) {
  Mat4x4f r = Mat4x4f::identity();
  r.set(0, 0, p_angle.cos());
  r.set(0, 2, p_angle.sin());
  r.set(2, 0, -p_angle.sin());
  r.set(2, 2, p_angle.cos());
  return r;
}

static Mat4x4f createRotation3DZ(Angle p_angle) {
  Mat4x4f r = Mat4x4f::identity();
  r.set(0, 0, p_angle.cos());
  r.set(0, 1, -p_angle.sin());
  r.set(1, 0, p_angle.sin());
  r.set(1, 1, p_angle.cos());
  return r;
}

static Mat4x4f createRotation3D(Angle p_pitch, Angle p_yaw, Angle p_roll) {
  return createRotation3DY(p_yaw) * createRotation3DX(p_pitch) * createRotation3DZ(p_roll);
}

static Vec3f transformPoint(const Mat4x4f &p_lhs, const Vec3f &p_point) {
  Vec4f p = p_lhs * Vec4f{.x = p_point.x, .y = p_point.y, .z = p_point.z, .w = 1.0f};
  return {.x = p.x / p.w, .y = p.y / p.w, .z = p.z / p.w};
}

static Vec3f transformDirection(const Mat4x4f &p_lhs, const Vec3f &p_dir) {
  return {p_lhs.get(0, 0) * p_dir.x + p_lhs.get(0, 1) * p_dir.y + p_lhs.get(0, 2) * p_dir.z,
          p_lhs.get(1, 0) * p_dir.x + p_lhs.get(1, 1) * p_dir.y + p_lhs.get(1, 2) * p_dir.z,
          p_lhs.get(2, 0) * p_dir.x + p_lhs.get(2, 1) * p_dir.y + p_lhs.get(2, 2) * p_dir.z};
}

static Vec3f transformNormal(const Mat4x4f &p_lhs, const Vec3f &p_normal) {
  return transformDirection(p_lhs.transpose().inverse(), p_normal);
}
} // namespace MatrixFactory
} // namespace ncfw
