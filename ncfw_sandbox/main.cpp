#include "ncfw/App.hpp"
#include "ncfw/EventSystem/EventManager.hpp"
#include "ncfw/PropertySystem/PropertyContainer.hpp"

using namespace ncfw;
class TestEvent : public Event {
public:
  TestEvent() : Event("TestEvent") {}

  const std::string &foo() const { return m_test; }

private:
  std::string m_test = "test";
};

class TestEventListener : public EventListener<TestEvent> {
public:
  void on(const TestEvent &p_evt) override { NCFW_INFO("Triggered: {}", p_evt.foo()); }
};

int32_t main(int32_t p_argc, char *p_argv[]) {
  ncfw::App app;

  NCFW_INFO("Hello {}", "world");
  NCFW_WARN("Hello {}", "world");
  NCFW_ERROR("Hello {}", "world");
  NCFW_FATAL("Hello {}", "world");
  // NCFW_ASSERT(false, "Hello {}", "world");

  PropertyContainer pc1;
  const PropertyContainer pc2;
  pc1["test"] = "test";
  NCFW_INFO("test: {}", pc1["test"].asString());

  EventManager *evtMgr = app.createModule<EventManager>();
  app.getProcessManager().addProcess(evtMgr);
  TestEventListener tel;
  evtMgr->addListener(&tel);
  evtMgr->pushNew<TestEvent>();

  return app.main({p_argv, p_argv + p_argc});
}