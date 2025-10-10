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

template <typename T>
concept ExplicitEvent = std::is_base_of_v<Event, T>;
} // namespace ncfw
