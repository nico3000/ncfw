#include "ncfw/ActorSystem/Actor.hpp"

#include "ncfw/ActorSystem/ActorFactory.hpp"
#include "ncfw/App.hpp"

namespace ncfw {
Actor::Actor(ActorId p_id, const std::string &p_name, Actor *p_parent)
    : m_id(p_id), m_name(p_name), m_parent(p_parent) {
  if (m_parent) {
    m_props.setParent(&m_parent->props());
  }
}

Actor *Actor::createChild(const std::string &p_name) {
  NCFW_THROW_IF(m_children.find(p_name) != m_children.end(), "Actor {} already has child actor with name {}.", m_name,
                p_name);
  return m_children.emplace(p_name, new Actor(g_app->getModule<ActorFactory>()->getNextActorId(), p_name, this))
      .first->second.get();
}
} // namespace ncfw
