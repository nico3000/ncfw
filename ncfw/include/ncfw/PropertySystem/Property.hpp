#pragma once
#include <string>

namespace ncfw {
class Property {
public:
  Property() : m_type(Type::eNil) {}
  Property(const std::string &p_value) : m_type(Type::eString), m_stringValue(p_value) {}
  Property(int64_t p_value) : m_type(Type::eInt), m_intValue(p_value) {}
  Property(uint64_t p_value) : m_type(Type::eUint), m_uintValue(p_value) {}
  Property(double p_value) : m_type(Type::eDouble), m_doubleValue(p_value) {}

  void setNil();
  void set(nullptr_t p_value) { this->setNil(); }
  void set(int64_t p_value);
  void set(uint64_t p_value);
  void set(double p_value);
  void set(const std::string p_value);

  bool isNil() const { return m_type == Type::eNil; }
  int64_t asInt() const;
  uint64_t asUint() const;
  double asDouble() const;
  std::string asString() const;

private:
  enum class Type { eNil, eInt, eUint, eDouble, eString };

  Type m_type;
  int64_t m_intValue;
  uint64_t m_uintValue;
  double m_doubleValue;
  std::string m_stringValue;
};
} // namespace ncfw
