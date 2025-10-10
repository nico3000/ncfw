#pragma once
#include "ncfw/AppModule.hpp"
#include "ncfw/Exception.hpp"
#include "ncfw/Logger.hpp"
#include "ncfw/ProcessSystem/ProcessManager.hpp"

#include <format>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#define NCFW_BREAK() _CrtDbgBreak()
#else
#define NCFW_BREAK() __builtin_trap()
#endif

#define NCFW_INFO(_fmt, ...)                                                                                           \
  ncfw::g_app->getLogger().log(__FILE__, __LINE__, ncfw::Logger::Severity::eInfo, std::format(_fmt, __VA_ARGS__))
#define NCFW_WARN(_fmt, ...)                                                                                           \
  ncfw::g_app->getLogger().log(__FILE__, __LINE__, ncfw::Logger::Severity::eWarning, std::format(_fmt, __VA_ARGS__))
#define NCFW_ERROR(_fmt, ...)                                                                                          \
  ncfw::g_app->getLogger().log(__FILE__, __LINE__, ncfw::Logger::Severity::eError, std::format(_fmt, __VA_ARGS__))
#define NCFW_FATAL(_fmt, ...)                                                                                          \
  ncfw::g_app->getLogger().log(__FILE__, __LINE__, ncfw::Logger::Severity::eFatal, std::format(_fmt, __VA_ARGS__))

#define NCFW_INFO_IF(_cond, _fmt, ...)                                                                                 \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_INFO(_fmt, __VA_ARGS__);                                                                                    \
    }                                                                                                                  \
  } while (0)

#define NCFW_WARN_IF(_cond, _fmt, ...)                                                                                 \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_WARN(_fmt, __VA_ARGS__);                                                                                    \
    }                                                                                                                  \
  } while (0)

#define NCFW_ERROR_IF(_cond, _fmt, ...)                                                                                \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_ERROR(_fmt, __VA_ARGS__);                                                                                   \
    }                                                                                                                  \
  } while (0)

#define NCFW_THROW_IF(_cond, _fmt, ...)                                                                                \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_FATAL(_fmt, __VA_ARGS__);                                                                                   \
      ncfw::g_app->getLogger().flushLogFile();                                                                         \
      NCFW_BREAK();                                                                                                    \
      throw ncfw::Exception(std::format(_fmt, __VA_ARGS__));                                                           \
      exit(1);                                                                                                         \
    }                                                                                                                  \
  } while (0)

#define NCFW_INFO_UNLESS(_cond, _fmt, ...) NCFW_INFO_IF(!(_cond), _fmt, __VA_ARGS__)
#define NCFW_WARN_UNLESS(_cond, _fmt, ...) NCFW_WARN_IF(!(_cond), _fmt, __VA_ARGS__)
#define NCFW_ERROR_UNLESS(_cond, _fmt, ...) NCFW_ERROR_IF(!(_cond), _fmt, __VA_ARGS__)
#define NCFW_THROW_UNLESS(_cond, _fmt, ...) NCFW_THROW_IF(!(_cond), _fmt, __VA_ARGS__)

namespace ncfw {
extern class App *g_app;

class App {
public:
  App();
  virtual ~App();

  int32_t main(const std::vector<std::string> &p_args = {});
  Logger &getLogger() { return *m_logger; }
  ProcessManager &getProcessManager() { return *m_processManager; }
  void discontinue() { m_continue = false; }

  template <typename T, typename... Args>
  T *createModule(Args... p_args)
    requires(std::is_base_of_v<AppModule, T>)
  {
    NCFW_THROW_UNLESS(m_modules.find(typeid(T)) == m_modules.end(), "App module {} was already created.",
                      typeid(T).name());
    return dynamic_cast<T *>(m_modules.emplace(typeid(T), std::make_unique<T>(p_args...)).first->second.get());
  }

  template <typename T>
  T *getModule() const
    requires(std::is_base_of_v<AppModule, T>)
  {
    auto it = m_modules.find(typeid(T));
    return it == m_modules.end() ? nullptr : dynamic_cast<T *>(it->second.get());
  }

private:
  std::unique_ptr<Logger> m_logger;
  std::unordered_map<std::type_index, std::unique_ptr<AppModule>> m_modules;
  ProcessManager *m_processManager;
  bool m_continue = true;

  void mainLoop();
};
} // namespace ncfw
