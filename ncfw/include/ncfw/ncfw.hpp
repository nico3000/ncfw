#pragma once
#include "Logger.hpp"

#include <format> // IWYU pragma: keep
#include <memory>

namespace ncfw {
static inline std::unique_ptr<Logger> g_logger;
}

#define NCFW_LOG(_fmt, ...)                                                                                            \
  ncfw::g_logger->log(__FILE__, __LINE__, ncfw::Logger::Severity::ePlain, std::format(_fmt, __VA_ARGS__))
#define NCFW_INFO(_fmt, ...)                                                                                           \
  ncfw::g_logger->log(__FILE__, __LINE__, ncfw::Logger::Severity::eInfo, std::format(_fmt, __VA_ARGS__))
#define NCFW_WARN(_fmt, ...)                                                                                           \
  ncfw::g_logger->log(__FILE__, __LINE__, ncfw::Logger::Severity::eWarning, std::format(_fmt, __VA_ARGS__))
#define NCFW_ERROR(_fmt, ...)                                                                                          \
  ncfw::g_logger->log(__FILE__, __LINE__, ncfw::Logger::Severity::eError, std::format(_fmt, __VA_ARGS__))
#define NCFW_FATAL(_fmt, ...)                                                                                          \
  ncfw::g_logger->log(__FILE__, __LINE__, ncfw::Logger::Severity::eFatal, std::format(_fmt, __VA_ARGS__))

#define NCFW_INFO_IF(_cond, _fmt, ...)                                                                                 \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_INFO(_fmt, __VA_ARGS__);                                                                                    \
    }                                                                                                                  \
  } while (0)

#define NCWF_WARN_IF(_cond, _fmt, ...)                                                                                 \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_WARN(_fmt, __VA_ARGS__);                                                                                    \
    }                                                                                                                  \
  } while (0)

#define NCWF_ERROR_IF(_cond, _fmt, ...)                                                                                \
  do {                                                                                                                 \
    if (_cond) {                                                                                                       \
      NCFW_ERROR(_fmt, __VA_ARGS__);                                                                                   \
    }                                                                                                                  \
  } while (0)

#define NCFW_INFO_UNLESS(_cond, _fmt, ...) NCFW_INFO_IF(!(_cond), _fmt, __VA_ARGS__)
#define NCFW_WARN_UNLESS(_cond, _fmt, ...) NCFW_WARN_IF(!(_cond), _fmt, __VA_ARGS__)
#define NCFW_ERROR_UNLESS(_cond, _fmt, ...) NCFW_ERROR_IF(!(_cond), _fmt, __VA_ARGS__)

#ifdef _WIN32
#define NCFW_BREAK() _CrtDbgBreak()
#else
#define NCFW_BREAK() __builtin_trap()
#endif

#define NCFW_ASSERT(_cond, _fmt, ...)                                                                                  \
  do {                                                                                                                 \
    if (!(_cond)) {                                                                                                    \
      NCFW_FATAL(_fmt, __VA_ARGS__);                                                                                   \
      ncfw::g_logger->flushLogFile();                                                                                  \
      NCFW_BREAK();                                                                                                    \
      exit(1);                                                                                                         \
    }                                                                                                                  \
  } while (0)
