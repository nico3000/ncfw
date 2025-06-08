#pragma once

namespace ncfw {
class Process {
public:
  enum class Status { eContinue, eFinished, eFailed, eAborted };

  virtual ~Process() = default;

  virtual Status update() = 0;

private:
};
} // namespace ncfw
