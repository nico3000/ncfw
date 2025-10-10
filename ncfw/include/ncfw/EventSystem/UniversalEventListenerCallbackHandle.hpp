#pragma once
#include "ncfw/EventSystem/UniversalEventListener.hpp"

#include <functional>

namespace ncfw {
class UniversalEventListenerCallbackHandle : public UniversalEventListener {
public:
  UniversalEventListenerCallbackHandle(const std::function<void(const Event &)> &p_callback) : m_callback(p_callback) {}

  void on(const Event &p_evt) override { m_callback(p_evt); }

private:
  std::function<void(const Event &)> m_callback;
};
} // namespace ncfw
