#include "ncfw/PropertySystem/Property.hpp"

#include "ncfw/App.hpp"

#include <stdexcept>

namespace ncfw {
void Property::setNil() {
  m_type = Type::eNil;
  m_intValue = 0;
  m_uintValue = 0;
  m_doubleValue = 0.0;
  m_stringValue.clear();
}

void Property::set(int64_t p_value) {
  m_type = Type::eInt;
  m_intValue = p_value;
  m_doubleValue = 0.0;
  m_stringValue.clear();
}

void Property::set(uint64_t p_value) {
  m_type = Type::eUint;
  m_intValue = 0;
  m_uintValue = p_value;
  m_doubleValue = 0.0;
  m_stringValue.clear();
}

void Property::set(double p_value) {
  m_type = Type::eDouble;
  m_intValue = 0;
  m_uintValue = 0;
  m_doubleValue = p_value;
  m_stringValue.clear();
}

void Property::set(const std::string p_value) {
  m_type = Type::eString;
  m_intValue = 0;
  m_uintValue = 0;
  m_doubleValue = 0.0;
  m_stringValue = p_value;
}

int64_t Property::asInt() const {
  switch (m_type) {
  case Type::eNil: return 0;
  case Type::eInt: return m_intValue;
  case Type::eUint: return static_cast<int64_t>(m_uintValue);
  case Type::eDouble: return static_cast<int64_t>(m_doubleValue);
  case Type::eString: try { return std::stoll(m_stringValue);
    } catch (const std::invalid_argument &ex) {
      NCFW_WARN("String {} could not be converted to int64_t.", m_stringValue);
      return 0;
    }
  default: NCFW_THROW_IF(true, "unreachable");
  }
}

uint64_t Property::asUint() const {
  switch (m_type) {
  case Type::eNil: return 0;
  case Type::eInt: return static_cast<uint64_t>(m_intValue);
  case Type::eUint: return m_uintValue;
  case Type::eDouble: return static_cast<uint64_t>(m_doubleValue);
  case Type::eString: try { return std::stoull(m_stringValue);
    } catch (const std::invalid_argument &ex) {
      NCFW_WARN("String {} could not be converted to uint64_t.", m_stringValue);
      return 0;
    }
  default: NCFW_THROW_IF(true, "unreachable");
  }
}

double Property::asDouble() const {
  switch (m_type) {
  case Type::eNil: return 0;
  case Type::eInt: return static_cast<double>(m_intValue);
  case Type::eUint: return static_cast<double>(m_uintValue);
  case Type::eDouble: return m_doubleValue;
  case Type::eString: try { return std::stod(m_stringValue);
    } catch (const std::invalid_argument &ex) {
      NCFW_WARN("String {} could not be converted to double.", m_stringValue);
      return 0.0;
    }
  default: NCFW_THROW_IF(true, "unreachable");
  }
}

std::string Property::asString() const {
  switch (m_type) {
  case Type::eNil: return "";
  case Type::eInt: return std::to_string(m_intValue);
  case Type::eUint: return std::to_string(m_uintValue);
  case Type::eDouble: return std::to_string(m_doubleValue);
  case Type::eString: return m_stringValue;
  default: NCFW_THROW_IF(true, "unreachable");
  }
}

} // namespace ncfw
