#pragma once
#include <future>
#include <stdint.h>
#include <string>
#include <vector>

namespace ncfw {
class Resource {
public:
  typedef std::future<std::unique_ptr<std::vector<uint8_t>>> FutureData;

  Resource(const std::string &p_name, FutureData p_futureData);

  const std::string &getName() const { return m_name; }
  bool wait();
  const std::string &getError() const { return m_error.value(); }
  const uint8_t *data() const { return m_data.data(); }
  size_t byteSize() const { return m_data.size(); }
  std::string createString() const;

private:
  enum class Status { eCreated, eLoaded, eError };

  std::string m_name;
  Status m_status = Status::eCreated;
  std::vector<uint8_t> m_data;
  std::mutex m_mtx;
  FutureData m_futureData;
  std::optional<std::string> m_error;
};
} // namespace ncfw
