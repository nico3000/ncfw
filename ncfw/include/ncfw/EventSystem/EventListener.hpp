#pragma once
#include "ncfw/EventSystem/Event.hpp"

namespace ncfw {
class GeneralEventListener {
public:
  virtual void on(const Event &p_evt) = 0;
};

template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
class EventListener : public GeneralEventListener {
public:
  void on(const Event &p_evt) override { this->on(*dynamic_cast<const T *>(&p_evt)); }

  virtual void on(const T &p_evt) = 0;
};
} // namespace ncfw
