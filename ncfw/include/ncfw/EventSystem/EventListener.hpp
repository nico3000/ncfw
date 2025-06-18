#pragma once
#include "ncfw/EventSystem/UniversalEventListener.hpp"

namespace ncfw {
template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
class EventListener : public UniversalEventListener {
public:
  void on(const Event &p_evt) override { this->on(*dynamic_cast<const T *>(&p_evt)); }

  virtual void on(const T &p_evt) = 0;
};
} // namespace ncfw
