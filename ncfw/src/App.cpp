#include "ncfw/App.hpp"

#include "ncfw/Logger.hpp"

#include <chrono>
#include <thread>

namespace ncfw {
App *g_app;

App::App() {
  NCFW_THROW_IF(g_app, "Only a single app instance is allowed.");
  g_app = this;
  m_logger = std::make_unique<Logger>("./ncfw.log");
  m_processManager = this->createModule<ProcessManager>();
}

App::~App() {
  NCFW_ERROR_UNLESS(g_app == this, "Global app instance pointer was modified.");
  g_app = nullptr;
}

int32_t App::main(const std::vector<std::string> &p_args) {
  try {
    this->mainLoop();
    return 0;
  } catch (const Exception &ex) {
    NCFW_FATAL("Uncaught exception. Exiting...");
    return 1;
  }
}

void App::mainLoop() {
  const std::chrono::duration<float> desiredFrameTime(1.0f / 60.0f);
  auto frameBegin = std::chrono::high_resolution_clock::now();
  while (m_continue) {
    m_processManager->update();
    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameTime = frameEnd - frameBegin;
    if (frameTime < desiredFrameTime) {
      std::this_thread::sleep_for(desiredFrameTime - frameTime);
    }
    frameBegin = frameEnd;
  }
}
} // namespace ncfw
