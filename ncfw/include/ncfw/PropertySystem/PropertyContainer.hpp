#pragma once
#include "ncfw/PropertySystem/Property.hpp"
#include "ncfw/PropertySystem/PropertyProxy.hpp"

#include <unordered_map>

namespace ncfw {
class PropertyContainer {
public:
  PropertyProxy operator[](const std::string &p_propertyName);
  const PropertyProxy operator[](const std::string &p_propertyName) const;

  Property &getOrCreateProperty(const std::string &p_propertyName) { return m_properties[p_propertyName]; }
  void removeProperty(const std::string &p_propertyName);
  const Property *getProperty(const std::string &p_propertyName) const;
  Property *getProperty(const std::string &p_propertyName);

private:
  std::unordered_map<std::string, Property> m_properties;
};
} // namespace ncfw
