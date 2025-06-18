#pragma once
#include "ncfw/AppModule.hpp"
#include "ncfw/EventSystem/Event.hpp"
#include "ncfw/EventSystem/EventListener.hpp"
#include "ncfw/EventSystem/EventListenerCallbackHandle.hpp"
#include "ncfw/EventSystem/UniversalEventListener.hpp"
#include "ncfw/EventSystem/UniversalEventListenerCallbackHandle.hpp"
#include "ncfw/ProcessSystem/Process.hpp"

#include <functional>
#include <memory>
#include <typeindex>
#include <vector>

namespace ncfw {
class EventManager : public AppModule, public Process {
public:
  typedef std::function<void(const Event &)> UniversalEventListenerCallback;
  template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
  using EventListenerCallback = std::function<void(const T &)>;

  void addListener(const std::string &p_evtName, UniversalEventListener *p_listener);
  UniversalEventListener *addListener(const std::string &p_evtName, const UniversalEventListenerCallback &p_callback);
  void removeListener(const std::string &p_evtName, UniversalEventListener *p_listener);
  Status update() override;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
  void addListener(EventListener<T> *p_listener) {
    m_listeners[typeid(T)].emplace_back(p_listener);
    this->addRefIfOwned(p_listener);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
  void removeListener(EventListener<T> *p_listener) {
    this->removeListener(typeid(T), p_listener);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
  EventListener<T> *addListener(const EventListenerCallback<T> &p_callback) {
    auto listener = std::make_unique<EventListenerCallbackHandle<T>>(p_callback);
    this->addListener(listener.get());
    return dynamic_cast<EventListener<T> *>(this->registerOwned(std::move(listener)));
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

  struct OwnedListener {
    std::unique_ptr<UniversalEventListener> listener;
    uint32_t refCount;
  };

  typedef std::vector<UniversalEventListener *> EventListeners;

  std::unordered_map<std::type_index, EventListeners> m_listeners;
  std::unordered_map<std::string, EventListeners> m_universalEventListeners;
  std::unordered_map<UniversalEventListener *, OwnedListener> m_ownedListeners;
  std::vector<EventInfo> m_eventQueues[2];
  uint32_t m_currentQueueIdx = 0;

  void removeListener(std::type_index p_typeId, UniversalEventListener *p_listener);
  UniversalEventListener *registerOwned(std::unique_ptr<UniversalEventListener> p_listener);
  void addRefIfOwned(UniversalEventListener *p_listener);
  void releaseIfOwned(UniversalEventListener *p_listener);
};
} // namespace ncfw
