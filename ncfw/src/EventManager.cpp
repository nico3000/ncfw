#include "ncfw/EventSystem/EventManager.hpp"

namespace ncfw {
Process::Status EventManager::update() {
  std::vector<EventInfo> &queue = m_eventQueues[m_currentQueueIdx];
  m_currentQueueIdx = (m_currentQueueIdx + 1) % std::size(m_eventQueues);
  for (const EventInfo &evtInfo : queue) {
    if (auto listenersIt = m_listeners.find(evtInfo.evtType); listenersIt != m_listeners.end()) {
      for (auto listener : listenersIt->second) {
        listener->on(*evtInfo.evt.get());
      }
    }
  }
  queue.clear();
  return Process::Status::eContinue;
}

void EventManager::removeListener(std::type_index p_typeId, GeneralEventListener *p_listener) {
  if (auto it = m_listeners.find(p_typeId); it != m_listeners.end()) {
    if (auto it2 = std::find(it->second.begin(), it->second.end(), p_listener); it2 != it->second.end()) {
      it->second.erase(it2);
    }
    if (it->second.empty()) {
      m_listeners.erase(it);
    }
  }
}
} // namespace ncfw
