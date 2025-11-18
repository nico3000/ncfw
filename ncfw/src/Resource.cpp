#include "ncfw/ResCache/Resource.hpp"
#include "ncfw/Exception.hpp"
#include <mutex>

namespace ncfw {
Resource::Resource(const std::string &p_name, FutureData p_futureData)
    : m_name(p_name), m_futureData(std::move(p_futureData)) {}

bool Resource::wait() {
  std::lock_guard guard{m_mtx};
  if (m_status == Status::eCreated) {
    try {
      m_futureData.wait();
      m_data = std::move(*m_futureData.get());
      m_status = Status::eLoaded;
    } catch (const Exception &ex) {
      m_error = ex.what();
      m_status = Status::eError;
    }
  }
  return m_status == Status::eLoaded;
}

std::string Resource::createString() const {
  return {reinterpret_cast<const char *>(m_data.data()), reinterpret_cast<const char *>(m_data.data()) + m_data.size()};
}
} // namespace ncfw