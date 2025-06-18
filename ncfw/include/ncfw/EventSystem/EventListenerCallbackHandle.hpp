#pragma once
#include "ncfw/EventSystem/EventListener.hpp"

#include <functional>

namespace ncfw {
template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
class EventListenerCallbackHandle : public EventListener<T> {
public:
  EventListenerCallbackHandle(const std::function<void(const T &)> &p_callback) : m_callback(p_callback) {}

  void on(const T &p_evt) override { m_callback(p_evt); }

private:
  std::function<void(const T &)> m_callback;
};
} // namespace ncfw
