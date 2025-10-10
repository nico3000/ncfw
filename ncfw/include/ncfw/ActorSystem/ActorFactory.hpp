#pragma once
#include "ncfw/ActorSystem/Actor.hpp"
#include "ncfw/ActorSystem/ActorId.hpp"
#include "ncfw/AppModule.hpp"

#include <string>

namespace ncfw {
class ActorFactory : public AppModule {
public:
  std::unique_ptr<Actor> createRootActor(const std::string &p_name);

private:
  friend class Actor;

  uint64_t m_nextActorId = 1ull;

  ActorId getNextActorId() { return m_nextActorId++; }
};
} // namespace ncfw
