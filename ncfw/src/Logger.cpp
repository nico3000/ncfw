#include "ncfw/Logger.hpp"

#include <filesystem>
#include <iostream>
#include <regex>

namespace ncfw {
Logger::Logger(const std::filesystem::path &p_logFilePath) {
  if (std::filesystem::is_directory(p_logFilePath)) {
    std::cout << std::format("{}({}) [ERROR] Given log file path points to a directory: {}", __FILE__, __LINE__,
                             p_logFilePath.string())
              << std::endl;
  }
  m_logFile.open(p_logFilePath);
  if (!m_logFile) {
    std::cout << std::format("{}({}) [ERROR] Given log file could not be opened for writing: {}", __FILE__, __LINE__,
                             p_logFilePath.string())
              << std::endl;
  }
}

Logger::~Logger() {}

void Logger::log(const std::string &p_file, int32_t p_line, Severity p_severity, const std::string &p_message) {
  std::string message;
  if (p_severity == Severity::ePlain) {
    message = p_message;
  } else if (p_severity == Severity::eInfo) {
    message = "\033[32m[INFO]\033[0m " + p_message;
  } else {
    std::string tag;
    switch (p_severity) {
    case Severity::eWarning:
      tag = "\033[33m[WARN]\033[0m";
      break;
    case Severity::eError:
      tag = "\033[31m[ERROR]\033[0m";
      break;
    case Severity::eFatal:
      tag = "\033[41m[FATAL]\033[0m";
      break;
    default:
      tag = "?";
      break;
    }
    message = std::format("{}({}) {} {}", p_file, p_line, tag, p_message);
  }
  static const std::regex graphicEscapeSequence("\033\\[[^m]*m");
  m_logFile << std::regex_replace(message, graphicEscapeSequence, "");
  std::cout << message;
  if (!message.ends_with('\n') && !message.ends_with('\r')) {
    m_logFile << std::endl;
    std::cout << std::endl;
  }
}
} // namespace ncfw