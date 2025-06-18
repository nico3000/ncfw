#include "ncfw/EventSystem/EventManager.hpp"

namespace ncfw {
void EventManager::addListener(const std::string &p_evtName, UniversalEventListener *p_listener) {
  m_universalEventListeners[p_evtName].emplace_back(p_listener);
}

UniversalEventListener *EventManager::addListener(const std::string &p_evtName,
                                                  const UniversalEventListenerCallback &p_callback) {
  auto listener = std::make_unique<UniversalEventListenerCallbackHandle>(p_callback);
  this->addListener(p_evtName, listener.get());
  return this->registerOwned(std::move(listener));
}

void EventManager::removeListener(const std::string &p_evtName, UniversalEventListener *p_listener) {
  if (auto it = m_universalEventListeners.find(p_evtName); it != m_universalEventListeners.end()) {
    if (auto it2 = std::find(it->second.begin(), it->second.end(), p_listener); it2 != it->second.end()) {
      it->second.erase(it2);
      if (it->second.empty()) {
        m_universalEventListeners.erase(it);
      }
    }
  }
  this->releaseIfOwned(p_listener);
}

void EventManager::removeListener(std::type_index p_typeId, UniversalEventListener *p_listener) {
  if (auto it = m_listeners.find(p_typeId); it != m_listeners.end()) {
    if (auto it2 = std::find(it->second.begin(), it->second.end(), p_listener); it2 != it->second.end()) {
      it->second.erase(it2);
    }
    if (it->second.empty()) {
      m_listeners.erase(it);
    }
  }
  this->releaseIfOwned(p_listener);
}

UniversalEventListener *EventManager::registerOwned(std::unique_ptr<UniversalEventListener> p_listener) {
  UniversalEventListener *key = p_listener.get();
  return m_ownedListeners.emplace(key, OwnedListener{.listener = std::move(p_listener), .refCount = 1}).first->first;
}

void EventManager::addRefIfOwned(UniversalEventListener *p_listener) {
  if (auto it = m_ownedListeners.find(p_listener); it != m_ownedListeners.end()) {
    ++it->second.refCount;
  }
}

void EventManager::releaseIfOwned(UniversalEventListener *p_listener) {
  if (auto it = m_ownedListeners.find(p_listener); it != m_ownedListeners.end() && --it->second.refCount == 0) {
    m_ownedListeners.erase(it);
  }
}

Process::Status EventManager::update() {
  std::vector<EventInfo> &queue = m_eventQueues[m_currentQueueIdx];
  m_currentQueueIdx = (m_currentQueueIdx + 1) % std::size(m_eventQueues);
  for (const EventInfo &evtInfo : queue) {
    if (auto it = m_listeners.find(evtInfo.evtType); it != m_listeners.end()) {
      for (auto listener : it->second) {
        listener->on(*evtInfo.evt.get());
      }
    }
    if (auto it = m_universalEventListeners.find(evtInfo.evt->getName()); it != m_universalEventListeners.end()) {
      for (auto listener : it->second) {
        listener->on(*evtInfo.evt);
      }
    }
  }
  queue.clear();
  return Process::Status::eContinue;
}
} // namespace ncfw
