#pragma once
#include "ncfw/ResCache/ResourceSource.hpp"

#include <filesystem>

namespace ncfw {
class FileSystemSource : public ResourceSource {
public:
  FileSystemSource(const std::filesystem::path &p_root);

  std::optional<size_t> tryGetResourceByteSize(const std::filesystem::path &p_resourcePath) override;
  void load(const std::filesystem::path &p_resourcePath, uint8_t *p_dst, size_t p_dstByteSize) override;

private:
  std::filesystem::path m_root;
};
} // namespace ncfw
