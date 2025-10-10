#pragma once
#include "ncfw/EventSystem/EventListener.hpp"

#include <functional>

namespace ncfw {
template <ExplicitEvent E> class EventListenerCallbackHandle : public EventListener<E> {
public:
  EventListenerCallbackHandle(const std::function<void(const E &)> &p_callback) : m_callback(p_callback) {}

  void on(const E &p_evt) override { m_callback(p_evt); }

private:
  std::function<void(const E &)> m_callback;
};
} // namespace ncfw
