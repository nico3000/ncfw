#pragma once
#include <string>

namespace ncfw {
class PropertyContainer;

class PropertyProxy {
public:
  PropertyProxy(PropertyContainer &p_propertyContainer, const std::string &p_propertyName);
  PropertyProxy(const PropertyContainer &p_propertyContainer, const std::string &p_propertyName);

  operator int64_t() const { return this->asInt(); }
  operator uint64_t() const { return this->asUint(); }
  operator double() const { return this->asDouble(); }
  operator std::string() const { return this->asString(); }

  int64_t asInt() const;
  uint64_t asUint() const;
  double asDouble() const;
  std::string asString() const;

  nullptr_t operator=(nullptr_t p_value);
  int64_t operator=(int64_t p_value);
  uint64_t operator=(uint64_t p_value);
  double operator=(double p_value);
  const std::string &operator=(const std::string &p_value);

  template <typename T> std::enable_if_t<!std::is_floating_point_v<T> && std::is_signed_v<T>, T> operator=(T p_value) {
    this->operator=(static_cast<int64_t>(p_value));
    return p_value;
  }

  template <typename T> std::enable_if_t<std::is_unsigned_v<T>, T> operator=(T p_value) {
    this->operator=(static_cast<uint64_t>(p_value));
    return p_value;
  }

  template <typename T> std::enable_if_t<std::is_floating_point_v<T>, T> operator=(T p_value) {
    this->operator=(static_cast<double>(p_value));
    return p_value;
  }

  PropertyProxy(PropertyProxy &) = delete;
  PropertyProxy(PropertyProxy &&) = delete;
  PropertyProxy &operator=(PropertyProxy &) = delete;
  PropertyProxy &operator=(PropertyProxy &&) = delete;

private:
  PropertyContainer *m_propertyContainer;
  const PropertyContainer &m_constPropertyContainer;
  std::string m_propertyName;
};
} // namespace ncfw
