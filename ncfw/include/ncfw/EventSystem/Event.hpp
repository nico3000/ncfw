#pragma once
#include "ncfw/PropertySystem/PropertyContainer.hpp"

namespace ncfw {
class Event : public PropertyContainer {
public:
  Event(const std::string &p_name) : m_eventName(p_name) {}
  virtual ~Event() = default;

  const std::string &getName() const { return m_eventName; }

private:
  std::string m_eventName;
};
} // namespace ncfw
