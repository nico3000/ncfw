
#include "ncfw/ProcessSystem/ProcessManager.hpp"

namespace ncfw {
void ProcessManager::update() {
  auto it = m_processes.begin();
  while (it != m_processes.end()) {
    if ((*it)->update() != Process::Status::eContinue) {
      it = m_processes.erase(it);
    } else {
      ++it;
    }
  }
}
} // namespace ncfw
