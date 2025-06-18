#include "ncfw/ActorSystem/ActorFactory.hpp"
#include "ncfw/App.hpp"
#include "ncfw/EventSystem/EventManager.hpp"

using namespace ncfw;
class TestEvent : public Event {
public:
  TestEvent(const std::string &p_text) : Event("TestEvent") { (*this)["text"] = p_text; }

  std::string getText() const { return (*this)["text"]; }
};

int32_t main(int32_t p_argc, char *p_argv[]) {
  ncfw::App app;

  NCFW_INFO("Hello {}", "world");
  NCFW_WARN("Hello {}", "world");
  NCFW_ERROR("Hello {}", "world");
  NCFW_FATAL("Hello {}", "world");
  // NCFW_ASSERT(false, "Hello {}", "world");

  EventManager *evtMgr = app.createModule<EventManager>();
  app.getProcessManager().addProcess(evtMgr);
  evtMgr->addListener<TestEvent>([](const TestEvent &p_evt) { NCFW_INFO("Test: {}", p_evt.getText()); });
  evtMgr->pushNew<TestEvent>("foo");

  ActorFactory *actorFactory = app.createModule<ActorFactory>();
  std::unique_ptr<Actor> actor = actorFactory->createRootActor("root");

  return app.main({p_argv, p_argv + p_argc});
}