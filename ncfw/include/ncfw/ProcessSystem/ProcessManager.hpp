#pragma once
#include "ncfw/AppModule.hpp"

#include "ncfw/ProcessSystem/Process.hpp"

#include <vector>

namespace ncfw {
class ProcessManager : public AppModule {
public:
  void addProcess(Process *p_process) { m_processes.emplace_back(p_process); }
  void update();

private:
  std::vector<Process *> m_processes;
};
} // namespace ncfw
