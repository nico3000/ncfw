#pragma once
#include <filesystem>

namespace ncfw {
class ResourceSource {
public:
  virtual ~ResourceSource() = default;

  virtual std::optional<size_t> tryGetResourceByteSize(const std::filesystem::path &p_resourcePath) = 0;
  virtual void load(const std::filesystem::path &p_resourcePath, uint8_t *p_dst, size_t p_dstByteSize) = 0;
};
} // namespace ncfw
