#include "ncfw/PropertySystem/PropertyContainer.hpp"

#include "ncfw/App.hpp"

namespace ncfw {
void PropertyContainer::setParent(const PropertyContainer *p_parent) {
  const PropertyContainer *p = m_parent;
  while (p != nullptr) {
    NCFW_THROW_IF(p == this, "Recursive property container structure.");
    p = p->m_parent;
  }
  m_parent = p_parent;
}

const PropertyProxy PropertyContainer::operator[](const std::string &p_propertyName) const {
  return PropertyProxy(*this, p_propertyName);
}

PropertyProxy PropertyContainer::operator[](const std::string &p_propertyName) {
  return PropertyProxy(*this, p_propertyName);
}

void PropertyContainer::removeProperty(const std::string &p_propertyName) {
  if (auto findIt = m_properties.find(p_propertyName); findIt != m_properties.end()) {
    m_properties.erase(findIt);
  }
}

const Property *PropertyContainer::getProperty(const std::string &p_propertyName) const {
  auto findIt = m_properties.find(p_propertyName);
  return findIt != m_properties.end() ? &findIt->second : m_parent ? m_parent->getProperty(p_propertyName) : nullptr;
}

Property *PropertyContainer::getProperty(const std::string &p_propertyName) {
  auto findIt = m_properties.find(p_propertyName);
  return findIt == m_properties.end() ? nullptr : &findIt->second;
}
} // namespace ncfw
