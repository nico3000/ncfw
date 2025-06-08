#pragma once
#include <filesystem>
#include <fstream>
#include <string>

namespace ncfw {
class Logger {
public:
  enum class Severity { eInfo, eWarning, eError, eFatal };

  static std::string applyTextStyle(const std::string &p_text, uint32_t p_code);

  Logger(const std::filesystem::path &p_logFilePath);
  ~Logger();

  void log(const std::string &p_file, int32_t p_line, Severity p_severity, const std::string &p_message);
  void flushLogFile() { m_logFile.flush(); }

private:
  std::ofstream m_logFile;
};
} // namespace ncfw

#define NCFW_TEXT_BLACK(_text) ncfw::Logger::applyTextStyle(_text, 30)
#define NCFW_TEXT_RED(_text) ncfw::Logger::applyTextStyle(_text, 31)
#define NCFW_TEXT_GREEN(_text) ncfw::Logger::applyTextStyle(_text, 32)
#define NCFW_TEXT_YELLOW(_text) ncfw::Logger::applyTextStyle(_text, 33)
#define NCFW_TEXT_BLUE(_text) ncfw::Logger::applyTextStyle(_text, 34)
#define NCFW_TEXT_MAGENTA(_text) ncfw::Logger::applyTextStyle(_text, 35)
#define NCFW_TEXT_CYAN(_text) ncfw::Logger::applyTextStyle(_text, 36)
#define NCFW_TEXT_WHITE(_text) ncfw::Logger::applyTextStyle(_text, 37)
#define NCFW_TEXT_BRIGHT_BLACK(_text) ncfw::Logger::applyTextStyle(_text, 90)
#define NCFW_TEXT_BRIGHT_RED(_text) ncfw::Logger::applyTextStyle(_text, 91)
#define NCFW_TEXT_BRIGHT_GREEN(_text) ncfw::Logger::applyTextStyle(_text, 92)
#define NCFW_TEXT_BRIGHT_YELLOW(_text) ncfw::Logger::applyTextStyle(_text, 93)
#define NCFW_TEXT_BRIGHT_BLUE(_text) ncfw::Logger::applyTextStyle(_text, 94)
#define NCFW_TEXT_BRIGHT_MAGENTA(_text) ncfw::Logger::applyTextStyle(_text, 95)
#define NCFW_TEXT_BRIGHT_CYAN(_text) ncfw::Logger::applyTextStyle(_text, 96)
#define NCFW_TEXT_BRIGHT_WHITE(_text) ncfw::Logger::applyTextStyle(_text, 97)