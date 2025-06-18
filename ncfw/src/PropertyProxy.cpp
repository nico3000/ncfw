#pragma once
#include "ncfw/PropertySystem/PropertyProxy.hpp"

#include "ncfw/App.hpp"
#include "ncfw/PropertySystem/PropertyContainer.hpp"

namespace ncfw {
PropertyProxy::PropertyProxy(PropertyContainer &p_propertyContainer, const std::string &p_propertyName)
    : m_propertyContainer(&p_propertyContainer), m_constPropertyContainer(p_propertyContainer),
      m_propertyName(p_propertyName) {}

PropertyProxy::PropertyProxy(const PropertyContainer &p_propertyContainer, const std::string &p_propertyName)
    : m_propertyContainer(nullptr), m_constPropertyContainer(p_propertyContainer), m_propertyName(p_propertyName) {}

nullptr_t PropertyProxy::operator=(nullptr_t p_value) {
  m_propertyContainer->getOrCreateProperty(m_propertyName).setNil();
  return p_value;
}

int64_t PropertyProxy::operator=(int64_t p_value) {
  m_propertyContainer->getOrCreateProperty(m_propertyName).set(p_value);
  return p_value;
}

uint64_t PropertyProxy::operator=(uint64_t p_value) {
  m_propertyContainer->getOrCreateProperty(m_propertyName).set(p_value);
  return p_value;
}

double PropertyProxy::operator=(double p_value) {
  m_propertyContainer->getOrCreateProperty(m_propertyName).set(p_value);
  return p_value;
}

const std::string &PropertyProxy::operator=(const std::string &p_value) {
  m_propertyContainer->getOrCreateProperty(m_propertyName).set(p_value);
  return p_value;
}

int64_t PropertyProxy::asInt() const {
  const Property *p = m_constPropertyContainer.getProperty(m_propertyName);
  if (!p) {
    NCFW_WARN("Nil property {} converted to int64_t 0.", m_propertyName);
    return 0;
  }
  return p->asInt();
}

uint64_t PropertyProxy::asUint() const {
  const Property *p = m_constPropertyContainer.getProperty(m_propertyName);
  if (!p || p->isNil()) {
    NCFW_WARN("Nil property {} converted to uint64_t 0.", m_propertyName);
    return 0;
  }
  return p->asUint();
}

double PropertyProxy::asDouble() const {
  const Property *p = m_constPropertyContainer.getProperty(m_propertyName);
  if (!p || p->isNil()) {
    NCFW_WARN("Nil property {} converted to double 0.", m_propertyName);
    return 0.0;
  }
  return p->asDouble();
}

std::string PropertyProxy::asString() const {
  const Property *p = m_constPropertyContainer.getProperty(m_propertyName);
  if (!p || p->isNil()) {
    NCFW_WARN("Nil property {} converted to empty string.", m_propertyName);
    return "";
  }
  return p->asString();
}
} // namespace ncfw
