#pragma once
#include <filesystem>
#include <fstream>
#include <string>

namespace ncfw {
class Logger {
public:
  enum class Severity { ePlain, eInfo, eWarning, eError, eFatal };

  Logger(const std::filesystem::path &p_logFilePath);
  ~Logger();

  void log(const std::string &p_file, int32_t p_line, Severity p_severity, const std::string &p_message);
  void flushLogFile() { m_logFile.flush(); }

private:
  std::ofstream m_logFile;
};
} // namespace ncfw