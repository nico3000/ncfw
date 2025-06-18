#pragma once
#include <stdint.h>

namespace ncfw {
class ActorId {
public:
  bool operator==(const ActorId &p_other) const { return m_id == p_other.m_id; }

private:
  friend class ActorFactory;

  ActorId(uint64_t p_id) : m_id(p_id) {}

  uint64_t m_id;
};
} // namespace ncfw
