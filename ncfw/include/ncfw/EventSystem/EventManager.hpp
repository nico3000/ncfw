#pragma once
#include "ncfw/AppModule.hpp"
#include "ncfw/EventSystem/Event.hpp"
#include "ncfw/EventSystem/EventListener.hpp"
#include "ncfw/ProcessSystem/Process.hpp"

#include <memory>
#include <typeindex>
#include <vector>

namespace ncfw {
class EventManager : public AppModule, public Process {
public:
  Status update() override;

  template <typename T> void addListener(EventListener<T> *p_listener) {
    m_listeners[typeid(T)].emplace_back(p_listener);
  }

  template <typename T> void removeListener(EventListener<T> *p_listener) {
    this->removeListener(typeid(T), p_listener);
  }

  template <typename T, typename... Args> std::enable_if_t<std::is_base_of_v<Event, T>, void> pushNew(Args... p_args) {
    EventInfo evtInfo = {.evtType = typeid(T), .evt = std::make_unique<T>(p_args...)};
    m_eventQueues[m_currentQueueIdx].emplace_back(std::move(evtInfo));
  }

private:
  struct EventInfo {
    std::type_index evtType;
    std::unique_ptr<Event> evt;
  };

  typedef std::vector<GeneralEventListener *> EventListeners;

  std::unordered_map<std::type_index, EventListeners> m_listeners;
  std::vector<EventInfo> m_eventQueues[2];
  uint32_t m_currentQueueIdx = 0;

  void removeListener(std::type_index p_typeId, GeneralEventListener *p_listener);
};
} // namespace ncfw
