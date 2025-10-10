#pragma once
#include "ncfw/EventSystem/UniversalEventListener.hpp"

namespace ncfw {
template <ExplicitEvent E> class EventListener : public UniversalEventListener {
public:
  void on(const Event &p_evt) override { this->on(dynamic_cast<const E &>(p_evt)); }

  virtual void on(const E &p_evt) = 0;
};
} // namespace ncfw
