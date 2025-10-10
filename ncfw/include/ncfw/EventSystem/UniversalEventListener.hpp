#pragma once
#include "ncfw/EventSystem/Event.hpp"

namespace ncfw {
class UniversalEventListener {
public:
  virtual ~UniversalEventListener() = default;

  virtual void on(const Event &p_evt) = 0;
};
} // namespace ncfw
