#include "ncfw/ActorSystem/ActorFactory.hpp"
#include "ncfw/Algebra/Angle.hpp"
#include "ncfw/Algebra/Matrix.hpp"
#include "ncfw/App.hpp"
#include "ncfw/EventSystem/EventManager.hpp"
#include "ncfw/ResCache/FileSystemSource.hpp"
#include "ncfw/ResCache/ResCache.hpp"

#include <lua.h>
#include <nlohmann/json.hpp>
#include <vulkan/vulkan.hpp>

#include <chrono>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace ncfw {
class TestEvent : public Event {
public:
  TestEvent(const std::string &p_text) : Event("TestEvent") { (*this)["text"] = p_text; }

  std::string getText() const { return (*this)["text"]; }
};

int32_t main(const std::vector<std::string> &p_args) {
  App app;
  auto resCache = app.createModule<ResCache>();
  resCache->pushSource(std::make_unique<FileSystemSource>("."));
  auto res = resCache->getResource(".clang-format");
  NCFW_THROW_UNLESS(res->wait(), "{}", res->getError());
  NCFW_INFO("╒══ {} ═══", res->getName());
  NCFW_INFO("{}", res->createString());
  NCFW_INFO("╘══ {} ═══", res->getName());

  NCFW_INFO("Information");
  NCFW_WARN("Warning");
  NCFW_ERROR("Error");
  NCFW_FATAL("Fatal error");

  Mat4x4f a = Mat4x4f::fromColumns({{1, 2, 3, 4}, {1, 7, 1, 2}, {3, 3, 0, 1}, {4, 5, 6, 8}});
  Mat4x4f b = a.inverse();
  NCFW_INFO("A:\n{}", a);
  NCFW_INFO("A * A^-1:\n{}", a * b);

  const uint32_t COUNT = 1000;
  std::chrono::nanoseconds nanos(0);
  for (uint32_t i = 0; i < COUNT; ++i) {
    Mat4x4f a;
    for (uint32_t r = 0; r < 4; ++r) {
      for (uint32_t c = 0; c < 4; ++c) {
        a.set(r, c, static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
      }
    }
    auto beg = std::chrono::high_resolution_clock::now();
    a.inverse();
    auto end = std::chrono::high_resolution_clock::now();
    nanos += end - beg;
  }
  NCFW_INFO("{} 4x4 matrix inversions took {} ms.", COUNT,
            std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(nanos).count());

  NCFW_INFO("{}", Angle::deg(-270.0f).rad());

  EventManager *evtMgr = app.createModule<EventManager>();
  app.getProcessManager().addProcess(evtMgr);
  evtMgr->addListener<TestEvent>([](const TestEvent &p_evt) { NCFW_INFO("Test: {}", p_evt.getText()); });
  evtMgr->pushNew<TestEvent>("foo");

  ActorFactory *actorFactory = app.createModule<ActorFactory>();
  std::unique_ptr<Actor> actor = actorFactory->createRootActor("root");

  app.discontinue();
  return app.main(p_args);
}
} // namespace ncfw

int32_t main(int32_t p_argc, char *p_argv[]) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  return ncfw::main({p_argv, p_argv + p_argc});
}