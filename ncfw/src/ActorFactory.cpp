#include "ncfw/ActorSystem/ActorFactory.hpp"

namespace ncfw {
std::unique_ptr<Actor> ActorFactory::createRootActor(const std::string &p_name) {
  return std::unique_ptr<Actor>(new Actor(this->getNextActorId(), p_name, nullptr));
}
} // namespace ncfw
