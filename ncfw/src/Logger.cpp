#include "ncfw/Logger.hpp"

#include <filesystem>
#include <iostream>
#include <regex>

namespace ncfw {
Logger::Logger(const std::filesystem::path &p_logFilePath) {
  if (std::filesystem::is_directory(p_logFilePath)) {
    std::cout << std::format("{}({}) {} Given log file path points to a directory: {}", __FILE__, __LINE__,
                             NCFW_TEXT_RED("[ERROR]"), p_logFilePath.string())
              << std::endl;
  }
  m_logFile.open(p_logFilePath);
  if (!m_logFile) {
    std::cout << std::format("{}({}) {} Given log file could not be opened for writing: {}", __FILE__, __LINE__,
                             NCFW_TEXT_RED("[ERROR]"), p_logFilePath.string())
              << std::endl;
  }
}

Logger::~Logger() {}

void Logger::log(const std::string &p_file, int32_t p_line, Severity p_severity, const std::string &p_message) {
  std::string message = p_message;
  if (p_severity != Severity::eInfo) {
    std::string tag;
    switch (p_severity) {
    case Severity::eWarning: tag = NCFW_TEXT_YELLOW("[WARN]"); break;
    case Severity::eError: tag = NCFW_TEXT_RED("[ERROR]"); break;
    case Severity::eFatal: tag = "\033[41m[FATAL]\033[0m"; break;
    default: tag = "?"; break;
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

std::string Logger::applyTextStyle(const std::string &p_text, uint32_t p_code) {
  return std::format("\033[{}m{}\033[0m", p_code, p_text);
}
} // namespace ncfw