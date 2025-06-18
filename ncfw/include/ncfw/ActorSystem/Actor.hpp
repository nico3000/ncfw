#pragma once
#include "ncfw/ActorSystem/ActorId.hpp"
#include "ncfw/PropertySystem/PropertyContainer.hpp"

#include <memory>

namespace ncfw {
class Actor {
public:
  Actor(Actor &) = delete;
  Actor &operator=(Actor &) = delete;

  const std::string &getName() const { return m_name; }
  PropertyContainer &props() { return m_props; }
  const PropertyContainer &props() const { return m_props; }
  Actor *createChild(const std::string &p_name);

private:
  friend class ActorFactory;

  Actor(ActorId p_id, const std::string &p_name, Actor *p_parent);

  ActorId m_id;
  std::string m_name;
  Actor *m_parent;
  std::unordered_map<std::string, std::unique_ptr<Actor>> m_children;
  PropertyContainer m_props;
};
} // namespace ncfw
