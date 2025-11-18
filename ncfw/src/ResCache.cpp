#include "ncfw/ResCache/ResCache.hpp"

#include "ncfw/ResCache/Resource.hpp"

#include <future>

namespace ncfw {
std::shared_ptr<Resource> ResCache::getResource(const std::filesystem::path &p_resourcePath) {
  std::lock_guard guard(m_mtx);
  if (auto findIt = m_resources.find(p_resourcePath); findIt != m_resources.end()) {
    std::shared_ptr<Resource> res = findIt->second.lock();
    if (res) {
      m_lru.erase(std::find(m_lru.begin(), m_lru.end(), res));
      m_lru.emplace_front(res);
      return res;
    } else {
      m_resources.erase(findIt);
    }
  }

  for (const auto &src : m_sources) {
    std::optional<size_t> byteSize = src->tryGetResourceByteSize(p_resourcePath);
    if (byteSize) {
      ResourceSource *srcPtr = src.get();
      auto loaderFn = [byteSize, srcPtr, p_resourcePath]() {
        std::unique_ptr<std::vector<uint8_t>> data = std::make_unique<std::vector<uint8_t>>(byteSize.value());
        srcPtr->load(p_resourcePath, data->data(), data->size());
        return std::move(data);
      };
      std::shared_ptr<Resource> res =
          std::make_shared<Resource>(p_resourcePath.string(), std::async(std::launch::async, loaderFn));
      m_resources.emplace(p_resourcePath, res);
      m_lru.emplace_front(res);
      return res;
    }
  }
  return nullptr;
}
} // namespace ncfw